#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* 问题一：抽象类和普通类有什么区别？
* 抽象类有纯虚函数
* 
* 问题二：一般把什么类设计成抽象类？
* 基类
*/

/*
* 动物基类 泛指 类->抽象一个实体的类型
* 定义Animal的初衷，并不是让Animal抽象某一个实体类型
* 1.string name_；让所有动物实体类通过继承Animal直接复用该属性；
* 2.给所有派生类保留统一的覆盖/重写接口
* 
* 拥有纯虚函数的类，叫做抽象类；
* 抽象类不能再实例化对象了，但是可以定义指针和引用变量；
* Animal animal；NO!
*/

#if 0
class Animal
{
public:
	Animal(const string& name) :name_(name) {}
	// 纯虚函数
	virtual void bark() = 0;
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


// 汽车的基类
class Car
{
public:
	Car(const string& name, double oil) :name_(name),oil_(oil) {}

	// 获取汽车剩余油量还能跑的公里数
	double getLeftMiles()
	{
		return oil_ * getMilesPerGallon();  // 发生动态绑定
	}

	string getName() const { return name_; }
protected:
	virtual double getMilesPerGallon() = 0;  // 纯虚函数
protected:
	string name_;
	double oil_;
};

class Benz : public Car
{
public:
	Benz(const string& name, double oil) :Car(name, oil) {}

	double getMilesPerGallon() { return 20.0; }
};

class Audi : public Car
{
public:
	Audi(const string& name, double oil) :Car(name, oil) {}
	double getMilesPerGallon() { return 18.0; }
};

class BMW : public Car
{
public:
	BMW(const string& name, double oil) :Car(name, oil) {}
	double getMilesPerGallon() { return 19.0; }
};

// 给外部提供一个统一的获取汽车剩余里程数的API
double showCarLeftMiles(Car& car)
{
	cout << car.getName() << " left miles: " << car.getLeftMiles() << "公里。" << endl;
	return car.getLeftMiles();  // 静态绑定 call Car::getLeftMiles()
}

int main()
{
	Benz bz("奔驰", 20.0);
	Audi ad("奥迪", 20.0);
	BMW bm("宝马", 20.0);

	showCarLeftMiles(bz);
	showCarLeftMiles(ad);
	showCarLeftMiles(bm);

	return 0;
}
#endif