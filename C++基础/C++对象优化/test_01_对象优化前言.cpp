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
	* C++编译器对于对象的优化：用临时对象生成新对象时，临时对象就不产生了，直接构造新对象就可以了
	*/
	Test t4 = Test(20);  // 显示生成临时对象，和Test t4(20)没区别，生存周期：所在语句

	cout << "--------------------------------" << endl;
	// t4.operator=(t2)
	t4 = t2;
	// t4.operator=(const Test& t)
	t4 = Test(30);
	t4 = (Test)30;  // 隐式生成临时对象
	t4 = 30;  // 隐式转换生成临时对象 int Test(int)

	cout << "--------------------------------" << endl;
	//Test* p = &Test(40); // 错误
	// p指向的是一个已经析构的临时对象
	const Test& ref = Test(50);
}

Test t1(10, 10);  // 1.Test(int,int)
void test_02()
{
	Test t2(20, 20);  // 3.Test(int,int)
	Test t3 = t2;     // 4.Test(const Test&)
	static Test t4 = Test(30, 30);  // 5.Test(int,int)，相当于static Test t4(30,30)
	t2 = Test(40, 40);  // 6.Test(int,int) operator= ~Test()
	// (50,50)=(Test)50 逗号表达式
	t2 = (Test)(50, 50);  // 7.Test(int,int) operator= ~Test()
	t2 = 60;              // 8.Test(int,int) operator= ~Test()
	Test* p1 = new Test(70, 70);  // 9.Test(int,int)
	Test* p2 = new Test[2];  // 10.Test(int,int) Test(int,int)
	//Test* p3 = &Test(80, 80);  // 11.Test(int,int) ~Test()
	//Test& p4 = Test(90, 90);  // 错误
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