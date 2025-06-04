#pragma once
#include <string>
#include <queue>
#include <mutex>
#include "Connection.h"

/*
* ʵ�����ӳ�
*/
class ConnectionPool
{
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* GetConnectionPool();
private:
	// ����#1 ���캯��˽�л�
	ConnectionPool();

	// �������ݿ������ļ�
	bool LoadConfigFile();

	std::string ip_;         // MySQL��IP��ַ
	unsigned short port_;    // MySQL�˿ں� 3306
	std::string username_;   // MySQL��¼�û���
	std::string password_;   // MySQL��¼����
	int initSize_;           // ���ӳس�ʼ������
	int maxSize_;            // ���ӳ����������
	int maxIdleTime_;        // ���ӳ�������ʱ��
	int connectionTimeout_;  // ���ӳػ�ȡ���ӵĳ�ʱʱ��

	std::queue<Connection*> connectionQue_;  // �洢MySQL���Ӷ���
	std::mutex queueMtx_;                    // ά�����Ӷ��е��̰߳�ȫ������
};