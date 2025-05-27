#include <iostream>
#include <string>

using namespace std;

#if 0
// 实现简单数组
class Array
{
public:
	Array(int size = 10)
		: mCap_(size)
		, mCur_(0)
	{
		mpArr_ = new int[mCap_]();  // 开辟内存并初始化
	}

	~Array()
	{
		delete[] mpArr_;
		mpArr_ = nullptr;
	}

	// 末尾增加元素
	void push_back(int val)
	{
		if (mCur_ == mCap_)
		{
			expand(2 * mCap_);  // O(n)
		}
		mpArr_[mCur_++] = val;
	}

	// 末尾删除元素
	void pop_back()
	{
		if (mCur_ == 0) return;
		mCur_--;
	}

	// 按位置增加元素
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

	// 按位置删除
	void erase(int pos)
	{
		if (pos < 0 || pos >= mCur_) return;

		for (int i = pos + 1; i < mCur_; i++)
		{
			mpArr_[i - 1] = mpArr_[i];
		}

		mCur_--;
	}

	// 元素查询
	int find(int val)
	{
		for (int i = 0; i < mCur_; i++)
		{
			if (mpArr_[i] == val)
				return i;
		}

		return -1;
	}

	// 打印数据
	void show()
	{
		for (int i = 0; i < mCur_; i++)
			cout << mpArr_[i] << " ";
		cout << endl;
	}

private:
	// 扩容接口
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpArr_, sizeof(int) * mCap_);  // 数组数据为整形，可以不用考虑深浅拷贝问题

		delete[] mpArr_;
		mpArr_ = p;
		mCap_ = size;
	}
private:
	int* mpArr_;  // 指向可扩容的数组内存
	int mCap_;    // 数组的容量
	int mCur_;     // 数组有效元素个数
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
// 逆序字符串
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

// 整形数组，把偶数调整到数组左边，把奇数调整到数组右边
void adjustArray(int arr[], int size)
{
	int* p = arr;
	int* q = arr + size - 1;

	while (p < q)
	{
		// p->奇数
		while (p < q) 
		{
			if ((*p & 0x1) == 1) break;
			p++;
		}

		// q->偶数
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