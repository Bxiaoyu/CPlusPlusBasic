#include <iostream>

using namespace std;

/*
* 迭代器失效的底层原理的简单理解
* 通过对Vector容器增加迭代器失效检测来实现
*/

#if 0
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

		verify(last_ - 1, last_);
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
		friend class Vector<T, Alloc>;

		iterator(Vector<T, Alloc>* pvec = nullptr, T* p = nullptr)
			: p_(p)
			, pVec_(pvec)
		{
			Iterator_Base* itb = new Iterator_Base(this, pVec_->head_.next_);
			pVec_->head_.next_ = itb;
		}

		bool operator!=(const iterator& it) const
		{
			// 检查迭代器有效性
			if (pVec_ == nullptr || pVec_ != it.pVec_)
			{
				throw "Iterator incompatable!";
			}
			return p_ != it.p_;
		}

		// 重载前置++运算符，对于对象，一般前置++效率高，避免产生临时量
		void operator++()
		{
			// 检查迭代器有效性
			if (pVec_ == nullptr)
			{
				throw "Iterator invalid!";
			}
			++p_;
		}

		T& operator*()
		{
			if (pVec_ == nullptr)
			{
				throw "Iterator invalid!";
			}
			return *p_;
		}
	private:
		T* p_;
		Vector<T, Alloc>* pVec_;  // 当前迭代器是哪一个容器对象
	};

	// begin返回的是容器底层首元素的迭代器表示
	iterator begin()
	{
		return iterator(this, first_);
	}

	// end返回的是容器末尾元素后继位置的迭代器表示
	iterator end()
	{
		return iterator(this, last_);
	}

	// 自定义Vector容器insert方法的简单实现
	iterator insert(iterator it, const T& val)
	{
		/*
		* 1、不考虑扩容
		* 2、不考虑it.p_的指针合法性
		*/
		verify(it.p_ - 1, last_);
		T* p = last_;
		while (p > it.p_)
		{
			allocator_.construct(p, *(p - 1));
			allocator_.destroy(p - 1);
			p--;
		}
		allocator_.construct(p, val);
		last_++;
		return iterator(this, p);
	}

	// 自定义Vector容器erase方法的简单实现
	iterator erase(iterator it)
	{
		verify(it.p_ - 1, last_);
		T* p = it.p_;
		while (p < last_ - 1)
		{
			allocator_.destroy(p);
			allocator_.construct(p, *(p + 1));
			p++;
		}
		allocator_.destroy(p);
		last_--;

		return iterator(this, it.p_);
	}

	// 检查迭代器是否失效
	void verify(T* first, T* last)
	{
		Iterator_Base* pre = &this->head_;
		Iterator_Base* it = this->head_.next_;
		while (it != nullptr)
		{
			if (it->cur_->p_ > first && it->cur_->p_ <= last_) 
			{
				// 迭代器失效，把iterator持有的容器指针置为nullptr
				it->cur_->pVec_ = nullptr;
				// 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
				pre->next_ = it->next_;
				delete it;
				it = pre->next_;
			}
			else
			{
				pre = it;
				it = it->next_;
			}
		}
	}
private:
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			: cur_(c)
			, next_(n)
		{
		}

		iterator* cur_;
		Iterator_Base* next_;
	};

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
	Iterator_Base head_;
};


int main()
{
	Vector<int> vec(200);
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

#if 0
	auto it = vec.begin();
	for (;it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, *it - 1);
			++it;
		}
	}
#endif

	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
#endif