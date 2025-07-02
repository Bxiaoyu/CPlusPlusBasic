#pragma once
#include <mysql.h>
#include <string>
#include <ctime>

/*
* 实现MySql数据库的操作
*/
class Connection
{
public:
	// 初始化数据库连接
	Connection();

	// 释放数据库连接资源
	~Connection();

	// 连接数据库
	bool connect(
		const std::string& ip, 
		unsigned short port, 
		const std::string& user, 
		const std::string& password, 
		const std::string& dbname);

	// 更新操作 insert、delete、update
	bool update(const std::string& sql);

	// 查询操作 select
	MYSQL_RES* query(const std::string& sql);

	// 刷新一下连接的起始空闲时间点
	void updateAliveTime() { alivetime_ = clock(); }

	// 返回存活时间
	clock_t getAliveTime() const { return clock() - alivetime_; }
private:
	MYSQL* conn_;  // 表示和mysql server的一条连接
	clock_t alivetime_;  // 记录进入空闲状态后的起始存活时间
};