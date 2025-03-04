#include <iostream>
#include <typeinfo>

using namespace std;


/*
* 虚函数，静态绑定，动态绑定
* 
* 一个类添加了虚函数，对这个类有什么影响？
* 总结：
* 1.一个类里面定义了虚函数，那么编译阶段，编译器会给这个类类型产生一个唯一的vftable虚函数表，
*   虚函数表中主要存储的内容就是RTTI指针和虚函数地址，当程序运行时，每一张虚函数表会被加载到
*   内存的.rodata（只读）区域；
* 
* 2.一个类里面定义了虚函数，那么这个类定义的对象，其运行时，内存中开始的部分，多存储一个vfptr虚函数指针
*   ，指向相应类型的虚函数表vftable，一个类型定义的n个对象，它们的vfptr指向的都是同一张虚函数表；
* 
* 3.一个类里面虚函数的个数，不影响对象内存的大小（vfptr），影响的是虚函数表的大小；
* 
* 4.如果派生类中的方法，和基类继承来的某个方法，返回值，函数名，参数列表都相同，而且基类的方法是virtual虚函数，
*   那么派生类的这个方法自动处理成虚函数，覆盖的关系（虚函数表中虚函数地址的覆盖）；
*/

#if 0
class Base
{
public:
	Base(int data=10):ma(data){}
	virtual void show() { cout << "Base::show()" << endl; }
	virtual void show(int) { cout << "Base::show(int)" << endl; }
protected:
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
	Derive d(50);
	Base* pb = &d;
	/*
	* pb->Base Base::show 如果发现show是普通函数，就进行静态绑定
	* call Base::show (07FF70A7C13F7h)
	* 
	* pb->Base Base::show 如果发现show是虚函数，就进行动态绑定
	* mov eax, dword ptr[pb]
	* mov ecx, dword ptr[eax]
	* call ecx(虚函数地址) 动态（运行时期）的绑定（函数调用）
	*/
	pb->show();
	pb->show(10);

	cout << sizeof(Base) << endl;    // 4 8
	cout << sizeof(Derive) << endl;  // 8 12

	cout << typeid(pb).name() << endl;  // class Base*

	/*
	* pb的类型：Base -> 有没有虚函数
	* 如果Base没有虚函数，*pb识别的就是编译时期的类型 *pb <=> Base类型
	* 如果Base有虚函数，*pb识别的就是运行时期的类型 RTTI类型
	*/
	cout << typeid(*pb).name() << endl; // class Base
	return 0;
}
#endif