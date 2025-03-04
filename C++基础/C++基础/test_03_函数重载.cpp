#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 函数重载：
* 1、C++为什么支持函数重载，C语言不支持函数重载？
* C++代码产生函数符号时，由函数名+参数列表类型组成；
* C代码产生函数符号时，仅由函数名决定；
* 
* 2、函数重载需要注意些什么？
* 3、C++和C语言代码之间如何相互调用？
* C++调用C代码：无法直接调用，需要把C函数的声明包含在extern "C"里面;
* C调用C++代码：无法直接调用，需要把C++代码包含在extern "C"里面；
* 
* 什么是函数重载？
* 1）、一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就称作函数重载；
* 2）、一组函数要称得上重载，一定得先处在同一个作用域当中；
* 3）、const或者volatile的时候，是怎么影响形参类型的；
* 4）、一组函数，函数名相同，参数列表也相同，仅仅是返回值不同，不能叫重载；
* 
* 解释一下，什么是多态？
* 静态（编译时期）的多态：函数重载，函数模板
* 动态（运行时期）的多态：虚函数，虚函数表
*/

#if 0
#ifdef __cplusplus  // 如果是C++编译器（有__cplusplus宏），则生成C规则的符号；如果是C编译器（没有__cplusplus宏），直接生成C规则符号
extern "C" {
#endif
	int sum(int a, int b)
	{
		return a + b;
	}
#ifdef __cplusplus
}
#endif // __cplusplus
#endif



#if 0
// C++调用C代码
extern "C"
{
	// 函数申明，符号生成按C++规则来生成
	int sum(int a, int b);  // sum "UND"
}

// 供给C调用C++，在C中申明函数并调用即可
extern "C"
{
	int sum(int a, int b)  // 符号生成按C规则来生成
	{
		return a + b;
	}
}

int main()
{
	cout << "ret:" << sum(10, 20) << endl;
	return 0;
}
#endif

#if 0
void func(int a) {}
void func(const int a) {}

int main()
{
	int a = 10;
	const int b = 10;
	cout << typeid(a).name() << endl;  // int
	cout << typeid(b).name() << endl;  // int
}
#endif

#if 0
bool compare(int a, int b)  // compare_int_int
{
	cout << "compare_int_int" << endl;
	return a > b;
}

bool compare(double a, double b)  // compare_double_double
{
	cout << "compare_double_double" << endl;
	return a > b;
}

bool compare(const char* a, const char* b)  // compare_char*_char*
{
	cout << "compare_char*_char*" << endl;
	return strcmp(a, b) > 0;
}

int main()
{
	bool compare(int a, int b);  // 函数申明，全局的compare被局部compare覆盖

	compare(10, 20);
	compare(10.0, 20.0);  // double -> int
	compare("aaa", "bbb");  // const char* -> int
}
#endif