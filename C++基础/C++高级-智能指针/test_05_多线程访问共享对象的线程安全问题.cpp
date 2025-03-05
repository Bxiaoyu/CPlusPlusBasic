#include <iostream>
#include <memory>
#include <thread>

using namespace std;

/*
* 带引用计数的智能指针：多个智能指针可以管理同一个资源
* C++11标准：
* 这两个是线程安全的智能指针
* 1、shared_ptr：强智能指针，可以改变资源的引用计数
* 2、weak_ptr：弱智能指针，不会改变资源的引用计数，只有观察引用计数的作用
*    weak_ptr没有提供operator*,operator->的运算符重载，所以并不能直接访问资源
*
* 联合使用：weak_ptr -》（观察）shared_ptr -》（观察）资源（内存）
*
* 强智能指针循环引用（交叉引用）是什么问题？会造成什么结果？怎么解决？
* 问题：
* - 造成new出来的资源无法释放，导致内存泄露；
* 解决：
* - 定义对象的时候用强智能指针，引用对象的地方用弱智能指针；
* 
* 多线程访问共享对象的线程安全问题
*/
#if 0
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "Hello!" << endl; }
};

void handler01(A* q)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	// q访问A对象的时候，需要侦测一下A对象是否存活
	q->testA();
}

void handler02(weak_ptr<A> pw)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	shared_ptr<A> p = pw.lock();  // 提升方法
	if (p != nullptr)
	{
		p->testA();
	}
	else
	{
		cout << "A对象已经析构，不能再次访问！" << endl;
	}
}

int main()
{
	//A* p = new A();
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	//delete p;

	// 出作用域，A对象析构
	{
		shared_ptr<A> p(new A());
		thread t(handler02, weak_ptr<A>(p));
		t.detach();
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	std::this_thread::sleep_for(std::chrono::seconds(20));
	// 阻塞等待子线程结束
	//t.join();

	return 0;
}
#endif