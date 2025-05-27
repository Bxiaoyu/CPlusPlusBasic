#pragma once
#include "mysql.h"
#include <string>

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
private:
	MYSQL* conn_;  // 表示和mysql server的一条连接
};