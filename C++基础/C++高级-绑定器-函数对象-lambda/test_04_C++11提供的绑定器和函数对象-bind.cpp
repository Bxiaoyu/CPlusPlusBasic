#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
* C++11�ṩ�İ����ͺ�������
* ��������������lambda���ʽ ����ֻ��ʹ����һ�������
*
* 1��bind ���� -> ���صĽ������һ����������
* bind�Ǻ���ģ��
*/


/*
* bind��ʹ��
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
	// 1��bind�Ǻ���ģ�壬�����Զ�����ģ�����Ͳ���
	// ֱ�Ӱ󶨲���
	bind(hello, "Hello world!")();
	cout << bind(sum, 10, 20)() << endl;
	cout << bind(&Test::sum, Test(), 10, 20)() << endl;  // ���ó�Ա��������Ҫ�ö������
	cout << bind(&Test::sum2, 10, 20)() << endl;

	cout << "--------------" << endl;
	// 2��ʹ�ò���ռλ��
	bind(hello, placeholders::_1)("Hello world2!");
	cout << bind(sum, placeholders::_1, placeholders::_2)(10, 20) << endl;
	cout << bind(&Test::sum, placeholders::_1, placeholders::_2, placeholders::_3)(Test(), 10, 20) << endl;
	cout << bind(&Test::sum2, placeholders::_1, placeholders::_2)(10, 20) << endl;

	// ֻʹ�ð����Ļ���������������޷�����ʹ�ã���Ҫ���function��������
	// ��function��bind���صİ���binder��������
	cout << "--------------" << endl;
	function<void(string)> func1 = bind(hello, placeholders::_1);
	func1("Hello ShangHai!");
	func1("Hello YunNan!");
	func1("Hello BeiJing!");
	return 0;
}
#endif

/*
* ����ʵ�������function��bindʵ��һ�����̳߳�
*/
#if 0
// �߳���
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

// �̳߳���
class ThreadPool
{
public:
	ThreadPool() {}
	~ThreadPool() 
	{
		// �ͷ�Thread����Ķ���Դ
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
	// ��runInThread�����Ա�����䵱��Ա����
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