#include <iostream>

using namespace std;

/*
* 问题一、模板的完全特例化和非完全（部分）特例化
* 问题二、模板的实参推演（基本概念很简单）
* 
* 注意区分函数类型和函数指针类型：
* 函数类型：
* - typedef int PFUNC2(int, int); // 老的写法
* - using PFUNC2 = int(int, int); // C++11中使用using的写法
* 
* 函数指针类型：
* - typedef int(*PFUNC1)(int, int);
* - using PFUNC1 = int(*)(int, int);
*/


/*
* 模板简单使用
*/
#if 0
template<typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

int main()
{
	compare(10, 20);
	compare("aaa", "bbb");

	return 0;
}
#endif


/*
* 问题一、模板的完全特例化和非完全（部分）特例化
* 
* 代码演示
* 
*/
#if 0
template<typename T>
class Vector
{
public:
	Vector() { cout << "call Vector template init" << endl; }
};

// 针对char*类型提供的完全特例化版本
template<>
class Vector<char*>
{
public:
	Vector() { cout << "call Vector(char*) init" << endl; }
};

// 针对指针类型提供的部分特例化版本
template<typename Ty>
class Vector<Ty*>
{
public:
	Vector() { cout << "call Vector<Ty*> init" << endl; }
};

// 针对函数指针类型（有返回值，有两个形参变量）提供的部分特例化版本
template<typename R, typename A1>
class Vector < R(*)(A1, A1) >
{
public:
	Vector() { cout << "Vector < R(*)(A1, A1) >" << endl; }
};

// 针对函数类型（有一个返回值，有两个形参变量）提供的部分特例化版本
template<typename R, typename A1, typename A2>
class Vector<R(A1, A2)>
{
public:
	Vector() { cout << "Vector<R(A1, A2)>" << endl; }
};

int sum(int a, int b) { return a + b; }

int main()
{
	Vector<int> vec1;
	Vector<char*> vec2;
	Vector<int*> vec3;
	Vector<int(*)(int, int)> vec4;
	Vector<int(int, int)> vec5;

	// 函数指针类型
	//typedef int(*PFUNC1)(int, int);  // 用老的typedef定义
	using PFUNC1 = int(*)(int, int);  // 使用c++11的using关键字定义
	PFUNC1 pfunc = sum;
	cout << pfunc(10, 29) << endl;

	// 函数类型
	//typedef int PFUNC2(int, int);
	using PFUNC2 = int(int, int);  // 使用c++11的using关键字
	PFUNC2* pfunc2 = sum;
	cout << (*pfunc2)(10, 29) << endl;

	return 0;
}
#endif

/*
* 问题二、模板的实参推演（基本概念很简单）
* 更灵活
* 
* 
* 代码演示
* 
*/
#if 0
// T包含了所有大的类型，返回值，所有形参类型都取出来
template<typename T>
void func(T a)
{
	cout << typeid(a).name() << endl;
}

template<typename R, typename A1, typename A2>
void func2(R(*a)(A1,A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

int sum(int a, int b) { return a + b; }

class Test
{
public:
	int sum(int a, int b) { return a + b; }
};

template<typename R, typename T, typename A1, typename A2>
void func3(R(T::* a)(A1, A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(T).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

int main()
{
	func(10);
	func("aaa");
	func(sum);  // T int(*)(int,int)
	func2(sum);
	func3(&Test::sum);
	return 0;
}
#endif
