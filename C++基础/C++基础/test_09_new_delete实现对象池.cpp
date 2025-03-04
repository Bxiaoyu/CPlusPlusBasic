#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 运算符重载：成员方法 全局方法
* 实现一个带头节点的链式队列对象池
*/
#if 0
template<typename T>
class Queue
{
public:
	Queue()
	{
		front_ = rear_ = new QueueItem();
	}

	~Queue()
	{
		QueueItem* cur = front_;
		while (cur != nullptr)
		{
			front_ = front_->next_;
			delete cur;
			cur = front_;
		}
	}

	void push(const T& val)  // 入队操作
	{
		QueueItem* item = new QueueItem(val);
		rear_->next_ = item;
		rear_ = item;
	}

	void pop()  // 出队操作
	{
		if (empty())
		{
			return;
		}
		QueueItem* tmp = front_->next_;
		front_->next_ = tmp->next_;
		if (front_->next_ == nullptr)
		{
			rear_ = front_;
		}
		delete tmp;
	}

	T front() const
	{
		return front_->next_->data_;
	}

	bool empty() const
	{
		return front_ == rear_;
	}
private:
	// 产生一个QueueItem的对象池（100000个QueueItem节点）
	struct QueueItem
	{
		QueueItem(T data = T())
			: data_(data)
			, next_(nullptr)
		{
		}

		// 给QueueItem提供自定义内存管理
		// 因为在处理前对象都不存在，所以编译器默认会处理这两个函数为静态方法
		void* operator new(size_t size)
		{
			if (itemPool_ == nullptr)
			{
				itemPool_ = (QueueItem*)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
				QueueItem* p = itemPool_;
				for (;p < itemPool_ + POOL_ITEM_SIZE - 1; ++p)
				{
					p->next_ = p + 1;
				}
				p->next_ = nullptr;
			}

			QueueItem* p = itemPool_;
			itemPool_ = itemPool_->next_;
			return p;
		}

		void operator delete(void* ptr)
		{
			QueueItem* p = (QueueItem*)ptr;
			p->next_ = itemPool_;
			itemPool_ = p;
		}

		T data_;
		QueueItem* next_;
		static QueueItem* itemPool_;
		static const int POOL_ITEM_SIZE = 100000;
	};

	QueueItem* front_;  // 指向队头节点
	QueueItem* rear_;   // 指向队尾节点
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::itemPool_ = nullptr;  // 告诉编译器这是个类型，避免编译错误

int main()
{
	Queue<int> que;
	for (int i = 0; i < 1000000; ++i)
	{
		que.push(i);
		que.pop();
	}

	cout << que.empty() << endl;

	return 0;
}
#endif