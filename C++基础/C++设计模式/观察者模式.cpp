#include <iostream>
#include <unordered_map>
#include <list>
#include <functional>
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

/*
* ����۲���ģʽʵ��
* �ù۲���ģʽ�Ǿ���ģʽ�����Ǵ���ȱ�ݣ�
��1����Ҫ�̳У��̳���ǿ�����ϵ��ֻ�ܶ��ض��Ĺ۲��߲���Ч����������Observer���������������У�

��2���۲��߱�֪ͨ�Ľӿڲ�����֧�ֱ仯�����¹۲��߲���Ӧ���ӿڵı仯����������۲��߻����ܴ����� ��
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


/*
* ʹ��C++11�Ľ�ʵ�ַ�ʽ
* C++11 ʵ�ֵĹ۲���ģʽ���ڲ�ά����һ�����ͺ����б��۲���ֻ��Ҫ���۲��ߺ���ע��������ɣ������˼̳е��µ�ǿ��ϡ�
* ֪ͨ�ӿ�ʹ���˿ɱ����ģ�壬֧����������������˽ӿڱ仯��Ӱ�졣

* �Ľ�֮��Ĺ۲���ģʽ��C# �е�event���ƣ�ͨ������ί���������޶��۲��ߣ���Ҫ��۲��߱���ĳ��������������Ҫ��ԭ����ͬ�Ĺ۲���ʱ��
* ֻ��Ҫ����һ���µ�event���ͼ��ɣ�ͨ��event���ɷ�������ӻ��Ƴ��۲��ߡ�
*/
#if 0
// ����������
class BaseSubject
{
public:
	BaseSubject(const BaseSubject&) = delete;
	BaseSubject& operator=(const BaseSubject&) = delete;
	BaseSubject() = default;
	~BaseSubject() = default;
};

// ����������
template<typename Func>
class Event : public BaseSubject
{
public:
	Event() 
		: observerId_(0)
	{
	}

	~Event() = default;

	// ע��۲��ߣ���ֵ
	int addObserver(const Func& f)
	{
		return assign(f);
	}

	// ע��۲��ߣ�֧����ֵ����
	int addObserver(Func&& f)
	{
		return assign(f);
	}

	// �Ƴ��۲���
	void removeObserver(int key)
	{
		observerMap_.erase(key);
	}

	// ֪ͨ���й۲���
	template<typename ...Args>
	void notify(Args&&... args)
	{
		for (auto& it : observerMap_)
		{
			auto& func = it.second;
			func(std::forward<Args>(args)...);
		}
	}

private:
	// ����۲��߲�����۲��߱��
	template<typename F>
	int assign(F&& f)
	{
		int k = observerId_++;
		observerMap_.emplace(k, std::forward<F>(f));
		return k;
	}

private:
	int observerId_;  // �۲��߱��
	unordered_map<int, Func> observerMap_;  // �۲����б�
};

// ���庯����ģ��
using observerFunc = std::function<int(int, int)>;

class Observer1
{
public:
	int operator()(int a, int b)
	{
		cout << "Observer����������¼�2������... �����";
		int res = a + b;
		cout << res << endl;
		return res;
	}
};

class Observer2
{
public:
	int observerFunc(int a, int b)
	{
		cout << "Observer��Ա�����¼�3������... �����";
		int res = a + b;
		cout << res << endl;
		return res;
	}
};

int globalObserverFunc(int a, int b)
{
	cout << "ȫ�ֵ�globalObserverFunc�¼�4������... �����";
	int res = a + b;
	cout << res << endl;
	return res;
}

int main()
{
	Event<observerFunc> event;

	// ����lambda���ʽ�Ĺ۲��ߺ���
	int id1 = event.addObserver([](int a, int b)->int
		{
			cout << "lambda�������¼�1������... �����";
			int res = a + b;
			cout << res << endl;
			return res;
		});

	// ���÷º����Ĺ۲��ߺ���
	int id2 = event.addObserver(Observer1());

	// ���ó�Ա�����Ĺ۲��ߺ���
	Observer2 obs2;
	int id3 = event.addObserver(std::bind(&Observer2::observerFunc, obs2, std::placeholders::_1, std::placeholders::_2));

	// ����ȫ�ֹ۲��ߺ���
	int id4 = event.addObserver(globalObserverFunc);

	event.notify(10, 20);

	// �Ƴ�1,3�Ź۲���
	cout << endl;
	event.removeObserver(id1);
	event.removeObserver(id3);

	event.notify(20, 30);

	return 0;
}
#endif