#include <iostream>

using namespace std;

/*
* 单链表，带头结点
*/

// 节点类型
struct Node
{
	Node(int data = 0) :data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 单链表
class CLink
{
public:
	CLink()
	{
		// 给head_初始化指向头节点
		head_ = new Node();
	}

	~CLink()
	{
		// 节点的释放
	}

public:
	// 链表尾插法 O(n)
	void insertTail(int val)
	{
		// 先找到当前链表的尾节点(特征：尾节点地址域为nullptr)
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// 生成新节点
		Node* node = new Node(val);
		// 把新节点挂在尾节点后面
		p->next_ = node;
	}

	// 链表的头插法 O(1)
	void insertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}

	// 链表节点的删除，删除第一个匹配的节点
	void remove(int val)
	{
		Node* p = head_;
		Node* q = p->next_;
		while (q != nullptr && q->data_ != val)
		{
			p = q;
			q = q->next_;
		}

		if (p == q) return;
		p->next_ = q->next_;
		delete q;
	}

	// 打印链表
	void show()
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
	Node* head_;  // 指向链表头节点
};

int main()
{
	CLink link;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int val = rand() % 100;
		link.insertHead(val);
	}
	link.show();
}