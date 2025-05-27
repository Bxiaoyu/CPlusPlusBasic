#include "public.h"
#include "Connection.h"
#include <iostream>

Connection::Connection()
{
	// 初始化数据库连接
	conn_ = mysql_init(nullptr);
}

Connection::~Connection()
{
	// 释放数据库连接资源
	if (conn_ != nullptr)
		mysql_close(conn_);
}

bool Connection::connect(const std::string& ip, unsigned short port, const std::string& user, const std::string& password, const std::string& dbname)
{
	// 连接数据库
	MYSQL* p = mysql_real_connect(conn_, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}

bool Connection::update(const std::string& sql)
{
	// 更新操作
	if (mysql_query(conn_, sql.c_str()))
	{
		LOG("更新失败：" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(const std::string& sql)
{
	// 查询操作
	if (mysql_query(conn_, sql.c_str()))
	{
		LOG("查询失败：" + sql);
		return nullptr;
	}
	return mysql_use_result(conn_);
}
