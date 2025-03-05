#include <iostream>
#include <memory>

using namespace std;

/*
* 智能指针介绍：
* 1、自己实现智能指针；
* 2、不带引用计数的智能指针auto_ptr(不推荐使用)，scoped_ptr（使用比较少），unique_ptr（推荐）；
* 3、带引用计数的智能指针shared_ptr，weak_ptr；
* 4、智能指针的交叉引用（循环引用）问题；
* 5、多线程访问共享对象问题；
* 6、自定义删除器；
*/

#if 0
// 实现简单的智能指针
// 智能指针 保证做到资源的自动释放
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		: mptr(ptr)
	{
	}

	~CSmartPtr()
	{
		delete mptr;
	}

	T& operator*() { return *mptr; }  // 返回的是可以改变的值

	T* operator->() { return mptr; }
private:
	T* mptr;
};

int main()
{
	/*
	* 不带引用计数的智能指针，如何解决浅拷贝问题？
	* auto_ptr:C++库里面的，不推荐使用，浅拷贝处理存在问题
	* 
	* C++11新标准：
	* scoped_ptr：不支持拷贝构造和拷贝赋值，不能进行函数传参和返回等，使用比较少
	* - scoped_ptr(const scoped_ptr<T>&) = delete;
	* - scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;
	* 
	* unique_ptr：推荐使用
	* 也不支持普通拷贝构造和拷贝运算符重载
	* - unique_ptr(const unique_ptr<T>&) = delete;
	* - unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	* 
	* 但是提供了带右值引用参数的拷贝构造和拷贝运算符重载
	* - unique_ptr(unique_ptr<T>&&);
	* - unique_ptr<T>& operator=(unique_ptr<T>&&);
	*/
	//CSmartPtr<int> ptr(new int(10));

	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;
	//cout << *ptr1 << endl;

	unique_ptr<int> ptr1(new int);
	// std::move -> c++11 右值引用 std::move得到当前变量的右值类型
	unique_ptr<int> ptr2(std::move(ptr1));
	return 0;
}
#endif