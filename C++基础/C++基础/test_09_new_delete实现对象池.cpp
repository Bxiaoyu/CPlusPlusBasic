#include <iostream>
#include <typeinfo>

using namespace std;

/*
* ��������أ���Ա���� ȫ�ַ���
* ʵ��һ����ͷ�ڵ����ʽ���ж����
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

	void push(const T& val)  // ��Ӳ���
	{
		QueueItem* item = new QueueItem(val);
		rear_->next_ = item;
		rear_ = item;
	}

	void pop()  // ���Ӳ���
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
	// ����һ��QueueItem�Ķ���أ�100000��QueueItem�ڵ㣩
	struct QueueItem
	{
		QueueItem(T data = T())
			: data_(data)
			, next_(nullptr)
		{
		}

		// ��QueueItem�ṩ�Զ����ڴ����
		// ��Ϊ�ڴ���ǰ���󶼲����ڣ����Ա�����Ĭ�ϻᴦ������������Ϊ��̬����
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

	QueueItem* front_;  // ָ���ͷ�ڵ�
	QueueItem* rear_;   // ָ���β�ڵ�
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::itemPool_ = nullptr;  // ���߱��������Ǹ����ͣ�����������

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