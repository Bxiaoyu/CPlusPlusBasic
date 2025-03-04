#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 虚函数和动态绑定
* 
* 问题一：是不是虚函数的调用一定是动态绑定？
* 1.不是的，比如在类的构造函数中调用虚函数，是静态绑定（构造函数中调用其它函数（虚），不会发生动态绑定）；
* 2.如果不是通过指针或者引用变量来调用虚函数，那就是静态绑定；
*/

#if 0
class Base
{
public:
	Base(int data = 0) :ma(data) {}
	virtual void show() { cout << "Base::show()" << endl; }
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 0) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Base b;
	Derive d;

	// 静态绑定 用对象本身调用虚函数，是静态绑定
	b.show();  // 虚函数 call Base::show
	d.show();  // 虚函数 call Derive::show

	// 动态绑定 必须由指针或引用调用虚函数
	Base* pb1 = &b;
	pb1->show();
	Base* pb2 = &d;
	pb2->show();
	
	// 动态绑定
	Base& rb1 = b;
	rb1.show();
	Base& rb2 = d;
	rb2.show();

	Derive* pd2 = (Derive*)&b;
	pd2->show();  // 动态绑定 pd2->b vfptr -> Base vftable Base::show

	return 0;
}
#endif