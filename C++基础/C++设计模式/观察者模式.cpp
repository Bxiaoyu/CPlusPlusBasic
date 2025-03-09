#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>

using namespace std;

/*
* ��Ϊ��ģʽ����Ҫ��ע���Ƕ�����ͨ��
* �۲��� - ������ģʽ������-����ģʽ������Ҫ��ע���Ƕ����һ�Զ��ϵ��Ҳ���Ƕ����������һ�����󣬵��ö����״̬�����ı�ʱ
*                                  ���������ܽ��յ���Ӧ��֪ͨ��
* 
* һ�����ݣ�����-��ͨ����һ������-������ͼ������1��/��״ͼ������2��/��ͼ������3��
* �����ݶ���ı�ʱ������1������2������3Ӧ�ü�ʱ�յ���Ӧ��֪ͨ
* 
* Observer1    Observer2    Observer3
*              Subject�����⣩�����и��ģ�Ӧ�ü�ʱ֪ͨ��Ӧ�Ĺ۲��ߣ�ȥ������Ӧ�¼�
*/

#if 0
// �۲��߳�����
class Observer
{
public:
	// ������Ϣ�Ľӿ�
	virtual void handle(int msgid) = 0;
};

// ��һ���۲���ʵ��
class Observer1 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer1 recv 1 msg." << endl;
			break;
		case 2:
			cout << "Observer1 recv 2 msg." << endl;
			break;
		default:
			cout << "Observer1 recv unknow msg." << endl;
			break;
		}
	}
};

class Observer2 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 2:
			cout << "Observer1 recv 2 msg." << endl;
			break;
		default:
			cout << "Observer1 recv unknow msg." << endl;
			break;
		}
	}
};

class Observer3 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer1 recv 1 msg." << endl;
			break;
		case 3:
			cout << "Observer1 recv 3 msg." << endl;
			break;
		default:
			cout << "Observer1 recv unknow msg." << endl;
			break;
		}
	}
};

// ������
class Subject
{
public:
	void addObserver(Observer* observer, int msgid)
	{
		// ��������д������
		_subMap[msgid].push_back(observer);

		//auto it = _subMap.find(msgid);
		//if (it != _subMap.end())
		//{
		//	_subMap[msgid].push_back(observer);
		//}
		//else
		//{
		//	list<Observer*> lst;
		//	lst.push_back(observer);
		//	_subMap.insert({ msgid, lst });
		//}
	}

	// �����ⷢ���仯��֪ͨ��Ӧ�Ĺ۲��߶������¼�
	void dispatch(int msgid)
	{
		auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			for (Observer* p : it->second)
			{
				p->handle(msgid);
			}
		}
	}
private:
	unordered_map<int, list<Observer*>> _subMap;
};

int main()
{
	Subject sub;

	Observer* p1 = new Observer1();
	Observer* p2 = new Observer2();
	Observer* p3 = new Observer3();

	sub.addObserver(p1, 1);
	sub.addObserver(p1, 2);
	sub.addObserver(p2, 2);
	sub.addObserver(p3, 1);
	sub.addObserver(p3, 3);

	int msgid = 0;
	for (;;)
	{
		cout << "������Ϣid��";
		cin >> msgid;
		if (msgid == -1)
		{
			break;
		}
		sub.dispatch(msgid);
	}
}

#endif