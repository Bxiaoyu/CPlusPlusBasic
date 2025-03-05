#include <iostream>
#include <memory>

using namespace std;

/*
* 不带引用计数的智能指针，如何解决浅拷贝问题？
* auto_ptr:C++库里面的，不推荐使用，浅拷贝处理存在问题
*
* C++11新标准：
* 1、scoped_ptr：不支持拷贝构造和拷贝赋值，不能进行函数传参和返回等，使用比较少
* - scoped_ptr(const scoped_ptr<T>&) = delete;
* - scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;
*
* 2、unique_ptr：推荐使用
* 也不支持普通拷贝构造和拷贝运算符重载
* - unique_ptr(const unique_ptr<T>&) = delete;
* - unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
*
* 但是提供了带右值引用参数的拷贝构造和拷贝运算符重载
* - unique_ptr(unique_ptr<T>&&);
* - unique_ptr<T>& operator=(unique_ptr<T>&&);
*/

#if 0
int main()
{
	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;  // 错误
	//cout << *ptr1 << endl;

	unique_ptr<int> ptr1(new int);
	// std::move -> c++11 右值引用 std::move得到当前变量的右值类型
	unique_ptr<int> ptr2(std::move(ptr1));
	return 0;
}
#endif