#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 问题一：哪些函数不能实现成虚函数？
* 先明白虚函数依赖：
* 1.虚函数能产生地址，存储在vftable中；
* 2.对象必须存在（vfptr->vftable->虚函数地址）；
* 
* 构造函数 NO
* 1.virtual+构造函数 NO!
* 2.构造函数中（调用的任何函数，都是静态绑定）调用虚函数，也不会发生静态绑定；
* 3.派生类构造过程：先调用基类构造，然后调用派生类构造；
* 
* static静态成员方法 NO
* 1.静态成员方法不依赖对象；
* 
* 问题二：虚析构函数
* 1.析构函数可以定义为虚函数，因为析构函数调用的时候，对象是存在的；
* 2.基类的析构函数是虚函数，那么派生类的析构函数自动成为虚函数；
* 
* 问题三：什么时候基类的析构函数必须实现成虚析构函数？
* 基类的指针（引用）指向堆上new出来的派生类对象的时候，delete pb(基类指针),
* 它调用析构函数的时候，必须发生动态绑定，否则会导致派生类的析构函数无法调用；
*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) 
	{
		cout << "Base()" << endl;
	}

	virtual ~Base()
	{
		cout << "~Base()" << endl;
	}

	virtual void show()
	{
		cout << "Call Base::show()" << endl;
	}
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data)
		: Base(data)
		, mb(data)
		, ptr(new int(data))
	{
		cout << "Derive()" << endl;
	}

	~Derive()
	{
		delete ptr;
		ptr = nullptr;
		cout << "~Derive()" << endl;
	}
private:
	int mb;
	int* ptr;
};

int main()
{
	Base* pb = new Derive(10);
	pb->show();  // 动态绑定 pb Base* *pb Derive
	delete pb;  // 没有定义基类虚析构的时候，派生类的析构函数没有被调用到！！！

	/*
	* pb->Base Base::~Base 对于析构函数的调用，就是静态绑定
	* call Base::~Base()
	* 
	* 将基类析构函数定义为虚析构后
	* pb->Base Base::~Base 对于析构函数的调用，就是动态绑定了
	* pb->Derive Derive vftable &Derive::~Derive
	*/

	/*
	Derive d(10);
	Base* pb = &d;
	pb->show();
	*/
	return 0;
}
#endif