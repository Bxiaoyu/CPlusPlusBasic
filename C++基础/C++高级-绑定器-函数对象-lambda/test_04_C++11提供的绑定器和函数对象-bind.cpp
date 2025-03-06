#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
* C++11提供的绑定器和函数对象
* 绑定器，函数对象，lambda表达式 它们只能使用在一条语句中
*
* 1、bind 绑定器 -> 返回的结果还是一个函数对象
* bind是函数模板
*/


/*
* bind简单使用
*/
#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

class Test
{
public:
	int sum(int a, int b) { return a + b; }

	static int sum2(int a, int b) { return a + b; }
};

int main()
{
	// 1、bind是函数模板，可以自动推演模板类型参数
	// 直接绑定参数
	bind(hello, "Hello world!")();
	cout << bind(sum, 10, 20)() << endl;
	cout << bind(&Test::sum, Test(), 10, 20)() << endl;  // 调用成员函数必须要用对象调用
	cout << bind(&Test::sum2, 10, 20)() << endl;

	cout << "--------------" << endl;
	// 2、使用参数占位符
	bind(hello, placeholders::_1)("Hello world2!");
	cout << bind(sum, placeholders::_1, placeholders::_2)(10, 20) << endl;
	cout << bind(&Test::sum, placeholders::_1, placeholders::_2, placeholders::_3)(Test(), 10, 20) << endl;
	cout << bind(&Test::sum2, placeholders::_1, placeholders::_2)(10, 20) << endl;

	// 只使用绑定器的话，绑定器出了语句无法继续使用，需要配合function函数对象
	// 用function把bind返回的绑定器binder复用起来
	cout << "--------------" << endl;
	function<void(string)> func1 = bind(hello, placeholders::_1);
	func1("Hello ShangHai!");
	func1("Hello YunNan!");
	func1("Hello BeiJing!");
	return 0;
}
#endif

/*
* 具体实例，结合function和bind实现一个简单线程池
*/
#if 0
// 线程类
class Thread
{
public:
	Thread(function<void()> func)
		: _pfunc(func)
	{
	}

	thread start()
	{
		thread t(_pfunc);  // _pfunc()
		return t;
	}
private:
	function<void()> _pfunc;
};

// 线程池类
class ThreadPool
{
public:
	ThreadPool() {}
	~ThreadPool() 
	{
		// 释放Thread对象的堆资源
		for (int i = 0; i < _pool.size(); ++i)
		{
			delete _pool[i];
		}
	}

	void startPool(int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, i)));
		}

		for (int i = 0; i < size; i++)
		{
			_handler.push_back(_pool[i]->start());
		}

		for (auto& t : _handler)
		{
			t.join();
		}
	}

private:
	// 把runInThread这个成员方法充当成员函数
	void runInThread(int id)
	{
		cout << "call runInThread! id:" << id << endl;
	}
private:
	vector<Thread*> _pool;
	vector<thread> _handler;
};

int main()
{
	ThreadPool pool;
	pool.startPool(10);

	return 0;
}
#endif