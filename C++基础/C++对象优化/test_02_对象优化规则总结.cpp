#include <iostream>

using namespace std;

/*
* 对象优化规则：
* 1、函数参数传递过程中，对象优先按引用传递，不要按值传递，可以减少实参到形参的拷贝构造和函数结束后对象析构；
* 2、函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象；
* 3、接收返回值是对象的函数调用的时候，优先按初始化的方式接收，不要按赋值的方式接收；
*/
#if 0
class Test
{
public:
	Test(int data = 10) : ma(data)
	{
		cout << "Test(int)" << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}

	Test(const Test& t) :ma(t.ma)
	{
		cout << "Test(const Test& t)" << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}

	int getData() const { return ma; }
private:
	int ma;
};

#if 0
Test getObject(Test t)  // 不能返回局部的或者临时对象的指针或引用
{
	int val = t.getData();
	Test tmp(val);  // 4.Test(int)
	return tmp;  // 5.Test(const Test&)  构造一个main函数栈帧上的临时对象并返回
	// 6.tmp -> ~Test()
	// 7.t -> ~Test()
}

int main()
{
	Test t1;  // 1.Test(int)
	Test t2;  // 2.Test(int)
	/*
	* 3.getObject(t1) -> Test(const Test&)形参到实参的初始化
	* 8.operator=
	* 9.返回的临时对象 -> ~Test()
	*/
	t2 = getObject(t1);
	// 10.t2 -> ~Test()
	// 11.t1 -> ~Test()

	return 0;
}
#endif	

// 优化：参数按引用传递，返回临时对象
Test getObject(const Test& t)
{
	int val = t.getData();
	// 返回临时对象
	// 2.Test(int) 直接构造
	return Test(val);  // 直接在main函数栈帧上构造一个临时对象，简化先构造临时对象，再拷贝构造到main函数栈帧临时对象的过程
}

int main()
{
	Test t1;  // 1.Test(int)
	Test t2 = getObject(t1);  // 临时对象拷贝构造同类型的新对象t2，临时对象不产生，也不用析构
	// 3. t2 -> ~Test()
	// 4. t1 -> ~Test()
	return 0;
}
#endif