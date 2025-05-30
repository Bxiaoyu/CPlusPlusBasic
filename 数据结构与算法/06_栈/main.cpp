#include <iostream>

using namespace std;

/*
* ˳��ջ  C++���������� stack    push   pop   top   empty  size
*/
class SeqStack
{
public:
	SeqStack(int size = 10)
		: top_(0)
		, cap_(size)
	{
		arr_ = new int[cap_];
	}

	~SeqStack()
	{
		delete[] arr_;
		arr_ = nullptr;
	}

public:
	// ��ջ
	void push(int val)
	{
		if (top_ == cap_)
		{
			expand(2 * cap_);
		}

		arr_[top_++] = val;
	}

	// ��ջ
	void pop()
	{
		if (top_ == 0)
			throw "Stack is empty!";
		top_--;
	}

	// ��ȡջ��Ԫ��
	int top() const
	{
		if (top_ == 0)
			throw "Stack is empty!";
		return arr_[top_ - 1];
	}

	// �ж�ջ��
	bool empty() const
	{
		return top_ == 0;
	}

	// ջԪ�ظ���
	int size() const
	{
		return top_;
	}
private:
	// ����
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, arr_, sizeof(int) * top_);
		delete[] arr_;
		arr_ = p;
		cap_ = size;
	}
private:
	int* arr_;
	int top_;    // ջ��λ��
	int cap_;    // ջ�ռ��С
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	SeqStack s;

	for (int v : arr)
	{
		s.push(v);
	}

	cout << "stack size = " << s.size() << endl;

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << "ջ" << (s.empty() ? "��" : "�ǿ�") << endl;
}