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
* ʵ�����ӳ�
*/
class ConnectionPool
{
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* GetConnectionPool();

	// ���ⲿ�ṩ�ӿڣ������ӳػ�ȡһ�����õĿ�������
	std::shared_ptr<Connection> GetConnection();
private:
	// ����#1 ���캯��˽�л�
	ConnectionPool();

	// �������ݿ������ļ�
	bool LoadConfigFile();

	// �����ڶ����߳��У�ר�Ÿ�������������
	void ProduceConnectionTask();

private:
	std::string ip_;         // MySQL��IP��ַ
	unsigned short port_;    // MySQL�˿ں� 3306
	std::string username_;   // MySQL��¼�û���
	std::string password_;   // MySQL��¼����
	std::string dbname_;     // ���ӵ����ݿ�����
	int initSize_;           // ���ӳس�ʼ������
	int maxSize_;            // ���ӳ����������
	int maxIdleTime_;        // ���ӳ�������ʱ��
	int connectionTimeout_;  // ���ӳػ�ȡ���ӵĳ�ʱʱ��

	std::queue<Connection*> connectionQue_;  // �洢MySQL���Ӷ���
	std::mutex queueMtx_;                    // ά�����Ӷ��е��̰߳�ȫ������
	std::atomic_int ConnectionCnt_;          // ��¼������������connection���ӵ�������
	std::condition_variable cv_;             // ���������������������������̺߳������̵߳�ͨ��
};