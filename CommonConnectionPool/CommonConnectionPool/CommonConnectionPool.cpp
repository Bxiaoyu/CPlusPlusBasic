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
        connectionQue_.push(p);
        ConnectionCnt_++;
    }

    // 启动一个新线程，作为连接的生产者
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
            cv_.wait(lock);
        }
    }
}
