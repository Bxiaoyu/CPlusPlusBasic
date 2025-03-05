#include <iostream>
#include <memory>

using namespace std;

/*
* �����ü���������ָ�룺�������ָ����Թ���ͬһ����Դ
* ��ô������ü�����
* ��ÿһ��������Դ��ƥ��һ�����ü�����
* ����ָ��ָ��һ����Դ��ʱ�����ü�����һ��
* ����ָ�벻ʹ����Դ��ʱ�����ü�����һ��
* �����ü���Ϊ0��ʱ����Դ�ͷţ�
* 
* C++11��׼��
* ���������̰߳�ȫ������ָ��
* 1��shared_ptr��ǿ����ָ��
* 2��weak_ptr��������ָ��
* 
* ����ʹ�ã�weak_ptr -�����۲죩shared_ptr -�����۲죩��Դ���ڴ棩
*/

#if 0
// �Լ�ʵ�����ü�����
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

	void addRef() { mcount++; }  // ������Դ�����ü���

	int delRef() { return --mcount; }
private:
	T* mptr;
	int mcount;  // ����ʹ��atomic_int���������ڶ��߳�
};

// ʵ�ּ򵥵�����ָ�룬�������ü���
// ����ָ�� ��֤������Դ���Զ��ͷ�
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷ�
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

	T& operator*() { return *mptr; }  // ���ص��ǿ��Ըı��ֵ

	T* operator->() { return mptr; }
private:
	T* mptr;  // ָ����Դ��ָ��
	RefCnt<T>* mpRefCnt;  // ָ�����Դ���ü��������ָ��
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