#include <iostream>

using namespace std;

/*
* 类模板 -》实现一个C++ STL里面的顺序容器 vector 向量容器
* 容器：
* 空间配置器allocator:
* template <class _Ty, class _Alloc = allocator<_Ty>>
* class vector
* 
* 容器的空间配置器allocator做四件事：
* 1.内存开辟；
* 2.内存释放；
* 3.对象构造；
* 4.对象析构；
*/

// 定义容器空间配置器，与C++标准库的allocator实现一样
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // 负责开辟内存
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // 负责释放内存
	{
		free(p);
	}

	void construct(T* p, const T& val)   // 负责对象构造
	{
		new (p) T(val);  // 定位new
	}

	void destroy(T* p)  // 负责对象析构
	{
		p->~T();  // ~T()代表T类型的析构函数
	}
};

/*
* 容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器来实现
*/
template<typename T, typename Alloc = Allocator<T>>
class Vector
{
public:

	Vector(int size = 10)
	{
		// 需要把内存开辟和对象构造分开处理
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		last_ = first_;
		end_ = first_ + size;
	}

	~Vector()
	{
		// 析构容器有效的元素，然后释放first_指针指向的堆内存
		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);  // 把first_指针指向的数组的有效元素进行析构操作
		}
		allocator_.deallocate(first_);  // 释放堆上的数组内存
		first_ = last_ = end_ = nullptr;
	}

	Vector(const Vector<T>& rhs)
	{
		int size = rhs.end_ - rhs.first_;
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		int len = rhs.last_ - rhs.first_;
		for (int i = 0; i < len; ++i)
		{
			//first_[i] = rhs.first_[i];
			allocator_.construct(first_ + i, rhs.first_[i]);
		}
		last_ = first_ + len;
		end_ = first_ + size;
	}

	Vector<T>& operator=(const Vector<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);  // 把first_指针指向的数组的有效元素进行析构操作
		}
		allocator_.deallocate(first_);  // 释放堆上的数组内存

		int size = rhs.end_ - rhs.first_;
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		int len = rhs.last_ - rhs.first_;
		for (int i = 0; i < len; ++i)
		{
			//first_[i] = rhs.first_[i];
			allocator_.construct(first_ + i, rhs.first_[i]);
		}
		last_ = first_ + len;
		end_ = first_ + size;

		return *this;
	}

	void push_back(const T& val)
	{
		if (full())
		{
			expand();
		}

		//*last_++ = val;  // last_指针指向的内存构造一个值为val的对象
		allocator_.construct(last_, val);
		last_++;
	}

	void pop_back()
	{
		if (empty())
		{
			return;
		}

		//--last_;  // 不仅要把last_指针--，还需要析构删除的元素
		--last_;
		allocator_.destroy(last_);
	}

	T back() const
	{
		if (empty())
		{
			throw "vector is empty!";
		}

		return *(last_ - 1);
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException";
		}
		return first_[index];
	}

	bool full() const { return last_ == end_; }
	bool empty() const { return first_ == last_; }
	int size() const { return last_ - first_; }

	// 提供迭代器，迭代器一般实现成容器的嵌套类型
	class iterator
	{
	public:
		iterator(T* p = nullptr) 
			: p_(p)
		{
		}

		bool operator!=(const iterator& it) const
		{
			return p_ != it.p_;
		}

		// 重载前置++运算符，对于对象，一般前置++效率高，避免产生临时量
		void operator++()
		{
			++p_;
		}

		T& operator*()
		{
			return *p_;
		}
	private:
		T* p_;
	};

	// begin返回的是容器底层首元素的迭代器表示
	iterator begin()
	{
		return iterator(first_);
	}

	// end返回的是容器末尾元素后继位置的迭代器表示
	iterator end()
	{
		return iterator(last_);
	}
private:
	void expand()
	{
		int size = end_ - first_;
		//T* ptmp = new T[2 * size];
		T* ptmp = allocator_.allocate(2 * size);
		for (int i = 0; i < size; ++i)
		{
			//ptmp[i] = first_[i];
			allocator_.construct(ptmp + i, first_[i]);
		}

		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);
		}
		allocator_.deallocate(first_);
		first_ = ptmp;
		last_ = first_ + size;
		end_ = first_ + 2 * size;
	}
private:
	T* first_;  // 指向数组起始的位置
	T* last_;   // 指向数组中有效元素的后继位置
	T* end_;    // 指向数组空间的后继位置
	Alloc allocator_;  // 定义容器的空间配置器对象
};

class Test
{
public:
	Test() { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
};

int main()
{
	Vector<int> v1;
	for (int i = 0; i < 20; ++i)
		v1.push_back(rand() % 100);

	//v1.pop_back();

	while (!v1.empty())
	{
		cout << v1.back() << " ";
		v1.pop_back();
	}
	cout << endl;

	cout << "--------------------" << endl;
	Test t1, t2, t3;
	Vector<Test> v2;
	v2.push_back(t1);
	v2.push_back(t2);
	v2.push_back(t3);
	cout << "---------------------" << endl;
	v2.pop_back();  // 只需要析构对象，要把对象的析构和内存释放分离开
	cout << "---------------------" << endl;

	Vector<int> v3;
	for (int i = 0;i < 20; ++i)
	{
		v3.push_back(rand() % 100 + 1);
	}

	Vector<int>::iterator it = v3.begin();
	for (;it != v3.end();++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	for (int i = 0; i < v3.size(); ++i)
	{
		cout << v3[i] << " ";
	}
	cout << endl;

	for (int val : v3)  // 其底层原理，就是通过容器的迭代器来实现容器的遍历
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}