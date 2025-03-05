#include <iostream>
#include <vector>

using namespace std;

#if 0
class String
{
public:
	String(const char* p = nullptr)
	{
		cout << "String(const char* p = nullptr)" << endl;
		if (p != nullptr)
		{
			pstr_ = new char[strlen(p) + 1];
			strcpy(pstr_, p);
		}
		else
		{
			pstr_ = new char[1];
			*pstr_ = '\0';  // 置为0
		}
	}

	~String()
	{
		cout << "~String()" << endl;
		delete[] pstr_;
		pstr_ = nullptr;
	}

	// 带左值引用参数的拷贝构造
	String(const String& str)
	{
		cout << "String(const String& str)" << endl;
		pstr_ = new char[strlen(str.pstr_) + 1];
		strcpy(pstr_, str.pstr_);
	}

	// 带右值引用参数的拷贝构造
	String(String&& str) noexcept
	{
		cout << "String(String&& str)" << endl;
		pstr_ = str.pstr_;
		str.pstr_ = nullptr;
	}

	// 带左值引用参数的赋值重载函数
	String& operator=(const String& str)
	{
		cout << "String& operator=(const String& str)" << endl;
		if (this == &str)
		{
			return *this;
		}

		delete[] pstr_;
		pstr_ = new char[strlen(str.pstr_) + 1];
		strcpy(pstr_, str.pstr_);
		return *this;
	}

	// 带右值引用参数的赋值重载函数
	String& operator=(String&& str) noexcept
	{
		cout << "String& operator=(String&& str)" << endl;
		if (this == &str)
		{
			return *this;
		}

		delete[] pstr_;
		pstr_ = str.pstr_;
		str.pstr_ = nullptr;
		return *this;
	}

	bool operator>(const String& str) const
	{
		return strcmp(pstr_, str.pstr_) > 0;
	}

	bool operator<(const String& str) const
	{
		return strcmp(pstr_, str.pstr_) < 0;
	}

	bool operator==(const String& str) const
	{
		return strcmp(pstr_, str.pstr_) == 0;
	}

	// 可读可写
	// char ch = str[0]; str[0] = '5';
	char& operator[](int index)
	{
		return pstr_[index];
	}

	// 可读不可写
	// char ch = str[0]; 不允许 str[0] = '5;
	const char& operator[](int index) const
	{
		return pstr_[index];
	}

	const char* c_str() const
	{
		return pstr_;
	}

	size_t length() const
	{
		return strlen(pstr_);
	}

	// 给String字符串类提供迭代器的实现,迭代器一般实现成容器的嵌套类型
	class iterator
	{
	public:
		iterator(char* p = nullptr)
			: p_(p)
		{
		}

		// 重载!=运算符
		bool operator!=(const iterator& it) const
		{
			return p_ != it.p_;
		}

		// 重载前置++运算符
		void operator++()
		{
			++p_;
		}

		// 重载解引用运算符
		char& operator*()
		{
			return *p_;
		}
	private:
		char* p_;
	};

	// begin返回的是容器底层首元素的迭代器表示
	iterator begin() { return iterator(pstr_); }

	// end返回的是容器末尾元素后继位置的迭代器表示
	iterator end() { return iterator(pstr_ + length()); }
private:
	char* pstr_;

	friend String operator+(const String& lhs, const String& rhs);
	friend ostream& operator<<(ostream& out, const String& str);
};

String operator+(const String& lhs, const String& rhs)
{
	String tmp;
	tmp.pstr_ = new char[strlen(lhs.pstr_) + strlen(rhs.pstr_) + 1];
	strcpy(tmp.pstr_, lhs.pstr_);
	strcat(tmp.pstr_, rhs.pstr_);
	return tmp;
}

ostream& operator<<(ostream& out, const String& str)
{
	out << str.pstr_;
	return out;
}

String GetString(String& str)
{
	const char* pstr = str.c_str();
	String tmpStr(pstr);
	return tmpStr;
}

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

	//void construct(T* p, const T& val)   // 负责对象构造
	//{
	//	new (p) T(val);  // 定位new
	//}

	//void construct(T* p, T&& val)   // 负责对象构造
	//{
	//	new (p) T(std::move(val));  // 定位new
	//}

	template<typename Ty>
	void construct(T* p, Ty&& val)
	{
		new (p) T(std::forward<Ty>(val));
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

	// 接收左值
	//void push_back(const T& val)
	//{
	//	if (full())
	//	{
	//		expand();
	//	}

	//	//*last_++ = val;  // last_指针指向的内存构造一个值为val的对象
	//	allocator_.construct(last_, val);
	//	last_++;
	//}

	//// 接收右值
	//void push_back(T&& val)
	//{
	//	if (full())
	//	{
	//		expand();
	//	}

	//	allocator_.construct(last_, std::move(val));
	//	last_++;
	//}

	template<typename Ty>  // 函数模板的类型推演 + 引用折叠
	void push_back(Ty&& val)  // 引用折叠 T& + && == T& , T&& + && = T&&，即左值+右值引用等于左值引用，右值引用+右值引用等于右值引用
	{
		if (full())
		{
			expand();
		}

		// std::move(左值)：移动语义，得到右值类型 (int&&)a
		// std::forward：类型完美转发，能够识别左值和右值类别
		allocator_.construct(last_, std::forward<Ty>(val));
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

void test_1()
{
	/*
String(const char* p = nullptr)
String(const char* p = nullptr)
String(const char* p = nullptr)
String& operator=(const String& str)
~String()
aaaaaaaaaaaaa
~String()
~String()
*/

/*
String(const char* p = nullptr)
String(const char* p = nullptr)
String(const char* p = nullptr)
String& operator=(String&& str)
~String()
aaaaaaaaaaaaa
~String()
~String()
*/
	String str1("aaaaaaaaaaaaa");
	String str2;
	str2 = GetString(str1);
	cout << str2.c_str() << endl;
}

void test_right_ref()
{
	// 右值引用
	// 左值：有内存，有名字
	// 右值：没名字（临时量），没内存
	int a = 10;
	int& b = a;  
	//int&& c = a;  // 无法将左值绑定到右值引用
	//int& c = 20;  // 错误

	/*
	* int tmp = 20;
	* const int& c = tmp;
	*/
	const int& c = 20;

	/*
	* int tmp = 20;
	* int&& d = tmp;
	*/
	int&& d = 20;  // 可以把一个右值绑定到一个右值引用上
	String&& ee = String("aaaa");

	//int&& f = d;  // 错误，一个右值引用变量，本身是一个左值
}

void test_2()
{
	String str1 = "aaa";
	vector<String> vec;
	vec.reserve(10);
	cout << "----------------------" << endl;
	vec.push_back(str1);
	vec.push_back(String("bbb"));
	cout << "----------------------" << endl;
	//String str1 = "hello";
	//String str2 = " world!";
	//String str3 = str1 + str2;
	//cout << str3 << endl;
}

void test_3()
{
	String str1 = "aaa";
	Vector<String> vec;
	cout << "----------------------" << endl;
	vec.push_back(std::move(str1));
	vec.push_back(String("bbb"));  // move forward
	cout << "----------------------" << endl;
}

int main()
{
	test_3();

	return 0;
}
#endif