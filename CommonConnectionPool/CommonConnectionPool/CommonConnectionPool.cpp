#include <iostream>
#include "CommonConnectionPool.h"
#include "public.h"

using namespace std;

// 线程安全的懒汉单例函数接口
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
    * shared_ptr智能指针析构时，会把connection资源直接delete掉，相当于调用了connection的析构，
    * connection就被close掉了。这里需要自定义shared_ptr的资源释放方式，把connection直接归还到queue中
    */
    shared_ptr<Connection> sp(connectionQue_.front(),
        [&](Connection* pcon) 
        {
            unique_lock<mutex> lock(queueMtx_);
            pcon->updateAliveTime();  // 刷新一下开始空闲的起始时间
            connectionQue_.push(pcon);
        });
    connectionQue_.pop();
    cv_.notify_all();  // 消费完连接以后，通知生产者线程检查一下，如果队列为空了，赶紧生产

    return sp;
}

// 连接池构造
ConnectionPool::ConnectionPool()
{
    // 加载配置项
    if (!LoadConfigFile())
    {
        LOG("Load config failed...");
        return;
    }

    // 创建初始数量的连接
    for (int i = 0; i < initSize_; ++i)
    {
        Connection* p = new Connection();
        p->connect(ip_, port_, username_, password_, dbname_);
        p->updateAliveTime();  // 刷新一下开始空闲的起始时间
        connectionQue_.push(p);
        connectionCnt_++;
    }

    // 启动一个新线程，作为连接的生产者
    thread produce(std::bind(&ConnectionPool::ProduceConnectionTask, this));
    produce.detach();

    // 启动一个新线程，扫描超过maxIdleTime时间的空闲连接，进行多余的连接回收
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
        if (idx == -1)  // 无效配置
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
            cv_.wait(lock);  // 队列不空，此处生产线程进入等待状态
        }

        // 连接数量没有达到上限，继续创建新的连接
        if (connectionCnt_ < maxSize_)
        {
            Connection* p = new Connection();
            p->connect(ip_, port_, username_, password_, dbname_);
            p->updateAliveTime();  // 刷新一下开始空闲的起始时间
            connectionQue_.push(p);
            connectionCnt_++;
        }

        // 通知消费者线程，可以消费连接了
        cv_.notify_all();
    }
}

void ConnectionPool::scanConnectionTask()
{
    for (;;)
    {
        // 通过sleep模拟定时效果
        this_thread::sleep_for(std::chrono::seconds(maxIdleTime_));

        // 扫描整个队列，释放多余连接
        unique_lock<mutex> lock(queueMtx_);
        while (connectionCnt_ > initSize_)
        {
            Connection* p = connectionQue_.front();
            if (p->getAliveTime() >= (maxIdleTime_ * 1000))
            {
                connectionQue_.pop();
                connectionCnt_--;
                delete p;  // 调用~Connection()释放连接
            }
            else
            {
                break;  // 队头连接都没有超过maxIdleTime，其它连接肯定没有
            }
        }
    }
}
