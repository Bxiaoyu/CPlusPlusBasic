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
        connectionQue_.push(p);
        ConnectionCnt_++;
    }

    // ����һ�����̣߳���Ϊ���ӵ�������
    thread produce(std::bind(&ConnectionPool::ProduceConnectionTask, this));
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
            cv_.wait(lock);
        }
    }
}
