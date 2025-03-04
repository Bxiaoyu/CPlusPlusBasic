#include <iostream>

using namespace std;

/*
* 自己实现一个字符串对象，且实现迭代器功能
* 迭代器：提供一种统一的方式，来透明的遍历容器，迭代器一般实现成容器的嵌套类型
*/
#if 0
class String
{
public:
	String(const char* p = nullptr)
	{
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
		delete[] pstr_;
		pstr_ = nullptr;
	}

	String(const String& str)
	{
		pstr_ = new char[strlen(str.pstr_) + 1];
		strcpy(pstr_, str.pstr_);
	}

	String& operator=(const String& str)
	{
		if (this == &str)
		{
			return *this;
		}

		delete[] pstr_;
		pstr_ = new char[strlen(str.pstr_) + 1];
		strcpy(pstr_, str.pstr_);
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
	// 这里还不够好，可以用移动语义来提高效率
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

void test_string()
{
	String s1;
	String s2 = "aaa";
	String s3 = "bbb";
	String s4 = s2 + s3;
	String s5 = s2 + "ccc";
	String s6 = "ddd" + s2;

	cout << "str6: " << s6 << endl;
	if (s5 > s6)
	{
		cout << s5 << " > " << s6 << endl;
	}
	else
	{
		cout << s5 << " < " << s6 << endl;
	}

	int len = s6.length();
	for (int i = 0; i < len; ++i)
	{
		cout << s6[i] << " ";
	}
	cout << endl;

	// string -> char*
	char buf[1024] = { 0 };
	strcpy(buf, s6.c_str());
	cout << "buf:" << buf << endl;
}

// 测试字符串容器迭代器
void test_string_iterator()
{
	String str1 = "hello world!";
	// 容器的迭代器类型
	//String::iterator it = str1.begin();
	auto it = str1.begin();
	for (;it != str1.end(); ++it)
	{
		cout << *it;
	}
	cout << endl;

	// C++11 foreach的方式遍历容器的内部元素的值
	// C++11的foreach遍历底层还是通过迭代器来实现
	for (const char& ch : str1)
	{
		cout << ch;
	}
	cout << endl;
}

int main()
{
	test_string_iterator();
	return 0;
}
#endif