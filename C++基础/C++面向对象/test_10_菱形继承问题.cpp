#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* C++的多重继承：
* 好处，可以做更多代码复用；
* 
* 菱形继承问题：
* 导致派生类有多份间接基类的数据，属于设计问题；
* 解决：用虚继承
*/

class A
{
public:
	A(int data) :ma(data) { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
protected:
	int ma;
};

class B : virtual public A
{
public:
	B(int data) : A(data), mb(data) { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
protected:
	int mb;
};

class C : virtual public A
{
public:
	C(int data) :A(data), mc(data) { cout << "C()" << endl; }
	~C() { cout << "~C()" << endl; }
protected:
	int mc;
};

class D : public B, public C
{
public:
	D(int data) :A(data), B(data), C(data), md(data) { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
protected:
	int md;
};

int main()
{
	D d(10);

	return 0;
}