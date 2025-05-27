#include "public.h"
#include "Connection.h"
#include <iostream>

Connection::Connection()
{
	// ��ʼ�����ݿ�����
	conn_ = mysql_init(nullptr);
}

Connection::~Connection()
{
	// �ͷ����ݿ�������Դ
	if (conn_ != nullptr)
		mysql_close(conn_);
}

bool Connection::connect(const std::string& ip, unsigned short port, const std::string& user, const std::string& password, const std::string& dbname)
{
	// �������ݿ�
	MYSQL* p = mysql_real_connect(conn_, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}

bool Connection::update(const std::string& sql)
{
	// ���²���
	if (mysql_query(conn_, sql.c_str()))
	{
		LOG("����ʧ�ܣ�" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(const std::string& sql)
{
	// ��ѯ����
	if (mysql_query(conn_, sql.c_str()))
	{
		LOG("��ѯʧ�ܣ�" + sql);
		return nullptr;
	}
	return mysql_use_result(conn_);
}
