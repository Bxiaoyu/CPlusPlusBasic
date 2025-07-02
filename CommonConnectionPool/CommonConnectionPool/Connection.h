#pragma once
#include <mysql.h>
#include <string>
#include <ctime>

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

	// ˢ��һ�����ӵ���ʼ����ʱ���
	void updateAliveTime() { alivetime_ = clock(); }

	// ���ش��ʱ��
	clock_t getAliveTime() const { return clock() - alivetime_; }
private:
	MYSQL* conn_;  // ��ʾ��mysql server��һ������
	clock_t alivetime_;  // ��¼�������״̬�����ʼ���ʱ��
};