#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* ���⣺�������̬��
* 1.��̬������ʱ�ڣ��Ķ�̬���������أ�ģ�壨����ģ�����ģ�壩
* bool compare(int, int){}
* bool compare(double, double){}
* 
* compare(10,20); call compare_int_int  �ڱ���׶ξ�ȷ���õ��õĺ����汾
* compare(10.0, 20.0); call compare_double_double  �ڱ���׶ξ�ȷ���õ��õĺ����汾
* 
* template<typename T>
* bool compare(T a, T b){}
* 
* compare(10, 20); -> int ʵ����һ��compare<int>
* compare(10.0, 20.0); -> double ʵ����һ��compare<double>
* 
* 2.��̬������ʱ�ڣ��Ķ�̬��
* �ڼ̳нṹ�У�����ָ�루���ã�ָ�����������ͨ����ָ�루���ã�����ͬ�����Ƿ������麯����������ָ��ָ���ĸ����������
* �ͻ�����ĸ����������ĸ��Ƿ�������Ϊ��̬��
* ��̬�ײ���ͨ����̬����ʵ��
* pbase -> ����˭��vfptr -> ��������˭��vftable -> ��Ȼ���õ��Ƕ�Ӧ�����������ķ�����
* 
* ��������̳еĺô���
* 1.����������ĸ��ã�
* 2.�ڻ����и������������ṩͳһ���麯���ӿڣ��������������д��Ȼ��Ϳ���ʹ�ö�̬�ˣ�
*/

#if 0
// �������
class Animal
{
public:
	Animal(const string& name) :name_(name) {}
	virtual void bark() {}
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

// ����ĺ�����ѭ����-�ա�ԭ�򣬶��޸Ĺرգ�����չ����
void bark(Animal* p)
{
	p->bark();  // Animal::bark �麯������̬��
	/*
	* p->Cat Cat vftable &Cat::bark
	* p->Dog Dog vftable &Dog::bark
	* p->Pig Pig vftable &Pig::bark
	*/
}

int main()
{
	Cat cat("è��");
	Dog dog("ʿ��");
	Pig pig("����");

	bark(&cat);
	bark(&dog);
	bark(&pig);

	return 0;
}
#endif