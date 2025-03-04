#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* 多重继承：代码复用 一个派生类有多个基类
* class C : public A, public B
* {
* };
* 
* 抽象类（有纯虚函数的类）
* 
* 虚基类
* virtual
* 1.修饰成员方法是虚函数
* 2.可以修饰继承方式，是虚继承，被虚继承的类称为虚基类
*/

#if 0
class A
{
public:
	virtual void func() { cout << "call A::func()" << endl; }
	void operator delete(void* ptr)
	{
		cout << "operator delete p:" << ptr << endl;
		free(ptr);
	}
private:
	int ma;
};

/*
* A a：4个字节
* B b：8个字节+4=12字节 vbptr
*/
class B : virtual public A  // 在这里A就被称为虚基类
{
public:
	void func() { cout << "call B::func()" << endl; }

	void* operator new(size_t size)
	{
		void* p = malloc(size);
		cout << "operator new p:" << p << endl;
		return p;
	}
private:
	int mb;
};

/*
* 类B内存布局，基类内存放置在派生类之后
*  _____
* |vbptr| -> 新增虚基类指针
* |mb   |
* |_____|
* |A::  | -> 虚基类部分
* |vfptr|
* |ma   |
*  _____
*/

int main()
{
	// 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
	//A* p = new B();
	//cout << "main p:" << p << endl;
	//p->func();
	//delete p;  // 此段代码在释放内存时会出错，会从基类地址开始释放而不是内存初始位置（VS编译器下有这个问题，G++下没有）

	B b;
	A* p = &b;
	cout << "main p:" << p << endl;
	p->func();

	return 0;
}
#endif