#include <iostream>

using namespace std;

/*
* 重载，隐藏，覆盖
* 1、重载关系
* - 一组函数要重载，必须处于同一个作用域中，而且函数名相同，参数列表不同；
* 
* 2、隐藏（作用域的隐藏）关系
* - 在继承结构当中，派生类的同名成员，把基类的同名成员给隐藏调用了；
* 
* 3、覆盖关系
* - 基类和派生类的方法，其返回值，函数名以及参数列表都相同，而且基类的方法是虚函数，
*   那么派生类的方法就自动处理成虚函数，它们之间成覆盖关系（虚函数表中虚函数地址的覆盖）；
* 
* ==============================================================
* 1、把继承结构，也说成从上（基类）到下（派生类）的结构
* 2、
* 
* 类型转换：
* 1.基类对象 -> 派生类对象（类型从上到下的转换） 不可以
* 2.派生类对象 -> 基类对象 （类型从下到上的转换）可以
* 
* 3.基类指针（引用）-> 派生类对象（类型从上到下的转换） 不可以
* 4.派生类指针（引用）-> 基类对象 （类型从下到上的转换）可以
* 
* 总结：在继承结构中进行上下的类型转换，默认只支持从下到上的类型转换
*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) {}
	void show() { cout << "Base::show()" << endl; }
	void show(int) { cout << "Base::show(int)" << endl; }
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Base b(10);
	Derive d(20);
	// 基类对象b <- 派生类对象d 类型从下到上的转换 Y
	b = d;

	// 派生类对象d <- 基类对象b 类型从上到下的转换 N
	//d = b;  // 错误

	// 基类指针（引用）<- 派生类对象 类型从下到上的转换 Y
	Base* pb = &d;
	pb->show();
	//((Derive*)pb)->show();
	pb->show(30);

	// 派生类指针（引用）<- 基类对象 类型从上到下的转换 N
	//Derive* pd = &b; // 错误
	Derive* pd = (Derive*)&b;  // 不安全，涉及内存的非法访问

#if 0
	Derive d;
	d.show();
	d.Base::show(10);  // 优先找的是派生类自己作用域的show名字成员，没有的话才去基类里面找
#endif
	return 0;
}
#endif