#include <iostream>

using namespace std;

class Test
{
public:
	// Test() Test(10) Test(10,10)
	Test(int a = 10, int b = 20) :ma(a),mb(b) { cout << "Test(int,int)" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test& t) :ma(t.ma),mb(t.mb) { cout << "Test(const Test& t)" << endl; }
	Test& operator=(const Test& t) 
	{ 
		cout << "Test& operator=(const Test& t)" << endl;
		ma = t.ma;
		mb = t.mb;
		return *this;
	}
private:
	int ma;
	int mb;
};

void test_01()
{
	Test t1;
	Test t2(t1);
	Test t3 = t1;

	/*
	* C++���������ڶ�����Ż�������ʱ���������¶���ʱ����ʱ����Ͳ������ˣ�ֱ�ӹ����¶���Ϳ�����
	*/
	Test t4 = Test(20);  // ��ʾ������ʱ���󣬺�Test t4(20)û�����������ڣ��������

	cout << "--------------------------------" << endl;
	// t4.operator=(t2)
	t4 = t2;
	// t4.operator=(const Test& t)
	t4 = Test(30);
	t4 = (Test)30;  // ��ʽ������ʱ����
	t4 = 30;  // ��ʽת��������ʱ���� int Test(int)

	cout << "--------------------------------" << endl;
	//Test* p = &Test(40); // ����
	// pָ�����һ���Ѿ���������ʱ����
	const Test& ref = Test(50);
}

Test t1(10, 10);  // 1.Test(int,int)
void test_02()
{
	Test t2(20, 20);  // 3.Test(int,int)
	Test t3 = t2;     // 4.Test(const Test&)
	static Test t4 = Test(30, 30);  // 5.Test(int,int)���൱��static Test t4(30,30)
	t2 = Test(40, 40);  // 6.Test(int,int) operator= ~Test()
	// (50,50)=(Test)50 ���ű��ʽ
	t2 = (Test)(50, 50);  // 7.Test(int,int) operator= ~Test()
	t2 = 60;              // 8.Test(int,int) operator= ~Test()
	Test* p1 = new Test(70, 70);  // 9.Test(int,int)
	Test* p2 = new Test[2];  // 10.Test(int,int) Test(int,int)
	//Test* p3 = &Test(80, 80);  // 11.Test(int,int) ~Test()
	//Test& p4 = Test(90, 90);  // ����
	const Test& p4 = Test(90, 90);  // 12.Test(int,int)
	delete p1;  // 13.~Test()
	delete[] p2;  // 14.~Test() ~Test()
}
Test t5(100, 100); // 2.Test(int,int)

int main()
{
	test_02();
	return 0;
}