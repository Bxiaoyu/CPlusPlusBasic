#include <iostream>
#include <string>

using namespace std;

/*
* 简单工厂 Simple Factory
* 优点：把对象的创建封装在一个接口函数里,通过传入不同的标识，返回创建的对象，客户不用自己负责new对象，不用了解对象的详细创建过程；
* 缺点：提供创建对象的接口函数不闭合，不能对修改关闭；
* 
* 工厂方法 Factory Method
* 优点：Factory基类提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的产品，可以做到不同的产品在不同的工厂
*      创建，能够对现有的工厂和产品的修改关闭；
* 
* 缺点：实际上很多产品是有关联关系的，属于一个产品簇，不应该放在不同的工厂去创建，这样一是不符合实际产品对象的创建逻辑，二是工厂类太多
*      不好维护；
* 
* 抽象工厂 Abstract Factory
* 优点：把有关联的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里，派生类（具体产品工厂）应该负责创建该产品簇的所有产品，减少工厂类维护难度；
* 
* 缺点：所有派生类（具体工厂）必须重写所有抽象接口，否则自己也成了抽象类，有时候没必要；
* 
* 工厂模式：主要是封装了对象的创建
*/

// 系列产品1
class Car
{
public:
	Car(string name) : name_(name) {}
	virtual void show() = 0;
protected:
	string name_;
};

class BMW : public Car
{
public:
	BMW(string name) :Car(name) {}
	void show()
	{
		cout << "宝马:" << name_ << endl;
	}
};

class Audi : public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "奥迪:" << name_ << endl;
	}
};

// 系类产品2
class Light
{
public:
	virtual void show() = 0;
};

class BMWLight : public Light
{
public:
	void show() { cout << "BMW Light!" << endl; }
};

class AudiLight : public Light
{
public:
	void show() { cout << "Audi Light!" << endl; }
};


/*
* 简单工厂
*/
#if 0

/*
* 简单工厂
*/
enum class CarType
{
	EBMW,
	EAUDI
};

class SimpleFactory
{
public:
	Car* createCar(CarType type)
	{
		switch (type)
		{
		case CarType::EBMW:
			return new BMW("X1");
		case CarType::EAUDI:
			return new Audi("A6");
		default:
			cerr << "参数不正确！" << endl;
			break;
		}

		return nullptr;
	}
};

int main()
{
	//SimpleFactory* factory = new SimpleFactory();
	unique_ptr<SimpleFactory> factory = make_unique<SimpleFactory>();
	//Car* car1 = factory->createCar(CarType::EBMW);
	unique_ptr<Car> car1(factory->createCar(CarType::EBMW));
	//Car* car2 = factory->createCar(CarType::EAUDI);
	unique_ptr<Car> car2(factory->createCar(CarType::EAUDI));
	car1->show();
	car2->show();

	//delete car2;
	//delete car1;
	//delete factory;
	return 0;
}
#endif

/*
* 工厂方法
*/
#if 0
class Factory
{
public:
	virtual Car* createCar(const std::string& name) = 0;
};

class BMWFactory : public Factory
{
public:
	Car* createCar(const std::string& name)
	{
		return new BMW(name);
	}
};

class AudiFactory : public Factory
{
public:
	Car* createCar(const std::string& name)
	{
		return new Audi(name);
	}
};

int main()
{
	unique_ptr<Factory> bmwfty(new BMWFactory());
	unique_ptr<Factory> audifty(new AudiFactory());
	unique_ptr<Car> bmw(bmwfty->createCar("X6"));
	unique_ptr<Car> audi(audifty->createCar("A8"));
	bmw->show();
	audi->show();

	return 0;
}
#endif

/*
* 抽象工厂（对有一组关联关系的产品簇提供产品对象的统一创建）
*/
#if 0
class AbstractFactory
{
public:
	virtual Car* createCar(const std::string& name) = 0;  // 工厂方法 创建汽车
	virtual Light* createCarLight() = 0;  // 工厂方法 创建车灯
};

class BMWFactory : public AbstractFactory
{
public:
	Car* createCar(const std::string& name)
	{
		return new BMW(name);
	}

	Light* createCarLight()
	{
		return new BMWLight();
	}
};

class AudiFactory : public AbstractFactory
{
public:
	Car* createCar(const std::string& name)
	{
		return new Audi(name);
	}

	Light* createCarLight()
	{
		return new AudiLight();
	}
};

int main()
{
	unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	unique_ptr<AbstractFactory> audifty(new AudiFactory());
	unique_ptr<Car> bmw(bmwfty->createCar("X6"));
	unique_ptr<Car> audi(audifty->createCar("A8"));
	unique_ptr<Light> bmwLight(bmwfty->createCarLight());
	unique_ptr<Light> audiLight(audifty->createCarLight());
	bmw->show();
	bmwLight->show();
	audi->show();
	audiLight->show();
}
#endif