#include <iostream>
#include <string>

using namespace std;

#if 0
// ʵ�ּ�����
class Array
{
public:
	Array(int size = 10)
		: mCap_(size)
		, mCur_(0)
	{
		mpArr_ = new int[mCap_]();  // �����ڴ沢��ʼ��
	}

	~Array()
	{
		delete[] mpArr_;
		mpArr_ = nullptr;
	}

	// ĩβ����Ԫ��
	void push_back(int val)
	{
		if (mCur_ == mCap_)
		{
			expand(2 * mCap_);  // O(n)
		}
		mpArr_[mCur_++] = val;
	}

	// ĩβɾ��Ԫ��
	void pop_back()
	{
		if (mCur_ == 0) return;
		mCur_--;
	}

	// ��λ������Ԫ��
	void insert(int pos, int val)
	{
		if (pos < 0 || pos > mCur_)
		{
			throw "pos invalid!";
		}

		if (mCur_ == mCap_)
		{
			expand(2 * mCap_);
		}

		for (int i = mCur_ - 1;i >= pos; i--)
		{
			mpArr_[i + 1] = mpArr_[i];
		}

		mpArr_[pos] = val;
		mCur_++;
	}

	// ��λ��ɾ��
	void erase(int pos)
	{
		if (pos < 0 || pos >= mCur_) return;

		for (int i = pos + 1; i < mCur_; i++)
		{
			mpArr_[i - 1] = mpArr_[i];
		}

		mCur_--;
	}

	// Ԫ�ز�ѯ
	int find(int val)
	{
		for (int i = 0; i < mCur_; i++)
		{
			if (mpArr_[i] == val)
				return i;
		}

		return -1;
	}

	// ��ӡ����
	void show()
	{
		for (int i = 0; i < mCur_; i++)
			cout << mpArr_[i] << " ";
		cout << endl;
	}

private:
	// ���ݽӿ�
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpArr_, sizeof(int) * mCap_);  // ��������Ϊ���Σ����Բ��ÿ�����ǳ��������

		delete[] mpArr_;
		mpArr_ = p;
		mCap_ = size;
	}
private:
	int* mpArr_;  // ָ������ݵ������ڴ�
	int mCap_;    // ���������
	int mCur_;     // ������ЧԪ�ظ���
};

int main()
{
	Array arr;

	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 100);
	}

	arr.show();
	arr.pop_back();
	arr.show();

	arr.insert(0, 100);
	arr.show();

	arr.insert(10, 200);
	arr.show();

	int pos = arr.find(100);
	if (pos != -1)
	{
		arr.erase(pos);
		arr.show();
	}
}
#endif

#if 0
// �����ַ���
void reverse(char arr[], int size)
{
	//int begin = 0;
	//int end = size - 1;

	//while (begin < end)
	//{
	//	char temp = arr[begin];
	//	arr[begin] = arr[end];
	//	arr[end] = temp;
	//	begin++;
	//	end--;
	//}

	char* p = arr;
	char* q = arr + size - 1;

	while (p < q)
	{
		char ch = *p;
		*p = *q;
		*q = ch;
		p++;
		q--;
	}
}

int main()
{
	char arr[] = "hello world";
	reverse(arr, strlen(arr));
	cout << arr << endl;
}
#endif

// �������飬��ż��������������ߣ������������������ұ�
void adjustArray(int arr[], int size)
{
	int* p = arr;
	int* q = arr + size - 1;

	while (p < q)
	{
		// p->����
		while (p < q) 
		{
			if ((*p & 0x1) == 1) break;
			p++;
		}

		// q->ż��
		while (p < q)
		{
			if ((*q & 0x1) == 0) break;
			q--;
		}

		if (p < q)
		{
			int temp = *p;
			*p = *q;
			*q = temp;
			p++;
			q--;
		}
	}
}

int main()
{
	int arr[10] = { 0 };
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	adjustArray(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}