#include <iostream>

using namespace std;

/*
* 双向链表
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

// 双向链表
class DoubleLink
{
public:
	DoubleLink()
	{
		head_ = new Node();
	}

	~DoubleLink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

	// 头插法
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_;
		node->next_ = head_->next_;
		if(head_->next_ != nullptr)  // 此条件判断可以完美适配链表为空和不空两种状态的插入行为
			head_->next_->pre_ = node;
		head_->next_ = node;
	}

	// 尾插法
	void InsertTail(int val)
	{
		Node* p = head_;

		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		Node* node = new Node(val);
		node->pre_ = p;
		p->next_ = node;
	}

	// 删除节点
	void Remove(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr)
					p->next_->pre_ = p->pre_;
				//Node* q = p->next_;  //删除多个
				delete p;
				//p = q;
				return;
			}

			p = p->next_;
		}
	}

	// 查找
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
				return true;
			p = p->next_;
		}

		return false;
	}

	// 打印链表
	void Show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
	Node* head_;  // 指向头节点
};

int main()
{
	DoubleLink dlink;

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