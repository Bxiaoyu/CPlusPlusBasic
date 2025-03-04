#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

/*
* ���ؼ̳У����븴�� һ���������ж������
* class C : public A, public B
* {
* };
* 
* �����ࣨ�д��麯�����ࣩ
* 
* �����
* virtual
* 1.���γ�Ա�������麯��
* 2.�������μ̳з�ʽ������̳У�����̳е����Ϊ�����
*/

#if 0
class A
{
public:
	virtual void func() { cout << "call A::func()" << endl; }
	void operator delete(void* ptr)
	{
		cout << "operator delete p:" << ptr << endl;
		free(ptr);
	}
private:
	int ma;
};

/*
* A a��4���ֽ�
* B b��8���ֽ�+4=12�ֽ� vbptr
*/
class B : virtual public A  // ������A�ͱ���Ϊ�����
{
public:
	void func() { cout << "call B::func()" << endl; }

	void* operator new(size_t size)
	{
		void* p = malloc(size);
		cout << "operator new p:" << p << endl;
		return p;
	}
private:
	int mb;
};

/*
* ��B�ڴ沼�֣������ڴ������������֮��
*  _____
* |vbptr| -> ���������ָ��
* |mb   |
* |_____|
* |A::  | -> ����ಿ��
* |vfptr|
* |ma   |
*  _____
*/

int main()
{
	// ����ָ��ָ�������������Զָ�������������ಿ�����ݵ���ʼ��ַ
	//A* p = new B();
	//cout << "main p:" << p << endl;
	//p->func();
	//delete p;  // �˶δ������ͷ��ڴ�ʱ�������ӻ����ַ��ʼ�ͷŶ������ڴ��ʼλ�ã�VS����������������⣬G++��û�У�

	B b;
	A* p = &b;
	cout << "main p:" << p << endl;
	p->func();

	return 0;
}
#endif