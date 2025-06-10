// 25_һ���Թ�ϣ�㷨.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
#include "md5.h"
using namespace std;

// һ���Թ�ϣ����ȡֵ����
using uint = unsigned int;

class PhscialHost;  // ǰ������

// ����ڵ�
class VirtualHost
{
public:
	VirtualHost(const string& ip, PhscialHost* p)
		: ip_(ip)
		, phscialHost_(p)
	{
		md5_ = getMD5(ip_.c_str());
	}

	bool operator<(const VirtualHost& host) const
	{
		return md5_ < host.md5_;
	}

	bool operator==(const VirtualHost& host) const
	{
		return ip_ == host.ip_;
	}

	uint get_md5() const
	{
		return md5_;
	}

	const PhscialHost* getPhscialHost() const
	{
		return phscialHost_;
	}

private:
	string ip_;                 // ����ڵ��ip��Ϣ
	uint md5_;                   // ����ڵ���һ���Թ�ϣ���ϵ�λ��
	PhscialHost* phscialHost_;  // ����ڵ�����������ڵ�
};

// ����ڵ�
class PhscialHost
{
public:
	PhscialHost(const string& ip, int vnumber)
		: ip_(ip)
	{
		for (int i = 0; i < vnumber; i++)
		{
			virtualHosts_.emplace_back(
				ip + "#" + ::to_string(i),
				this
			);
		}
	}

	string getIp() const
	{
		return ip_;
	}

	const list<VirtualHost>& getVirtualHosts() const
	{
		return virtualHosts_;
	}
private:
	string ip_;                       // �������IP��ַ
	list<VirtualHost> virtualHosts_;  // �洢����ڵ��б�
};

// һ���Թ�ϣ�㷨����ʵ��
class ConsistentHash
{
public:
	// ��һ���Թ�ϣ���������������������ڵ�
	void addHost(const PhscialHost& host)
	{
		// ��ȡ�����������е�����ڵ��б�
		auto virtualList = host.getVirtualHosts();
		for (auto host : virtualList)
		{
			hashCircle_.insert(host);
		}
	}

	// ��һ���Թ�ϣ����ɾ����������������ڵ�
	void delHost(const PhscialHost& host)
	{
		// ��ȡ�����������е�����ڵ��б�
		auto virtualList = host.getVirtualHosts();
		for (auto host : virtualList)
		{
			auto it = hashCircle_.find(host);
			if (it != hashCircle_.end())
			{
				// ��һ���Թ�ϣ����ɾ����������������Ӧ������ڵ�
				hashCircle_.erase(it);
			}
		}
	}

	// ���ظ��ص���ʵ����������ip��Ϣ
	string getHost(const string& clientIp) const
	{
		uint md5 = getMD5(clientIp.c_str());
		for (auto vhost : hashCircle_)
		{
			if (vhost.get_md5() > md5)
			{
				return vhost.getPhscialHost()->getIp();
			}
		}

		// ӳ���0��ʼ�����ĵ�һ������ڵ�
		return hashCircle_.begin()->getPhscialHost()->getIp();
	}

private:
	set<VirtualHost> hashCircle_;  // һ���Թ�ϣ��
};

void ShowConsistentHash(ConsistentHash& chash);

// ����һ���Թ�ϣ�㷨�Ĺ���
int main()
{
	PhscialHost host1("10.117.124.10", 150);
	PhscialHost host2("10.117.124.20", 150);
	PhscialHost host3("10.117.124.30", 150);

	ConsistentHash chash;
	chash.addHost(host1);
	chash.addHost(host2);
	chash.addHost(host3);

	ShowConsistentHash(chash);

	// ģ��host1�й���
	chash.delHost(host1);

	ShowConsistentHash(chash);
}

void ShowConsistentHash(ConsistentHash& chash)
{
	list<string> iplists{
		"192.168.1.123",
		"192.168.1.12",
		"192.168.1.13",
		"192.168.1.23",
		"192.168.1.54",
		"192.168.1.89",
		"192.168.1.21",
		"192.168.1.27",
		"192.168.1.49",
		"192.168.1.145",
		"192.168.2.34",
		"192.168.6.78",
		"192.168.2.90",
		"192.168.4.5"
	};

	map<string, list<string>> logMap;

	for (auto clientip : iplists)
	{
		string host = chash.getHost(clientip);
		logMap[host].emplace_back(clientip);
	}

	for (auto pair : logMap)
	{
		cout << "��������:" << pair.first << endl;
		cout << "�ͻ���ӳ�������:" << pair.second.size() << endl;

		for (auto ip : pair.second)
		{
			cout << ip << endl;
		}

		cout << "----------------------------" << endl;
	}
	cout << endl;
}