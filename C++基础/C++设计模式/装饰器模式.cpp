#include <iostream>
#include <memory>

using namespace std;

/*
* װ����ģʽ��Decorator��
* ͨ������ʵ�ֹ�����ǿ�����⣺
* Ϊ����ǿ������Ĺ��ܣ�ͨ��ʵ������ķ�ʽ����д�ӿڣ��ǿ�����ɹ�����չ�����Ǵ�������̫��������ӽ���
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
		cout << "�������ã���������";
	}
};

class Audi : public Car
{
public:
	void show()
	{
		cout << "�µϣ����ã���������";
	}
};

class Benz : public Car
{
public:
	void show()
	{
		cout << "���ۣ����ã���������";
	}
};

// װ����һ������Ѳ��
class ConcreteDecorator01 :public Car
{
public:
	ConcreteDecorator01(Car* p):pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "������Ѳ��";
	}
private:
	Car* pCar;
};

// װ���������Զ�ɲ��
class ConcreteDecorator02 :public Car
{
public:
	ConcreteDecorator02(Car* p) :pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "���Զ�ɲ��";
	}
private:
	Car* pCar;
};

// װ������������ƫ��
class ConcreteDecorator03 :public Car
{
public:
	ConcreteDecorator03(Car* p) :pCar(p) {}

	void show()
	{
		pCar->show();
		cout << "������ƫ��";
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