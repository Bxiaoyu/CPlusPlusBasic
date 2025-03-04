#include <iostream>
#include <typeinfo>

using namespace std;

/*
* C++的引用和指针的区别：
* 1、左值引用和右值引用；
* 2、引用的实例；
* 
* 引用是一种更安全的指针：
* 1、引用必须初始化，指针可以不初始化；
* 2、引用只有一级引用，没有多级引用，指针可以有一级指针，也可以有多级指针；
* 3、定义一个引用变量和定义一个指针变量，其汇编指令是一模一样的；通过引用变量修改
* 所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层指令也是一样的；
* 
* 右值引用：
* 1、int &&c = 20; 专门用来引用右值类型，指令上可以自动产生临时量，然后直接引用临时量 c = 40;
* 2、右值引用变量本身是一个左值，只能用左值引用来引用它；
* 不能用一个右值引用变量来引用一个左值；
*/

#if 0
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void test_p()
{
	int array[5] = {};
	int* p = array;
	// 定义一个引用变量来引用array数组
	int(&q)[5] = array;

	cout << sizeof(array) << endl;  // 20
	cout << sizeof(p) << endl;  // 8
	cout << sizeof(q) << endl;  // 20
}

void test_ref()
{
	int a = 10;  // 左值，有内存有名字，值秀嘎
	int& b = a;

	//int& c = 20;  // 20是右值：没有内存，没有名字
	// C++11提供了右值引用
	int&& c = 20;
	c = 30;  // 能更改

	int& e = c; // 一个右值引用变量，本身是一个左值
	//int&& s = c;  // 错误

	/*
	* int temp = 20;
	* temp -> d
	*/
	const int& d = 20;  // 汇编指令和上面的int&& c = 20一样
}

int main()
{
	int a = 10;
	int b = 20;
	swap(&a, &b);
	cout << "a:" << a << " b:" << b << endl;
	swap(a, b);
	cout << "a:" << a << " b:" << b << endl;

	test_p();
	test_ref();
	return 0;
}
#endif