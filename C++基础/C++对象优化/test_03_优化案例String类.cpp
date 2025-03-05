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
			*pstr_ = '\0';  // ��Ϊ0
		}
	}

	~String()
	{
		cout << "~String()" << endl;
		delete[] pstr_;
		pstr_ = nullptr;
	}

	// ����ֵ���ò����Ŀ�������
	String(const String& str)
	{
		cout << "String(const String& str)" << endl;
		pstr_ = new char[strlen(str.pstr_) + 1];
		strcpy(pstr_, str.pstr_);
	}

	// ����ֵ���ò����Ŀ�������
	String(String&& str) noexcept
	{
		cout << "String(String&& str)" << endl;
		pstr_ = str.pstr_;
		str.pstr_ = nullptr;
	}

	// ����ֵ���ò����ĸ�ֵ���غ���
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

	// ����ֵ���ò����ĸ�ֵ���غ���
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

	// �ɶ���д
	// char ch = str[0]; str[0] = '5';
	char& operator[](int index)
	{
		return pstr_[index];
	}

	// �ɶ�����д
	// char ch = str[0]; ������ str[0] = '5;
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

	// ��String�ַ������ṩ��������ʵ��,������һ��ʵ�ֳ�������Ƕ������
	class iterator
	{
	public:
		iterator(char* p = nullptr)
			: p_(p)
		{
		}

		// ����!=�����
		bool operator!=(const iterator& it) const
		{
			return p_ != it.p_;
		}

		// ����ǰ��++�����
		void operator++()
		{
			++p_;
		}

		// ���ؽ����������
		char& operator*()
		{
			return *p_;
		}
	private:
		char* p_;
	};

	// begin���ص��������ײ���Ԫ�صĵ�������ʾ
	iterator begin() { return iterator(pstr_); }

	// end���ص�������ĩβԪ�غ��λ�õĵ�������ʾ
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

// ���������ռ�����������C++��׼���allocatorʵ��һ��
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // ���𿪱��ڴ�
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // �����ͷ��ڴ�
	{
		free(p);
	}

	//void construct(T* p, const T& val)   // ���������
	//{
	//	new (p) T(val);  // ��λnew
	//}

	//void construct(T* p, T&& val)   // ���������
	//{
	//	new (p) T(std::move(val));  // ��λnew
	//}

	template<typename Ty>
	void construct(T* p, Ty&& val)
	{
		new (p) T(std::forward<Ty>(val));
	}

	void destroy(T* p)  // �����������
	{
		p->~T();  // ~T()����T���͵���������
	}
};

/*
* �����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ���������ʵ��
*/
template<typename T, typename Alloc = Allocator<T>>
class Vector
{
public:

	Vector(int size = 10)
	{
		// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		last_ = first_;
		end_ = first_ + size;
	}

	~Vector()
	{
		// ����������Ч��Ԫ�أ�Ȼ���ͷ�first_ָ��ָ��Ķ��ڴ�
		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);  // ��first_ָ��ָ����������ЧԪ�ؽ�����������
		}
		allocator_.deallocate(first_);  // �ͷŶ��ϵ������ڴ�
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
			allocator_.destroy(p);  // ��first_ָ��ָ����������ЧԪ�ؽ�����������
		}
		allocator_.deallocate(first_);  // �ͷŶ��ϵ������ڴ�

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

	// ������ֵ
	//void push_back(const T& val)
	//{
	//	if (full())
	//	{
	//		expand();
	//	}

	//	//*last_++ = val;  // last_ָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
	//	allocator_.construct(last_, val);
	//	last_++;
	//}

	//// ������ֵ
	//void push_back(T&& val)
	//{
	//	if (full())
	//	{
	//		expand();
	//	}

	//	allocator_.construct(last_, std::move(val));
	//	last_++;
	//}

	template<typename Ty>  // ����ģ����������� + �����۵�
	void push_back(Ty&& val)  // �����۵� T& + && == T& , T&& + && = T&&������ֵ+��ֵ���õ�����ֵ���ã���ֵ����+��ֵ���õ�����ֵ����
	{
		if (full())
		{
			expand();
		}

		// std::move(��ֵ)���ƶ����壬�õ���ֵ���� (int&&)a
		// std::forward����������ת�����ܹ�ʶ����ֵ����ֵ���
		allocator_.construct(last_, std::forward<Ty>(val));
		last_++;
	}

	void pop_back()
	{
		if (empty())
		{
			return;
		}

		//--last_;  // ����Ҫ��last_ָ��--������Ҫ����ɾ����Ԫ��
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

	// �ṩ��������������һ��ʵ�ֳ�������Ƕ������
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

		// ����ǰ��++����������ڶ���һ��ǰ��++Ч�ʸߣ����������ʱ��
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

	// begin���ص��������ײ���Ԫ�صĵ�������ʾ
	iterator begin()
	{
		return iterator(first_);
	}

	// end���ص�������ĩβԪ�غ��λ�õĵ�������ʾ
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
	T* first_;  // ָ��������ʼ��λ��
	T* last_;   // ָ����������ЧԪ�صĺ��λ��
	T* end_;    // ָ������ռ�ĺ��λ��
	Alloc allocator_;  // ���������Ŀռ�����������
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
	// ��ֵ����
	// ��ֵ�����ڴ棬������
	// ��ֵ��û���֣���ʱ������û�ڴ�
	int a = 10;
	int& b = a;  
	//int&& c = a;  // �޷�����ֵ�󶨵���ֵ����
	//int& c = 20;  // ����

	/*
	* int tmp = 20;
	* const int& c = tmp;
	*/
	const int& c = 20;

	/*
	* int tmp = 20;
	* int&& d = tmp;
	*/
	int&& d = 20;  // ���԰�һ����ֵ�󶨵�һ����ֵ������
	String&& ee = String("aaaa");

	//int&& f = d;  // ����һ����ֵ���ñ�����������һ����ֵ
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