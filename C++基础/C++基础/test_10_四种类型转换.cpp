#include <iostream>

using namespace std;


/*
* C++语言级别提供的四种类型转换方式：
* const_cast：去掉（指针或者引用）常量属性的类型转换，且const_cast<这里必须是指针或者引用类型 int* int&>；
* static_cast：提供编译器认为安全的类型转化（没有任何联系的类型之间的转换就被否定了），最常用；
* reinterpret_cast：类似于C风格的强制类型转换；
* dynamic_cast：主要用在继承结构中，可以支持RTTI类型识别的上下转换；
*/

#if 0
class Base
{
public:
	virtual void func() = 0;
};

class Derive : public Base
{
public:
	void func() { cout << "call Derive::func()" << endl; }
};

class Derive2 : public Base
{
public:
	void func() { cout << "call Derive2::func()" << endl; }
	// 实现新功能的API接口函数，假设func()函数废弃
	void derive2Func() { cout << "call Derive2::derive2Func()" << endl; }
};

void showFunc(Base* p)
{
	/*
	* dynamic_cast会检查p指针是否指向的是同一个Derive2类型的对象，
	* p->vfptr->vftable RTTI信息，如果是，dynamic_cast转换类型成功，返回Derive2对象地址，否则返回nullptr。
	* static_cast编译时期的类型转换；
	* dynamic_cast运行时期的类型转换，支持RTTI
	*/
	Derive2* pd = dynamic_cast<Derive2*>(p);
	//Derive2* pd = static_cast<Derive2*>(p);  // static_cast也能转换成功，但是永远都会成功，起不到判定对象的作用
	if (pd != nullptr)
	{
		pd->derive2Func();  // 对于Derive2调用新功能
	}
	else
	{
		p->func();  // 动态绑定
	}
}

int main()
{
	Derive d1;
	Derive2 d2;

	showFunc(&d1);
	showFunc(&d2);

	// static_cast 积累类型 《-》派生类类型 能不能用static_cast？当然可以
	//int* p = nullptr;
	//double* p1 = static_cast<double*>(p);
	//double* p2 = reinterpret_cast<double*>(p);

	//const int a = 10;
	//int* p = (int*)&a;  // C风格的强转
	//int* p1 = const_cast<int*>(&a);  // 在汇编指令上和C风格强转一样，但是类型有限定
	//int b = const_cast<int>(a);  // const_cast<这里必须是指针或者引用类型 int* int&>
}
#endif



