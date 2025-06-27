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

    while (!feof(pf))
    {
        char line[1024] = { 0 };
        fgets(line, 1024, pf);
        std::string str = line;

        int idx = str.find('=', 0);
        if (idx == -1)
        {
            continue;
        }

        int endidx = str.find('\n', idx);
        std::string key = str.substr(0, idx);
        std::string value = str.substr(idx + 1, endidx - idx - 1);

        std::cout << key << ":" << value << std::endl;
    }
}
