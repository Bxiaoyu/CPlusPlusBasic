#include <iostream>

using namespace std;

/*
* 双向循环链表
*/

// 定义双向链表的节点类型
struct Node
{
	Node(int data = 0)
		: data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{
	}

	int data_;    // 数据域
	Node* pre_;   // 指向前一个节点
	Node* next_;  // 指向后一个节点
};


class DoubleCircleLink
{
public:
	DoubleCircleLink()
	{
		head_ = new Node();
		head_->pre_ = head_->next_ = head_;
	}

	~DoubleCircleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			p->next_->pre_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}

	// 头插法 O(1)
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_;
		node->next_ = head_->next_;
		head_->next_->pre_ = node;
		head_->next_ = node;
	}

	// 尾插法 O(1)
	void InsertTail(int val)
	{
		// head_->pre_既是尾节点，所以不需要遍历到尾节点
		Node* node = new Node(val);
		node->pre_ = head_->pre_;
		node->next_ = head_;
		head_->pre_->next_ = node;
		head_->pre_ = node;
	}

	// 节点删除
	void Remove(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				delete p;
				return;
			}

			p = p->next_;
		}
	}

	// 查找
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				return true;
			}

			p = p->next_;
		}

		return false;
	}

	// 打印链表
	void Show()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}

private:
	Node* head_;  // 头节点
};

int main()
{
	DoubleCircleLink dlink;

	dlink.InsertHead(100);

	dlink.InsertTail(20);
	dlink.InsertTail(12);
	dlink.InsertTail(78);
	dlink.InsertTail(32);
	dlink.InsertTail(7);
	dlink.InsertTail(90);
	dlink.Show();

	dlink.InsertHead(200);
	dlink.Show();

	dlink.Remove(200);
	dlink.Show();

	dlink.Remove(90);
	dlink.Show();

	dlink.Remove(78);
	dlink.Show();

	if (dlink.Find(20))
	{
		cout << "找到20" << endl;
	}

	if (dlink.Find(200))
	{
		cout << "找到200" << endl;
	}
}