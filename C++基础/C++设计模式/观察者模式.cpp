#include <iostream>
#include <unordered_map>
#include <list>
#include <functional>
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

/*
* 经典观察者模式实现
* 该观察者模式是经典模式，但是存在缺陷：
（1）需要继承，继承是强对象关系，只能对特定的观察者才有效，即必须是Observer抽象类的派生类才行；

（2）观察者被通知的接口参数不支持变化，导致观察者不能应付接口的变化，并且这个观察者还不能带参数 ；
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


/*
* 使用C++11改进实现方式
* C++11 实现的观察者模式，内部维护了一个泛型函数列表，观察者只需要将观察者函数注册进来即可，消除了继承导致的强耦合。
* 通知接口使用了可变参数模板，支持任意参数，消除了接口变化的影响。

* 改进之后的观察者模式和C# 中的event类似，通过定义委托类型来限定观察者，不要求观察者必须某个类派生，当需要和原来不同的观察者时，
* 只需要定义一个新的event类型即可，通过event还可方便地增加或移除观察者。
*/
#if 0
// 抽象主题类
class BaseSubject
{
public:
	BaseSubject(const BaseSubject&) = delete;
	BaseSubject& operator=(const BaseSubject&) = delete;
	BaseSubject() = default;
	~BaseSubject() = default;
};

// 具体主题类
template<typename Func>
class Event : public BaseSubject
{
public:
	Event() 
		: observerId_(0)
	{
	}

	~Event() = default;

	// 注册观察者，左值
	int addObserver(const Func& f)
	{
		return assign(f);
	}

	// 注册观察者，支持右值引用
	int addObserver(Func&& f)
	{
		return assign(f);
	}

	// 移除观察者
	void removeObserver(int key)
	{
		observerMap_.erase(key);
	}

	// 通知所有观察者
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
	// 保存观察者并分配观察者编号
	template<typename F>
	int assign(F&& f)
	{
		int k = observerId_++;
		observerMap_.emplace(k, std::forward<F>(f));
		return k;
	}

private:
	int observerId_;  // 观察者编号
	unordered_map<int, Func> observerMap_;  // 观察者列表
};

// 定义函数类模板
using observerFunc = std::function<int(int, int)>;

class Observer1
{
public:
	int operator()(int a, int b)
	{
		cout << "Observer函数对象的事件2被调用... 结果：";
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
		cout << "Observer成员函数事件3被调用... 结果：";
		int res = a + b;
		cout << res << endl;
		return res;
	}
};

int globalObserverFunc(int a, int b)
{
	cout << "全局的globalObserverFunc事件4被调用... 结果：";
	int res = a + b;
	cout << res << endl;
	return res;
}

int main()
{
	Event<observerFunc> event;

	// 调用lambda表达式的观察者函数
	int id1 = event.addObserver([](int a, int b)->int
		{
			cout << "lambda函数的事件1被调用... 结果：";
			int res = a + b;
			cout << res << endl;
			return res;
		});

	// 调用仿函数的观察者函数
	int id2 = event.addObserver(Observer1());

	// 调用成员函数的观察者函数
	Observer2 obs2;
	int id3 = event.addObserver(std::bind(&Observer2::observerFunc, obs2, std::placeholders::_1, std::placeholders::_2));

	// 调用全局观察者函数
	int id4 = event.addObserver(globalObserverFunc);

	event.notify(10, 20);

	// 移除1,3号观察者
	cout << endl;
	event.removeObserver(id1);
	event.removeObserver(id3);

	event.notify(20, 30);

	return 0;
}
#endif