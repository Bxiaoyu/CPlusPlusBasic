#include <iostream>
#include <memory>
#include <functional>

using namespace std;

/*
* 智能指针的删除器 deletor
* 智能指针：能够确保资源的绝对释放 delete ptr；
* 
~unique_ptr() { 是一个函数对象的调用 deletor(ptr); }
template<typename T>
class Deletor
{
public:
	void operator()(T* ptr)
	{
		delete ptr;
	}
};
*/

#if 0
// 自定义函数对象，删除器
template<typename T>
class MyDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyDeletor.operator()" << endl;
		delete[] ptr;
	}
};

template<typename T>
class MyFileDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyFileDeletor.operator()" << endl;
		fclose(ptr);
	}
};


int main()
{
	unique_ptr<int, MyDeletor<int>> ptr1(new int[100]);
	unique_ptr<FILE, MyFileDeletor<FILE>> ptr2(fopen("data.txt", "w"));

	// 使用lambda表达式来简化代码
	// lambda -> 函数对象 function
	unique_ptr<int, function<void(int*)>> ptr3(new int[100],
		[](int* p)->void
		{
			cout << "call lambda release new int[100]" << endl;
			delete[] p;
		});

	unique_ptr<FILE, function<void(FILE*)>> ptr4(fopen("data.txt", "w"),
		[](FILE* p)->void
		{
			cout << "call lambda release fopen()" << endl;
			fclose(p);
		});

	shared_ptr<int> ptr5(new int[10],
		[](int* p)->void
		{
			cout << "call lambda release new int[10]" << endl;
			delete[] p;
		});

	return 0;
}
#endif