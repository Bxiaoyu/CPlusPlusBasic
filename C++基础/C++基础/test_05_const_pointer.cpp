#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 1、const和一级指针的结合:
* C++语法规范：const 修饰的是离它最近的类型；
* const右边如果没有指针"*"的话，const不参与类型；即int* const == int* 在编译器眼中是这样的；
* const int* p;  可以指向任意不同的int类型的内存，但是不能通过指针间接修改指向的内存的值；
* int const* p;  同上；
* int* const p;  不能再指向其它内存，但是可以通过指针解引用修改指向的内存的值；
* const int* const p;  不能再指向其它内存，也不可以通过指针解引用修改指向的内存的值；
* 
* 2、const和二级（多级）指针的结合：
* 
* const修饰的变量叫常量，和普通变量的区别是什么？
* C++有两点区别：1.编译方式不同；2.不能作为左值了
* 
* const修饰的量常出现的错误：
* 1.常量不能作为左值 《= 直接修改常量的值；
* 2.不能把常量的地址泄露给一个普通的指针或者普通的引用变量 《= 间接修改常量的值;
* 
* 总结const和指针的类型转换公式：
* int* <- const int*  是错误的！
* const int* <- int*  是可以的！
* 
* 二级指针下，要么都有const，要么都没有，否则错误
* int** <- const int**  是错误的！
* const int** <- int**  是错误的！
* 
* (int*const*)实际上是const和一级指针的结合
* int** <- int* const*  是错误的！
* int* const* <- int**  是可以的！
*/

#if 0
// const和一级指针的结合
int main01()
{
	int* q1 = nullptr;
	int* const q2 = nullptr;
	cout << typeid(q1).name() << endl;
	cout << typeid(q2).name() << endl;
	// const右边如果没有指针"*"的话，const不参与类型修饰；

	int a = 10;
	int* p1 = &a;
	const int* p2 = &a;  // const int* <- int*
	int* const p3 = &a;  // int* <- int*
	int* p4 = p3;  // int* <- int*

	//const int a = 10;
	//int* p = &a;  // *p = 30; int* <<= const int*;错误;
}

// const和二级指针的结合
int main()
{
	int a = 10;
	int* p = &a;
	const int** q = &p;  // const int** <- int**，错误

	return 0;
}
#endif