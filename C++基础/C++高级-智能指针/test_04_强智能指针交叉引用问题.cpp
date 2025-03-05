#include <iostream>
#include <memory>

using namespace std;

/*
* �����ü���������ָ�룺�������ָ����Թ���ͬһ����Դ
* C++11��׼��
* ���������̰߳�ȫ������ָ��
* 1��shared_ptr��ǿ����ָ�룬���Ըı���Դ�����ü���
* 2��weak_ptr��������ָ�룬����ı���Դ�����ü�����ֻ�й۲����ü���������
*    weak_ptrû���ṩoperator*,operator->����������أ����Բ�����ֱ�ӷ�����Դ
*
* ����ʹ�ã�weak_ptr -�����۲죩shared_ptr -�����۲죩��Դ���ڴ棩
* 
* ǿ����ָ��ѭ�����ã��������ã���ʲô���⣿�����ʲô�������ô�����
* ���⣺
* - ���new��������Դ�޷��ͷţ������ڴ�й¶��
* �����
* - ��������ʱ����ǿ����ָ�룬���ö���ĵط���������ָ�룻
*/

#if 0
class B;

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void show() { cout << "hello!" << endl; }
public:
	//shared_ptr<B> _ptrb;
	weak_ptr<B> _ptrb;  // ���ö���ĵط���������ָ��
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	void func()
	{
		//_ptra->show();  // ����weak_ptr������ֱ�ӷ�����Դ
		shared_ptr<A> ps = _ptra.lock();  // ��������������Ϊshared_ptr����
		if (ps != nullptr)
		{
			ps->show();
		}
	}
public:
	//shared_ptr<A> _ptra;
	weak_ptr<A> _ptra;  // ���ö���ĵط���������ָ��
};

int main()
{
	shared_ptr<A> pa(new A());  // ��������ʱ����ǿ����ָ��
	shared_ptr<B> pb(new B());  // ��������ʱ����ǿ����ָ��

	// ѭ������
	pa->_ptrb = pb;
	pb->_ptra = pa;

	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;
	pb->func();

	return 0;
}
#endif