#pragma once
#include <string>
#include <queue>
#include <mutex>
#include "Connection.h"

/*
* 实现连接池
*/
class ConnectionPool
{
public:
	// 获取连接池对象实例
	static ConnectionPool* GetConnectionPool();
private:
	// 单例#1 构造函数私有化
	ConnectionPool();

	// 加载数据库配置文件
	bool LoadConfigFile();

	std::string ip_;         // MySQL的IP地址
	unsigned short port_;    // MySQL端口号 3306
	std::string username_;   // MySQL登录用户名
	std::string password_;   // MySQL登录密码
	int initSize_;           // 连接池初始连接量
	int maxSize_;            // 连接池最大连接量
	int maxIdleTime_;        // 连接池最大空闲时间
	int connectionTimeout_;  // 连接池获取连接的超时时间

	std::queue<Connection*> connectionQue_;  // 存储MySQL连接队列
	std::mutex queueMtx_;                    // 维护连接队列的线程安全互斥锁
};