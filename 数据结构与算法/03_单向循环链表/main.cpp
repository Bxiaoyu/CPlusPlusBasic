#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
* 单向循环链表（带头节点）
*/
class CircleLink
{
public:
	CircleLink()
	{
		head_ = new Node();  // 头节点
		tail_ = head_;
		head_->next_ = head_;
	}

	~CircleLink()
	{
		Node* p = head_->next_;  // 指向第一个节点
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}

public:
	// 尾插法
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_;
		tail_->next_ = node;
		tail_ = node;  // 更新tail指针指向新的尾节点
	}

	// 头插法
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		// 要注意空链表情况下对于tail_节点的处理
		if (node->next_ == head_)
		{
			tail_ = node;
		}
	}

	// 删除节点
	void Remove(int val)
	{
		Node* p = head_;
		Node* q = head_->next_;

		while (q != head_)
		{
			if (q->data_ == val)
			{
				p->next_ = q->next_;
				delete q;
				if (p->next_ == head_)  // 考虑删除的如果是最后一个节点，要更新tail_
				{
					tail_ = p;
				}
				return;
			}
			else
			{
				p = q;
				q = q->next_;
			}
		}
	}

	// 查询
	bool Find(int val) const
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

	// 打印
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
	struct Node
	{
		Node(int data = 0):data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;  // 指向头节点
	Node* tail_;  // 指向尾节点
};
#if 0
int main()
{
	CircleLink clink;
	srand(time(NULL));

	clink.InsertHead(100);

	for (int i = 0; i < 10; i++)
	{
		clink.InsertTail(rand() % 100);
	}

	clink.InsertTail(200);
	clink.Show();

	clink.Remove(200);
	clink.Show();

	clink.InsertTail(300);
	clink.Show();

	if (clink.Find(300))
	{
		cout << "find data" << endl;
	}
}
#endif

/*
* 约瑟夫环问题（这里用不带头结点的单向循环链表，与leetcode对齐）
*/
struct Node
{
	Node(int data):data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

void Joseph(Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;

	// p指向最后一个节点，因为没有头节点，这样做可以防止k=1，m=1时出现p==q判断错误
	while (p->next_ != head)
	{
		p = p->next_;
	}

	// 从第k个人开始报数的
	for (int i = 1; i < k; i++)
	{
		p = q;
		q = q->next_;
	}

	for (;;)
	{
		for (int i = 1; i < m; i++)
		{
			p = q;
			q = q->next_;
		}

		// 打印q
		cout << q->data_ << " ";

		if (p == q)  // 相当于是最后一个节点了
		{
			delete q;
			break;
		}
		// 删除q指向的节点
		p->next_ = q->next_;
		delete q;
		q = p->next_;
	}
}

int main()
{
	Node* head = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);

	head->next_ = n2;
	n2->next_ = n3;
	n3->next_ = n4;
	n4->next_ = n5;
	n5->next_ = n6;
	n6->next_ = n7;
	n7->next_ = n8;
	n8->next_ = head;

	Joseph(head, 1, 3);
}