#include <iostream>

using namespace std;

/*
* Ë³ÐòÕ»  C++ÈÝÆ÷ÊÊÅäÆ÷ stack    push   pop   top   empty  size
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
	// ÈëÕ»
	void push(int val)
	{
		if (top_ == cap_)
		{
			expand(2 * cap_);
		}

		arr_[top_++] = val;
	}

	// ³öÕ»
	void pop()
	{
		if (top_ == 0)
			throw "Stack is empty!";
		top_--;
	}

	// »ñÈ¡Õ»¶¥ÔªËØ
	int top() const
	{
		if (top_ == 0)
			throw "Stack is empty!";
		return arr_[top_ - 1];
	}

	// ÅÐ¶ÏÕ»¿Õ
	bool empty() const
	{
		return top_ == 0;
	}

	// Õ»ÔªËØ¸öÊý
	int size() const
	{
		return top_;
	}
private:
	// À©ÈÝ
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
	int top_;    // Õ»¶¥Î»ÖÃ
	int cap_;    // Õ»¿Õ¼ä´óÐ¡
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

	cout << "Õ»" << (s.empty() ? "¿Õ" : "·Ç¿Õ") << endl;
}