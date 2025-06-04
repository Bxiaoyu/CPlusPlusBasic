#include <iostream>
#include "CommonConnectionPool.h"
#include "public.h"

// 线程安全的懒汉单例函数接口
ConnectionPool* ConnectionPool::GetConnectionPool()
{
    static ConnectionPool instance;
    return &instance;
}

bool ConnectionPool::LoadConfigFile()
{
    FILE* pf = fopen("mysql.ini", "r");
    if (pf == nullptr)
    {
        LOG("mysql.ini file is not exist!");
        return false;
    }


}
