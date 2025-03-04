#include <iostream>

using namespace std;

/*
* ��ģ�� -> ʵ���� -> ģ����
*/

#if 0
// ��ģ�壬����ָ��Ĭ������
template<typename T=int>
class SeqStack  // ģ������ + ���Ͳ����б� = ������
{
public:
	// ���캯���������������Բ��ü�<T>����������ģ��ĵط����������Ͳ����б�
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
		// ��Ҫ��memcpy���п���
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
		// ��Ҫ��memcpy���п���
		for (int i = 0; i < top_; ++i)
			pstack_[i] = other.pstack_[i];

		return *this;
	}

	// ��ջ����
	void push(const T& val)
	{
		if (full())
		{
			expand();
		}

		pstack_[top_++] = val;
	}

	// ��ջ����
	void pop()
	{
		if (empty())
		{
			return;
		}

		--top_;
	}

	// ����ջ��Ԫ��
	T top() const
	{
		if (empty())
		{
			throw "stack is empty!";  // ���쳣Ҳ�������߼�����
		}

		return pstack_[top_ - 1];
	}

	// ջ��
	bool full() const
	{
		return top_ == size_;
	}

	// ջ��
	bool empty() const
	{
		return top_ == 0;
	}

private:
	// ˳��ջ�ײ����鰴2���ķ�ʽ����
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
// ��ջ����������ʵ��
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
	// ��ģ���ѡ����ʵ����
	// ģ���� class SeqStack<int>{};
	SeqStack<int> s1;
	s1.push(20);
	s1.push(50);
	s1.push(35);
	s1.push(40);
	s1.pop();
	cout << s1.top() << endl;

	SeqStack<> s2;  // ʹ��Ĭ������

	return 0;
}

#endif
