#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* ����һ�����������ͨ����ʲô����
* �������д��麯��
* 
* �������һ���ʲô����Ƴɳ����ࣿ
* ����
*/

/*
* ������� ��ָ ��->����һ��ʵ�������
* ����Animal�ĳ��ԣ���������Animal����ĳһ��ʵ������
* 1.string name_�������ж���ʵ����ͨ���̳�Animalֱ�Ӹ��ø����ԣ�
* 2.�����������ౣ��ͳһ�ĸ���/��д�ӿ�
* 
* ӵ�д��麯�����࣬���������ࣻ
* �����಻����ʵ���������ˣ����ǿ��Զ���ָ������ñ�����
* Animal animal��NO!
*/

#if 0
class Animal
{
public:
	Animal(const string& name) :name_(name) {}
	// ���麯��
	virtual void bark() = 0;
protected:
	string name_;
};

// ����ʵ����
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


// �����Ļ���
class Car
{
public:
	Car(const string& name, double oil) :name_(name),oil_(oil) {}

	// ��ȡ����ʣ�����������ܵĹ�����
	double getLeftMiles()
	{
		return oil_ * getMilesPerGallon();  // ������̬��
	}

	string getName() const { return name_; }
protected:
	virtual double getMilesPerGallon() = 0;  // ���麯��
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

// ���ⲿ�ṩһ��ͳһ�Ļ�ȡ����ʣ���������API
double showCarLeftMiles(Car& car)
{
	cout << car.getName() << " left miles: " << car.getLeftMiles() << "���" << endl;
	return car.getLeftMiles();  // ��̬�� call Car::getLeftMiles()
}

int main()
{
	Benz bz("����", 20.0);
	Audi ad("�µ�", 20.0);
	BMW bm("����", 20.0);

	showCarLeftMiles(bz);
	showCarLeftMiles(ad);
	showCarLeftMiles(bm);

	return 0;
}
#endif