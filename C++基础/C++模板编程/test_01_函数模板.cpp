#include <iostream>

using namespace std;

/*
* C++函数模板:
* 模板意义：对类型也可以进行参数化；
* 
* 函数模板：
* - 不进行编译，因为类型还不知道；
* 模板的实例化：
* - 函数调用点进行实例化；
* 模板函数：
* - 真正要被编译器所编译的，如bool compare<int>(int a, int b)；
* 
* 模板类型参数 - typename/class
* 模板非类型参数：
* - 指定某一个具体类型，如template<typename T, int SIZE>
* - 必须是整数类型（整数或者地址/引用都可以），且都是常量，只能使用，不能修改，
* 
* 模板的实参推演：
* - 可以根据用户传入的实参类型，来推导出模板类型参数的具体类型
* 
* 模板的特例化（专用化）：
* - 对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是有错误的;
* - 所以需要特殊的实例化（不是编译器提供的，而是用户提供的）;
* 
* 函数模板、模板的特例化，非模板函数的重载关系？
* 
* 注意：
* 模板代码不能在一个文件中定义，在另一个文件中使用，模板代码调用之前，一定要看到模板定义的地方，
* 这样的话，模板才能进行正常的实例化，产生能够被编译器编译的代码；所以模板代码定义都是放在头文
* 件当中，然后在源文件中直接#include包含
*/
#if 0
// 函数模板、模板的特例化，非模板函数的重载关系，如下所示：
// 函数模板
template<typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

// 非模板函数 - 普通函数
bool compare(const char* a, const char* b)
{
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}

/*
* 在函数调用点，编译器根据用户指定的类型，从原模板实例化一份函数代码出来
* 模板函数
* bool compare<int>(int a, int b)
* {
*		return a > b;
* }
* 
* bool compare<double>(double a, double b)
* {
*		return a > b;
* }
* 
* bool compare<const char*>(const char* a, const char* b)
* {
*		// 不能使用编译器默认提供的 a > b;
*		return strcmp(a, b) > 0;
* }
*/


// 模板非类型参数演示：
// 实现一个冒泡排序
template<typename T, int SIZE>
void sort(T* arr)
{
	for (int i = 0; i < SIZE - 1; ++i)
	{
		for (int j = 0; j < SIZE - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				T tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	// 函数调用点
	compare<int>(10, 20);
	compare<double>(10, 20);

	// 函数模板实参推演
	compare(10, 20);
	//compare(10, 15.0);  // 错误
	compare<int>(10, 15.0);  // 会涉及到类型转换

	// 函数模板实参推演 T -> const char*
	// 对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是有错误的
	// 编译器优先把compare处理成函数名字，没有的话才去找compare模板
	compare("aaa", "bbb");  // 调用非模板函数
	compare<const char*>("aaa", "bbb");  // 调用模板函数

	// 模板非类型参数演示
	int arr[] = { 12,5,7,89,20,31 };
	const int size = sizeof(arr) / sizeof(arr[0]);
	sort<int, size>(arr);
	for (int val : arr)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
#endif