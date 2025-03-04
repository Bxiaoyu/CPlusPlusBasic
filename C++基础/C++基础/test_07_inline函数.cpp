#include <iostream>
#include <typeinfo>

using namespace std;

/*
* inline内联函数 和 普通函数的区别？？
* 1.inline内联函数在编译过程中，没有函数调用开销，在函数的调用点把函数的代码进行展开处理了；
* 2.inline函数不再生成相应的函数符号；
* 
* inline只是建议编译器把这个函数处理成内联函数
* 但不是所有的inline都会被编译器处理成内联函数，比如递归函数；
* 
* debug版本下，inline是不起作用的，只有在release版本下起作用；
* 
* inline适合于简单函数；
*/

#if 0
inline int sum(int a, int b = 20)  // 编译器不再生成sum_int_int函数符号
{
	return a + b;
}

int sum2(int a, int b)  // sum2_int_int
{
	return a + b;
}

int main()
{
	int a = 30;
	int b = 40;

	int ret = sum(a, b);  // 直接展开成a+b，少了函数调用开销
	cout << "ret:" << ret << endl;

	ret = sum2(a, b);
	// 此处有函数的标准调用过程 参数压栈，函数栈帧的开辟和回退过程
	// 有函数调用的开销
	// a+b mov add mov 1000000 a+b
	cout << "ret:" << ret << endl;

	return 0;
}
#endif