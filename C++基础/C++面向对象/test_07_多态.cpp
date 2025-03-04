#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* 问题：如何理解多态？
* 1.静态（编译时期）的多态：函数重载，模板（函数模板和类模板）
* bool compare(int, int){}
* bool compare(double, double){}
* 
* compare(10,20); call compare_int_int  在编译阶段就确定好调用的函数版本
* compare(10.0, 20.0); call compare_double_double  在编译阶段就确定好调用的函数版本
* 
* template<typename T>
* bool compare(T a, T b){}
* 
* compare(10, 20); -> int 实例化一个compare<int>
* compare(10.0, 20.0); -> double 实例化一个compare<double>
* 
* 2.动态（运行时期）的多态：
* 在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数），基类指针指向哪个派生类对象，
* 就会调用哪个派生类对象的覆盖方法，成为多态。
* 多态底层是通过动态绑定来实现
* pbase -> 访问谁的vfptr -> 进而访问谁的vftable -> 当然调用的是对应的派生类对象的方法了
* 
* 问题二：继承的好处？
* 1.可以做代码的复用；
* 2.在基类中给所有派生类提供统一的虚函数接口，让派生类进行重写，然后就可以使用多态了；
*/

#if 0
// 动物基类
class Animal
{
public:
	Animal(const string& name) :name_(name) {}
	virtual void bark() {}
protected:
	string name_;
};

// 动物实体类
class Cat : public Animal
{
public:
	Cat(const string& name) :Animal(name) {}
	void bark() { cout << name_ << " bark: miao miao!" << endl; }
};

class Dog : public Animal
{
public:
	Dog(const string& name) :Animal(name) {}
	void bark() { cout << name_ << " bark: wang wang!" << endl; }
};

class Pig : public Animal
{
public:
	Pig(const string& name) :Animal(name) {}
	void bark() { cout << name_ << " bark: heng heng!" << endl; }
};

// 下面的函数遵循“开-闭”原则，对修改关闭，对扩展开放
void bark(Animal* p)
{
	p->bark();  // Animal::bark 虚函数，动态绑定
	/*
	* p->Cat Cat vftable &Cat::bark
	* p->Dog Dog vftable &Dog::bark
	* p->Pig Pig vftable &Pig::bark
	*/
}

int main()
{
	Cat cat("猫咪");
	Dog dog("士奇");
	Pig pig("佩奇");

	bark(&cat);
	bark(&dog);
	bark(&pig);

	return 0;
}
#endif