#include <iostream>

using namespace std;

/*
* C++运算符重载：使对象的运算表现得和编译器内置类型一样
* 复数类实现
*/
#if 0

class CComplex
{
public:
	CComplex(int r = 0, int i = 0)
		: mreal_(r), mimage_(i)
	{
	}

	// 指导编译器怎么做CComplex类对象的加法操作
	CComplex operator+(const CComplex& other)
	{
		// 局部对象不能返回其引用或指针
		return CComplex(this->mreal_ + other.mreal_,
			this->mimage_ + other.mimage_);
	}

	// 前置++，先++，后赋值；
	// 返回++后的值；
	CComplex& operator++()
	{
		mreal_ += 1;
		mimage_ += 1;
		return *this;
	}

	// 后置++，先赋值，后++；
	// 返回++前的原始值
	CComplex operator++(int)
	{
		// 局部对象不能返回其引用或指针
		//CComplex comp = *this;
		//mreal_ += 1;
		//mimage_ += 1;
		//return comp;
		return CComplex(mreal_++, mimage_++);  // 优化
	}

	// 复合运算符重载
	void operator+=(const CComplex& other)
	{
		mreal_ += other.mreal_;
		mimage_ += other.mimage_;
	}

	void show()
	{
		cout << "real:" << mreal_ << " image:" << mimage_ << endl;
	}
private:
	int mreal_;
	int mimage_;

	friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);
	friend ostream& operator<<(ostream& out, const CComplex& src);
	friend istream& operator>>(istream& in, CComplex& src);
};

// 全局重载函数
CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.mreal_ + rhs.mreal_,
		lhs.mimage_ + rhs.mimage_);
}

ostream& operator<<(ostream& out, const CComplex& src)
{
	out << "real:" << src.mreal_ << " image:" << src.mimage_ << endl;
	return out;
}

istream& operator>>(istream& in, CComplex& src)
{
	in >> src.mreal_ >> src.mimage_;
	return in;
}

int main()
{
	CComplex com1(10, 10);
	CComplex com2(20, 20);
	// com1.operator+(com2)  加法运算符的重载函数
	CComplex com3 = com1 + com2;
	com3.show();
	CComplex com4 = com1 + 20;
	com4.show();
	// 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有
	// 成员方法，就在全局作用域找合适的运算符重载函数
	// ::operator+(30, com1)
	CComplex com5 = 30 + com1;
	com5.show();

	com5 = com1++;  // ++ -- 单目运算符 operator++() 前置++ operator++(int) 后置++
	com1.show();
	com5.show();
	com5 = ++com1;
	com1.show();
	com5.show();

	// void com1.operator+=(com2)  void::operator+=(com1, com2)
	com1 += com2;
	com1.show();

	// cout ::operator<<(cout, com1)
	// ostream& operator<<(ostream& out, const CComplex& src)
	// istream& operator>>(istream& in, CComplex& src)
	cout << com1 << endl;
	cin >> com1 >> com2;
	cout << com1 << com2 << endl;

	return 0;
}
#endif