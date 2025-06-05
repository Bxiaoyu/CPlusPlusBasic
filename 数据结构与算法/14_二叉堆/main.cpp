#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 优先级队列实现   priority_queue(vector)  push pop top empty size
/*
* 第i个节点的左孩子：i * 2 + 1
* 第i个节点的右孩子：i * 2 + 2
* 第i个节点的父节点：(i - 1) / 2
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
	// 入堆操作
	void push(int val)
	{
		// 判断扩容
		if (size_ == cap_)
		{
			expand(2 * cap_);
		}

		if (size_ == 0)
		{
			// 只有一个元素，不需要进行上浮调整
			que_[size_] = val;
		}
		else
		{
			// 堆里面有多个元素，需要进行上浮调整
			shiftUp(size_, val);
		}

		size_++;
	}

	// 出堆操作
	void pop()
	{
		if (size_ == 0)
		{
			throw "container is empty!";
		}

		size_--;

		if (size_ > 0)
		{
			// 删除堆顶元素，还有剩余元素，要进行下沉调整
			shiftDown(0, que_[size_]);
		}
	}

	// 获取堆顶元素
	int top() const
	{
		if (size_ == 0)
		{
			throw "container is empty!";
		}

		return que_[0];
	}

	// 判空
	bool empty() const
	{
		return size_ == 0;
	}

	// 获取堆元素个数
	int size() const
	{
		return size_;
	}

private:
	// 扩容函数
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, que_, sizeof(int) * cap_);  // 只涉及到int类型，可以用memcpy进行复制
		delete[] que_;
		que_ = p;
		cap_ = size;
	}

	// 堆的上浮调整函数
	void shiftUp(int i, int val)
	{
		while (i > 0)  // 最多计算到根节点（0号位）
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

		// 把val放到i的位置
		que_[i] = val;
	}

	// 堆的下沉调整函数
	void shiftDown(int i, int val)
	{
		// i下沉不能超过最后一个有孩子的节点
		while (i < size_ / 2)  // 或者 i <= size / 2 - 1
		{
			int child = i * 2 + 1;  // 第i个节点的左孩子
			if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))  // 有右孩子，且右孩子和左孩子满足关系式
			{
				// 如果i节点的右孩子大于左孩子，leftChild记录右孩子的下标
				child += 1;
			}

			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break;  // 已经满足堆的性质，提前结束
			}
		}
		que_[i] = val;
	}

private:
	int* que_;   // 指向动态扩容的数组
	int size_;   // 数组元素个数
	int cap_;    // 数组的总空间大小
	Comp comp_;  // 比较器对象
};

int main()
{
	 PriorityQueue que; // 基于大根堆实现的优先级队列

	// 基于小根堆实现的优先级队列
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