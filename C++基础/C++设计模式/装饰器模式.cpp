#include <iostream>
#include <memory>

using namespace std;

/*
* 装饰器模式（Decorator）
* 通过子类实现功能增强的问题：
* 为了增强现有类的功能，通过实现子类的方式，重写接口，是可以完成功能扩展，但是代码中有太多子类添加进来
*/
#if 0
class Car
{
public:
	virtual void show() = 0;
};

class BMW : public Car
{
public:
	void show()
	{
		cout << "宝马，配置：基本配置";
	}
};

class Audi : public Car
{
public:
	void show()
	{
		cout << "奥迪，配置：基本配置";
	}
};

class Benz : public Car
{
public:
	void show()
	{
		cout << "奔驰，配置：基本配置";
	}
};

// 装饰器一，定速巡航
class ConcreteDecorator01 :public Car
{
public:
	ConcreteDecorator01(Car* p):pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "，定速巡航";
	}
private:
	Car* pCar;
};

// 装饰器二，自动刹车
class ConcreteDecorator02 :public Car
{
public:
	ConcreteDecorator02(Car* p) :pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "，自动刹车";
	}
private:
	Car* pCar;
};

// 装饰器三，车道偏离
class ConcreteDecorator03 :public Car
{
public:
	ConcreteDecorator03(Car* p) :pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "，车道偏离";
	}
private:
	Car* pCar;
};

int main()
{
	Car* p1 = new ConcreteDecorator01(new BMW());
	p1 = new ConcreteDecorator02(p1);
	p1->show();
	cout << endl;

	Car* p2 = new ConcreteDecorator01(new Audi());
	p2 = new ConcreteDecorator03(p2);
	p2->show();
	cout << endl;

	Car* p3 = new ConcreteDecorator01(new Benz());
	p3 = new ConcreteDecorator02(p3);
	p3 = new ConcreteDecorator03(p3);
	p3->show();
	cout << endl;

	delete p1;
	delete p2;
	delete p3;

	return 0;
}
#endif