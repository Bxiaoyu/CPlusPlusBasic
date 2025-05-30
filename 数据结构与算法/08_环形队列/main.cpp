#include <iostream>

using namespace std;

/*
* 环形队列，数组实现，queue  push  pop  front  back  empty size
* 始终空出一个位置，来区分队列空还是满
* first_ == rear_ -> 队列为空
* (rear_ + 1) % length == first_ -> 队列满了
* rear_总是指向末尾元素的下一个位置
*/
class Queue
{
public:
	Queue(int size = 10)
		: cap_(size)
		, size_(0)
		, front_(0)
		, rear_(0)
	{
		pQue_ = new int[cap_];
	}

	~Queue()
	{
		delete[] pQue_;
		pQue_ = nullptr;
	}

public:
	// 入队 O(1)
	void push(int val)
	{
		if ((rear_ + 1) % cap_ == front_)
		{
			expand(2 * cap_);
		}

		pQue_[rear_] = val;
		rear_ = (rear_ + 1) % cap_;
		size_++;
	}

	// 出队 O(1)
	void pop()
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		front_ = (front_ + 1) % cap_;
		size_--;
	}

	// 获取队头元素
	int front() const
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		return pQue_[front_];
	}

	// 获取队尾元素
	int back() const
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		// 此处考虑到如果队列不空，且rear_== 0时，该怎么获取队尾元素
		// (rear_ - 1 + cap_) % cap_ 保证 rear_ == 0 的特殊情况时也能正确获取队尾元素
		return pQue_[(rear_ - 1 + cap_) % cap_];
	}

	// 队列判空
	bool empty() const
	{
		return rear_ == front_;
	}

	// 队列元素个数
	int size() const
	{
		return size_;
	}

	// 打印
	void show()
	{
		for (int i = front_; i != rear_; i = (i + 1) % cap_)
		{
			cout << pQue_[i] << " ";
		}
		cout << endl;
	}

private:
	// 扩容，因为是环形队列，不能用memcpy来简单拷贝
	void expand(int size)
	{
		cout << "expand size..." << endl;
		int* p = new int[size];
		int index = 0;
		for (int i = front_; i != rear_; i = (i + 1) % cap_)
		{
			p[index++] = pQue_[i];
		}
		delete[] pQue_;
		pQue_ = p;
		cap_ = size;
		front_ = 0;
		rear_ = index;
	}
private:
	int* pQue_;
	int front_;  // 队头
	int rear_;   // 队尾
	int size_;   // 队列元素个数
	int cap_;    // 空间容量
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	Queue que;

	for (int v : arr)
	{
		que.push(v);
	}

	que.show();
	cout << que.front() << endl;
	cout << que.back() << endl;

	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.front() << endl;
	cout << que.back() << endl;
	que.show();

	while (!que.empty())
	{
		cout << que.front() << " " << que.back() << endl;
		que.pop();
	}
}