#include <iostream>

using namespace std;


/*
* 派生类的构造过程:
* 派生类怎么初始化从基类继承来的成员变量呢？
* 1.派生类从基类可以继承来所有的成员（变量和方法），除了构造函数和析构函数；
* 2.通过调用基类相应的构造函数来初始化基类；
* 3.派生类的构造函数和析构函数，负责初始化和清理派生类的部分，派生类从基类继承的成员，由基类的构造和析构负责初始化和清理；
* 
* 派生类对象构造和析构的过程是：
* 1.派生类调用基类的构造函数，初始化从基类继承来的成员；
* 2.派生类调用自己的构造函数，初始化自己特有的成员；
* -----析构
* 3.调用派生类的析构函数，释放派生类成员可能占用的外部资源（堆内存，文件）;
* 4.调用基类的析构函数，释放派生类内存中从基类继承来的成员可能占用的外部资源（堆内存，文件）;
*/

#if 0
class Base
{
public:
	Base(int data) 
		: ma(data)
	{
		cout << "Base()" << endl;
	}

	~Base()
	{
		cout << "~Base()" << endl;
	}
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data)
		: Base(data)
		, mb(data)
	{
		cout << "Derive()" << endl;
	}

	~Derive()
	{
		cout << "~Derive()" << endl;
	}

private:
	int mb;
};

int main()
{
	Derive d(20);

	return 0;
}
#endif