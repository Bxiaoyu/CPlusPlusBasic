#include "CommonConnectionPool.h"

// �̰߳�ȫ���������������ӿ�
ConnectionPool* ConnectionPool::GetConnectionPool()
{
    static ConnectionPool instance;
    return &instance;
}

void ConnectionPool::LoadConfigFile()
{
}
