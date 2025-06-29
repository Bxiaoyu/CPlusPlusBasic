#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include "Connection.h"

/*
* 实现连接池
*/
class ConnectionPool
{
public:
	// 获取连接池对象实例
	static ConnectionPool* GetConnectionPool();

	// 给外部提供接口，从连接池获取一个可用的空闲连接
	std::shared_ptr<Connection> GetConnection();
private:
	// 单例#1 构造函数私有化
	ConnectionPool();

	// 加载数据库配置文件
	bool LoadConfigFile();

	// 运行在独立线程中，专门负责生产新连接
	void ProduceConnectionTask();

private:
	std::string ip_;         // MySQL的IP地址
	unsigned short port_;    // MySQL端口号 3306
	std::string username_;   // MySQL登录用户名
	std::string password_;   // MySQL登录密码
	std::string dbname_;     // 连接的数据库名称
	int initSize_;           // 连接池初始连接量
	int maxSize_;            // 连接池最大连接量
	int maxIdleTime_;        // 连接池最大空闲时间
	int connectionTimeout_;  // 连接池获取连接的超时时间

	std::queue<Connection*> connectionQue_;  // 存储MySQL连接队列
	std::mutex queueMtx_;                    // 维护连接队列的线程安全互斥锁
	std::atomic_int ConnectionCnt_;          // 记录连接所创建的connection连接的总数量
	std::condition_variable cv_;             // 设置条件变量，用于连接生产线程和消费线程的通信
};