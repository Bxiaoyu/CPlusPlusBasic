#include <iostream>
#include <typeinfo>

using namespace std;

/*
* new和delete
* - malloc和free，称作C的库函数;
* - new和delete，称作运算符;
* 
* 
* 1、new和malloc的区别是什么？
* a.malloc按字节开辟内存，new开辟内存时需要指定类型（如new int[10]），所以malloc开辟内存返回的是void*，
*	而new开辟内存返回数据类型指针（如int*）；
* b.malloc只负责开辟内存空间，new不仅有malloc的功能，还可以进行数据初始化（如 new int(20), new int[20]()）；
* c.malloc开辟内存失败返回nullptr指针，new分配内存失败则抛出bad_alloc类型的异常；
* 
* 2、delete和free的区别是什么？
* delete：先调用析构，再free；（如 delete (int*)p;free(p)）
* 
* new -> operator new
* delete -> operator delete
* 
* 3、new和delete能混用吗？C++为什么区分单个元素和数组的内存分配和释放呢？
* new-delete
* new[]-delete[]
* a.对于普通的编译器内置类型，new/delete[] new[]/delete可以混用，但是也不推荐;
* b.自定义的类类型，有析构函数，为了调用正确的析构函数，编译器在开辟对象数组的时候会多开辟4字节（32位下），记录对象的个数，
*	这种情况下不能混用；
* c.为了编码安全和编码规范，不推荐混用；
*/

#if 0
void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new addr:" << p << endl;
	return p;
}

void operator delete(void* ptr)
{
	cout << "operator delete addr:" << ptr << endl;
	free(ptr);
}

void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new[] addr:" << p << endl;
	return p;
}

void operator delete[](void* ptr)
{
	cout << "operator delete[] addr:" << ptr << endl;
	free(ptr);
}


class Test
{
public:
	Test(int data = 10)
	{
		cout << "Test()" << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int ma;
};


int main()
{
	Test* t = new Test();
	delete[] t;  // 错误

	Test* t1 = new Test[5];
	delete[] t1;
#if 0
	try
	{
		int* p = new int;
		delete p;

		int* p1 = new int[10];
		delete[] p1;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
#endif

#if 0
	// new有多少种
	int* p1 = new int(20);
	int* p2 = new (nothrow) int;
	const int* p3 = new const int(40);
	// 定位new
	int data = 0;
	int* p4 = new (&data)int(50);
	cout << "data:" << data << endl;
#endif

#if 0
	int* p = (int*)malloc(sizeof(int));
	if (p == nullptr)
	{
		return -1;
	}
	*p = 20;
	free(p);

	int* p1 = new int(20);
	delete p1;

	// 数组
	int* q = (int*)malloc(sizeof(int) * 20);
	if (q == nullptr)
	{
		return -1;
	}
	free(q);

	//int* q1 = new int[20];  // 只开辟内存
	int* q1 = new int[20]();  // 20个int，sizeof(int)*20;开辟内存并初始化
	delete[] q1;
#endif

	return 0;
}
#endif