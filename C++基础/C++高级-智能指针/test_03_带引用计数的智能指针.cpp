#include <iostream>
#include <memory>

using namespace std;

/*
* 带引用计数的智能指针：多个智能指针可以管理同一个资源
* 怎么理解引用计数：
* 给每一个对象资源，匹配一个引用计数；
* 智能指针指向一个资源的时候，引用计数加一；
* 智能指针不使用资源的时候，引用计数减一；
* 当引用计数为0的时候，资源释放；
* 
* C++11标准：
* 这两个是线程安全的智能指针
* 1、shared_ptr：强智能指针
* 2、weak_ptr：弱智能指针
* 
* 联合使用：weak_ptr -》（观察）shared_ptr -》（观察）资源（内存）
*/

#if 0
// 自己实现引用计数类
template<typename T>
class RefCnt
{
public:
	RefCnt(T* ptr = nullptr)
		:mptr(ptr)
	{
		if (mptr != nullptr)
		{
			mcount = 1;
		}
	}

	void addRef() { mcount++; }  // 增加资源的引用计数

	int delRef() { return --mcount; }
private:
	T* mptr;
	int mcount;  // 建议使用atomic_int，可以用于多线程
};

// 实现简单的智能指针，增加引用计数
// 智能指针 保证做到资源的自动释放
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		: mptr(ptr)
	{
		mpRefCnt = new RefCnt<T>(mptr);
	}

	~CSmartPtr()
	{
		if (0 == mpRefCnt->delRef())
		{
			delete mptr;
			mptr = nullptr;
		}
	}

	CSmartPtr(const CSmartPtr<T>& src)
		: mptr(src.mptr)
		, mpRefCnt(src.mpRefCnt)
	{
		if (mptr != nullptr)
		{
			mpRefCnt->addRef();
		}
	}

	CSmartPtr<T>& operator=(const CSmartPtr<T>& src)
	{
		if (this == &src)
		{
			return *this;
		}

		if (0 == mpRefCnt->delRef())
		{
			delete mptr;
		}

		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}

	T& operator*() { return *mptr; }  // 返回的是可以改变的值

	T* operator->() { return mptr; }
private:
	T* mptr;  // 指向资源的指针
	RefCnt<T>* mpRefCnt;  // 指向该资源引用计数对象的指针
};

int main()
{
	CSmartPtr<int> ptr1(new int(10));
	CSmartPtr<int> ptr2(ptr1);
	CSmartPtr<int> ptr3;
	ptr3 = ptr2;

	*ptr1 = 20;
	cout << *ptr2 << " " << *ptr3 << endl;
	return 0;
}
#endif