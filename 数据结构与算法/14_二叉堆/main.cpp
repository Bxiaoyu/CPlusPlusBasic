#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>
using namespace std;

// ���ȼ�����ʵ��   priority_queue(vector)  push pop top empty size
/*
* ��i���ڵ�����ӣ�i * 2 + 1
* ��i���ڵ���Һ��ӣ�i * 2 + 2
* ��i���ڵ�ĸ��ڵ㣺(i - 1) / 2
*/
class PriorityQueue
{
public:
	using Comp = function<bool(int, int)>;

	PriorityQueue(int cap=20, Comp comp=greater<int>())
		: size_(0)
		, cap_(cap)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}

	PriorityQueue(Comp comp)
		: size_(0)
		, cap_(20)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}

	~PriorityQueue()
	{
		delete[] que_;
		que_ = nullptr;
	}

public:
	// ��Ѳ���
	void push(int val)
	{
		// �ж�����
		if (size_ == cap_)
		{
			expand(2 * cap_);
		}

		if (size_ == 0)
		{
			// ֻ��һ��Ԫ�أ�����Ҫ�����ϸ�����
			que_[size_] = val;
		}
		else
		{
			// �������ж��Ԫ�أ���Ҫ�����ϸ�����
			shiftUp(size_, val);
		}

		size_++;
	}

	// ���Ѳ���
	void pop()
	{
		if (size_ == 0)
		{
			throw "container is empty!";
		}

		size_--;

		if (size_ > 0)
		{
			// ɾ���Ѷ�Ԫ�أ�����ʣ��Ԫ�أ�Ҫ�����³�����
			shiftDown(0, que_[size_]);
		}
	}

	// ��ȡ�Ѷ�Ԫ��
	int top() const
	{
		if (size_ == 0)
		{
			throw "container is empty!";
		}

		return que_[0];
	}

	// �п�
	bool empty() const
	{
		return size_ == 0;
	}

	// ��ȡ��Ԫ�ظ���
	int size() const
	{
		return size_;
	}

private:
	// ���ݺ���
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, que_, sizeof(int) * cap_);  // ֻ�漰��int���ͣ�������memcpy���и���
		delete[] que_;
		que_ = p;
		cap_ = size;
	}

	// �ѵ��ϸ���������
	void shiftUp(int i, int val)
	{
		while (i > 0)  // �����㵽���ڵ㣨0��λ��
		{
			int f = (i - 1) / 2;
			if (comp_(val, que_[f]))
			{
				que_[i] = que_[f];
				i = f;
			}
			else
			{
				break;
			}
		}

		// ��val�ŵ�i��λ��
		que_[i] = val;
	}

	// �ѵ��³���������
	void shiftDown(int i, int val)
	{
		// i�³����ܳ������һ���к��ӵĽڵ�
		while (i < size_ / 2)  // ���� i <= size / 2 - 1
		{
			int child = i * 2 + 1;  // ��i���ڵ������
			if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))  // ���Һ��ӣ����Һ��Ӻ����������ϵʽ
			{
				// ���i�ڵ���Һ��Ӵ������ӣ�leftChild��¼�Һ��ӵ��±�
				child += 1;
			}

			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break;  // �Ѿ�����ѵ����ʣ���ǰ����
			}
		}
		que_[i] = val;
	}

private:
	int* que_;   // ָ��̬���ݵ�����
	int size_;   // ����Ԫ�ظ���
	int cap_;    // ������ܿռ��С
	Comp comp_;  // �Ƚ�������
};

int main()
{
	 PriorityQueue que; // ���ڴ����ʵ�ֵ����ȼ�����

	// ����С����ʵ�ֵ����ȼ�����
	//PriorityQueue que([](int a, int b) {return a < b; });
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		que.push(rand() % 100);
	}

	while (!que.empty())
	{
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
}