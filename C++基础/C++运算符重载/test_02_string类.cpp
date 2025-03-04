#include <iostream>

using namespace std;

/*
* �Լ�ʵ��һ���ַ���������ʵ�ֵ���������
* ���������ṩһ��ͳһ�ķ�ʽ����͸���ı���������������һ��ʵ�ֳ�������Ƕ������
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
			*pstr_ = '\0';  // ��Ϊ0
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
	// ���ﻹ�����ã��������ƶ����������Ч��
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

// �����ַ�������������
void test_string_iterator()
{
	String str1 = "hello world!";
	// �����ĵ���������
	//String::iterator it = str1.begin();
	auto it = str1.begin();
	for (;it != str1.end(); ++it)
	{
		cout << *it;
	}
	cout << endl;

	// C++11 foreach�ķ�ʽ�����������ڲ�Ԫ�ص�ֵ
	// C++11��foreach�����ײ㻹��ͨ����������ʵ��
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