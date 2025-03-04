#include <iostream>

using namespace std;

/*
* C++��������أ�ʹ�����������ֵúͱ�������������һ��
* ������ʵ��
*/
#if 0

class CComplex
{
public:
	CComplex(int r = 0, int i = 0)
		: mreal_(r), mimage_(i)
	{
	}

	// ָ����������ô��CComplex�����ļӷ�����
	CComplex operator+(const CComplex& other)
	{
		// �ֲ������ܷ��������û�ָ��
		return CComplex(this->mreal_ + other.mreal_,
			this->mimage_ + other.mimage_);
	}

	// ǰ��++����++����ֵ��
	// ����++���ֵ��
	CComplex& operator++()
	{
		mreal_ += 1;
		mimage_ += 1;
		return *this;
	}

	// ����++���ȸ�ֵ����++��
	// ����++ǰ��ԭʼֵ
	CComplex operator++(int)
	{
		// �ֲ������ܷ��������û�ָ��
		//CComplex comp = *this;
		//mreal_ += 1;
		//mimage_ += 1;
		//return comp;
		return CComplex(mreal_++, mimage_++);  // �Ż�
	}

	// �������������
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

// ȫ�����غ���
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
	// com1.operator+(com2)  �ӷ�����������غ���
	CComplex com3 = com1 + com2;
	com3.show();
	CComplex com4 = com1 + 20;
	com4.show();
	// �����������������ʱ�򣬻���ö������������غ��������ȵ��ó�Ա�����������û��
	// ��Ա����������ȫ���������Һ��ʵ���������غ���
	// ::operator+(30, com1)
	CComplex com5 = 30 + com1;
	com5.show();

	com5 = com1++;  // ++ -- ��Ŀ����� operator++() ǰ��++ operator++(int) ����++
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