#include <iostream>
#include <memory>
#include <thread>

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
* 
* ���̷߳��ʹ��������̰߳�ȫ����
*/
#if 0
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "Hello!" << endl; }
};

void handler01(A* q)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	// q����A�����ʱ����Ҫ���һ��A�����Ƿ���
	q->testA();
}

void handler02(weak_ptr<A> pw)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	shared_ptr<A> p = pw.lock();  // ��������
	if (p != nullptr)
	{
		p->testA();
	}
	else
	{
		cout << "A�����Ѿ������������ٴη��ʣ�" << endl;
	}
}

int main()
{
	//A* p = new A();
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	//delete p;

	// ��������A��������
	{
		shared_ptr<A> p(new A());
		thread t(handler02, weak_ptr<A>(p));
		t.detach();
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	std::this_thread::sleep_for(std::chrono::seconds(20));
	// �����ȴ����߳̽���
	//t.join();

	return 0;
}
#endif