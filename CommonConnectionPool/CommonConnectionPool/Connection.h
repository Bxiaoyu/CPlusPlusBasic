#pragma once
#include "mysql.h"
#include <string>

/*
* ʵ��MySql���ݿ�Ĳ���
*/
class Connection
{
public:
	// ��ʼ�����ݿ�����
	Connection();

	// �ͷ����ݿ�������Դ
	~Connection();

	// �������ݿ�
	bool connect(
		const std::string& ip, 
		unsigned short port, 
		const std::string& user, 
		const std::string& password, 
		const std::string& dbname);

	// ���²��� insert��delete��update
	bool update(const std::string& sql);

	// ��ѯ���� select
	MYSQL_RES* query(const std::string& sql);
private:
	MYSQL* conn_;  // ��ʾ��mysql server��һ������
};