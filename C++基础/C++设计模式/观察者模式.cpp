#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>

using namespace std;

/*
* 行为型模式：主要关注的是对象间的通信
* 观察者 - 监听者模式（发布-订阅模式）：主要关注的是对象的一对多关系，也就是多个对象都依赖一个对象，当该对象的状态发生改变时
*                                  其它对象都能接收到相应的通知；
* 
* 一组数据（对象）-》通过这一组数据-》曲线图（对象1）/柱状图（对象2）/饼图（对象3）
* 当数据对象改变时，对象1，对象2，对象3应该及时收到相应的通知
* 
* Observer1    Observer2    Observer3
*              Subject（主题）主题有更改，应该及时通知相应的观察者，去处理相应事件
*/

#if 0
// 观察者抽象类
class Observer
{
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
};

// 第一个观察者实例
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

// 主题类
class Subject
{
public:
	void addObserver(Observer* observer, int msgid)
	{
		// 以下两种写法都可
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

	// 主题检测发生变化，通知相应的观察者对象处理事件
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
		cout << "输入消息id：";
		cin >> msgid;
		if (msgid == -1)
		{
			break;
		}
		sub.dispatch(msgid);
	}
}

#endif