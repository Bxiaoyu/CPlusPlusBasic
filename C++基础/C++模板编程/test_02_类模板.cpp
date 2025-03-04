#include <iostream>

using namespace std;

/*
* 类模板 -> 实例化 -> 模板类
*/

#if 0
// 类模板，可以指定默认类型
template<typename T=int>
class SeqStack  // 模板名称 + 类型参数列表 = 类名称
{
public:
	// 构造函数和析构函数可以不用加<T>，其它出现模板的地方都加上类型参数列表
	SeqStack(int size = 10)
		: pstack_(new T[size])
		, top_(0)
		, size_(size)
	{
	}

	~SeqStack()
	{
		delete[] pstack_;
		pstack_ = nullptr;
	}

	SeqStack(const SeqStack<T>& other)
		: top_(other.top_)
		, size_(other.size_)
	{
		pstack_ = new T[size_];
		// 不要用memcpy进行拷贝
		for (int i = 0; i < top_; ++i)
			pstack_[i] = other.pstack_[i];
	}

	SeqStack<T>& operator=(const SeqStack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] pstack_;

		top_ = other.top_;
		size_ = other.size_;
		pstack_ = new T[size_];
		// 不要用memcpy进行拷贝
		for (int i = 0; i < top_; ++i)
			pstack_[i] = other.pstack_[i];

		return *this;
	}

	// 入栈操作
	void push(const T& val)
	{
		if (full())
		{
			expand();
		}

		pstack_[top_++] = val;
	}

	// 出栈操作
	void pop()
	{
		if (empty())
		{
			return;
		}

		--top_;
	}

	// 返回栈顶元素
	T top() const
	{
		if (empty())
		{
			throw "stack is empty!";  // 抛异常也代表函数逻辑结束
		}

		return pstack_[top_ - 1];
	}

	// 栈满
	bool full() const
	{
		return top_ == size_;
	}

	// 栈空
	bool empty() const
	{
		return top_ == 0;
	}

private:
	// 顺序栈底层数组按2倍的方式扩容
	void expand()
	{
		T* ptmp = new T[2 * size_];
		for (int i = 0; i < top_; ++i)
			ptmp[i] = pstack_[i];

		delete[] pstack_;
		pstack_ = ptmp;
		size_ *= 2;
	}

private:
	T* pstack_;
	int top_;
	int size_;
};

#if 0
// 入栈操作，类外实现
template<typename T>
void SeqStack<T>::push(const T& val)
{
	if (full())
	{
		expand();
	}

	pstack_[top_++] = val;
}
#endif


int main()
{
	// 类模板的选择性实例化
	// 模板类 class SeqStack<int>{};
	SeqStack<int> s1;
	s1.push(20);
	s1.push(50);
	s1.push(35);
	s1.push(40);
	s1.pop();
	cout << s1.top() << endl;

	SeqStack<> s2;  // 使用默认类型

	return 0;
}

#endif
