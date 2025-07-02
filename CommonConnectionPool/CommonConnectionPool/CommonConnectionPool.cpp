#include <iostream>
#include "CommonConnectionPool.h"
#include "public.h"

using namespace std;

// �̰߳�ȫ���������������ӿ�
ConnectionPool* ConnectionPool::GetConnectionPool()
{
    static ConnectionPool instance;
    return &instance;
}

std::shared_ptr<Connection> ConnectionPool::GetConnection()
{
    unique_lock<mutex> lock(queueMtx_);
    while (connectionQue_.empty())
    {
        if (cv_status::timeout == cv_.wait_for(lock, std::chrono::milliseconds(connectionTimeout_)))
        {
            if (connectionQue_.empty())
            {
                LOG("Get connection timeout...");
                return nullptr;
            }
        }
    }

    /*
    * shared_ptr����ָ������ʱ�����connection��Դֱ��delete�����൱�ڵ�����connection��������
    * connection�ͱ�close���ˡ�������Ҫ�Զ���shared_ptr����Դ�ͷŷ�ʽ����connectionֱ�ӹ黹��queue��
    */
    shared_ptr<Connection> sp(connectionQue_.front(),
        [&](Connection* pcon) 
        {
            unique_lock<mutex> lock(queueMtx_);
            pcon->updateAliveTime();  // ˢ��һ�¿�ʼ���е���ʼʱ��
            connectionQue_.push(pcon);
        });
    connectionQue_.pop();
    cv_.notify_all();  // �����������Ժ�֪ͨ�������̼߳��һ�£��������Ϊ���ˣ��Ͻ�����

    return sp;
}

// ���ӳع���
ConnectionPool::ConnectionPool()
{
    // ����������
    if (!LoadConfigFile())
    {
        LOG("Load config failed...");
        return;
    }

    // ������ʼ����������
    for (int i = 0; i < initSize_; ++i)
    {
        Connection* p = new Connection();
        p->connect(ip_, port_, username_, password_, dbname_);
        p->updateAliveTime();  // ˢ��һ�¿�ʼ���е���ʼʱ��
        connectionQue_.push(p);
        connectionCnt_++;
    }

    // ����һ�����̣߳���Ϊ���ӵ�������
    thread produce(std::bind(&ConnectionPool::ProduceConnectionTask, this));
    produce.detach();

    // ����һ�����̣߳�ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ж�������ӻ���
    thread scanner(std::bind(&ConnectionPool::scanConnectionTask, this));
    scanner.detach();
}

bool ConnectionPool::LoadConfigFile()
{
    FILE* pf = fopen("mysql.ini", "r");
    if (pf == nullptr)
    {
        LOG("mysql.ini file is not exist!");
        return false;
    }

    while (!feof(pf))
    {
        char line[1024] = { 0 };
        fgets(line, 1024, pf);
        std::string str = line;

        int idx = str.find('=', 0);
        if (idx == -1)  // ��Ч����
        {
            continue;
        }

        int endidx = str.find('\n', idx);
        std::string key = str.substr(0, idx);
        std::string value = str.substr(idx + 1, endidx - idx - 1);
        //std::cout << key << ":" << value << std::endl;
        if (key == "ip")
        {
            ip_ = value;
        }
        else if (key == "port")
        {
            port_ = atoi(value.c_str());
        }
        else if (key == "username")
        {
            username_ = value;
        }
        else if (key == "password")
        {
            password_ = value;
        }
        else if (key == "dbname")
        {
            dbname_ = value;
        }
        else if (key == "initSize")
        {
            initSize_ = atoi(value.c_str());
        }
        else if (key == "maxSize")
        {
            maxSize_ = atoi(value.c_str());
        }
        else if (key == "maxIdleTime")
        {
            maxIdleTime_ = atoi(value.c_str());
        }
        else if (key == "connectionTimeOut")
        {
            connectionTimeout_ = atoi(value.c_str());
        }
    }
}

void ConnectionPool::ProduceConnectionTask()
{
    for (;;)
    {
        unique_lock<mutex> lock(queueMtx_);
        while (!connectionQue_.empty())
        {
            cv_.wait(lock);  // ���в��գ��˴������߳̽���ȴ�״̬
        }

        // ��������û�дﵽ���ޣ����������µ�����
        if (connectionCnt_ < maxSize_)
        {
            Connection* p = new Connection();
            p->connect(ip_, port_, username_, password_, dbname_);
            p->updateAliveTime();  // ˢ��һ�¿�ʼ���е���ʼʱ��
            connectionQue_.push(p);
            connectionCnt_++;
        }

        // ֪ͨ�������̣߳���������������
        cv_.notify_all();
    }
}

void ConnectionPool::scanConnectionTask()
{
    for (;;)
    {
        // ͨ��sleepģ�ⶨʱЧ��
        this_thread::sleep_for(std::chrono::seconds(maxIdleTime_));

        // ɨ���������У��ͷŶ�������
        unique_lock<mutex> lock(queueMtx_);
        while (connectionCnt_ > initSize_)
        {
            Connection* p = connectionQue_.front();
            if (p->getAliveTime() >= (maxIdleTime_ * 1000))
            {
                connectionQue_.pop();
                connectionCnt_--;
                delete p;  // ����~Connection()�ͷ�����
            }
            else
            {
                break;  // ��ͷ���Ӷ�û�г���maxIdleTime���������ӿ϶�û��
            }
        }
    }
}
