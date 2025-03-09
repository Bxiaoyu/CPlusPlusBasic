#include <iostream>
#include <string>

using namespace std;

/*
* �򵥹��� Simple Factory
* �ŵ㣺�Ѷ���Ĵ�����װ��һ���ӿں�����,ͨ�����벻ͬ�ı�ʶ�����ش����Ķ��󣬿ͻ������Լ�����new���󣬲����˽�������ϸ�������̣�
* ȱ�㣺�ṩ��������Ľӿں������պϣ����ܶ��޸Ĺرգ�
* 
* �������� Factory Method
* �ŵ㣺Factory�����ṩ��һ�����麯����������Ʒ�������������ࣨ�����Ʒ�Ĺ��������𴴽���Ӧ�Ĳ�Ʒ������������ͬ�Ĳ�Ʒ�ڲ�ͬ�Ĺ���
*      �������ܹ������еĹ����Ͳ�Ʒ���޸Ĺرգ�
* 
* ȱ�㣺ʵ���Ϻܶ��Ʒ���й�����ϵ�ģ�����һ����Ʒ�أ���Ӧ�÷��ڲ�ͬ�Ĺ���ȥ����������һ�ǲ�����ʵ�ʲ�Ʒ����Ĵ����߼������ǹ�����̫��
*      ����ά����
* 
* ���󹤳� Abstract Factory
* �ŵ㣺���й����ģ�����һ����Ʒ�ص����в�Ʒ�����Ľӿں���������һ�����󹤳�������ࣨ�����Ʒ������Ӧ�ø��𴴽��ò�Ʒ�ص����в�Ʒ�����ٹ�����ά���Ѷȣ�
* 
* ȱ�㣺���������ࣨ���幤����������д���г���ӿڣ������Լ�Ҳ���˳����࣬��ʱ��û��Ҫ��
* 
* ����ģʽ����Ҫ�Ƿ�װ�˶���Ĵ���
*/

// ϵ�в�Ʒ1
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
		cout << "����:" << name_ << endl;
	}
};

class Audi : public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "�µ�:" << name_ << endl;
	}
};

// ϵ���Ʒ2
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
* �򵥹���
*/
#if 0

/*
* �򵥹���
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
			cerr << "��������ȷ��" << endl;
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
* ��������
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
* ���󹤳�������һ�������ϵ�Ĳ�Ʒ���ṩ��Ʒ�����ͳһ������
*/
#if 0
class AbstractFactory
{
public:
	virtual Car* createCar(const std::string& name) = 0;  // �������� ��������
	virtual Light* createCarLight() = 0;  // �������� ��������
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