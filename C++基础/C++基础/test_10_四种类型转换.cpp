#include <iostream>

using namespace std;


/*
* C++���Լ����ṩ����������ת����ʽ��
* const_cast��ȥ����ָ��������ã��������Ե�����ת������const_cast<���������ָ������������� int* int&>��
* static_cast���ṩ��������Ϊ��ȫ������ת����û���κ���ϵ������֮���ת���ͱ����ˣ�����ã�
* reinterpret_cast��������C����ǿ������ת����
* dynamic_cast����Ҫ���ڼ̳нṹ�У�����֧��RTTI����ʶ�������ת����
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
	// ʵ���¹��ܵ�API�ӿں���������func()��������
	void derive2Func() { cout << "call Derive2::derive2Func()" << endl; }
};

void showFunc(Base* p)
{
	/*
	* dynamic_cast����pָ���Ƿ�ָ�����ͬһ��Derive2���͵Ķ���
	* p->vfptr->vftable RTTI��Ϣ������ǣ�dynamic_castת�����ͳɹ�������Derive2�����ַ�����򷵻�nullptr��
	* static_cast����ʱ�ڵ�����ת����
	* dynamic_cast����ʱ�ڵ�����ת����֧��RTTI
	*/
	Derive2* pd = dynamic_cast<Derive2*>(p);
	//Derive2* pd = static_cast<Derive2*>(p);  // static_castҲ��ת���ɹ���������Զ����ɹ����𲻵��ж����������
	if (pd != nullptr)
	{
		pd->derive2Func();  // ����Derive2�����¹���
	}
	else
	{
		p->func();  // ��̬��
	}
}

int main()
{
	Derive d1;
	Derive2 d2;

	showFunc(&d1);
	showFunc(&d2);

	// static_cast �������� ��-������������ �ܲ�����static_cast����Ȼ����
	//int* p = nullptr;
	//double* p1 = static_cast<double*>(p);
	//double* p2 = reinterpret_cast<double*>(p);

	//const int a = 10;
	//int* p = (int*)&a;  // C����ǿת
	//int* p1 = const_cast<int*>(&a);  // �ڻ��ָ���Ϻ�C���ǿתһ���������������޶�
	//int b = const_cast<int>(a);  // const_cast<���������ָ������������� int* int&>
}
#endif



