#include <iostream>
#include <memory>

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
*/

#if 0
class B;

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void show() { cout << "hello!" << endl; }
public:
	//shared_ptr<B> _ptrb;
	weak_ptr<B> _ptrb;  // 引用对象的地方用弱智能指针
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	void func()
	{
		//_ptra->show();  // 错误，weak_ptr并不能直接访问资源
		shared_ptr<A> ps = _ptra.lock();  // 提升方法，提升为shared_ptr才行
		if (ps != nullptr)
		{
			ps->show();
		}
	}
public:
	//shared_ptr<A> _ptra;
	weak_ptr<A> _ptra;  // 引用对象的地方用弱智能指针
};

int main()
{
	shared_ptr<A> pa(new A());  // 定义对象的时候用强智能指针
	shared_ptr<B> pb(new B());  // 定义对象的时候用强智能指针

	// 循环引用
	pa->_ptrb = pb;
	pb->_ptra = pa;

	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;
	pb->func();

	return 0;
}
#endif