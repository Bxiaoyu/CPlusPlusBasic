#include "CommonConnectionPool.h"

// 线程安全的懒汉单例函数接口
ConnectionPool* ConnectionPool::GetConnectionPool()
{
    static ConnectionPool instance;
    return &instance;
}

void ConnectionPool::LoadConfigFile()
{
}
