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
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}

		head_ = nullptr;
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
		Node* q = head_->next_;
		while (q != nullptr)
		{
			if (q->data_ == val)
			{
				p->next_ = q->next_;
				delete q;
				return;
			}
			else
			{
				p = q;
				q = q->next_;
			}
		}
	}

	// 链表节点删除，删除多个节点
	void removeAll(int val)
	{
		Node* p = head_;
		Node* q = head_->next_;
		while (q != nullptr)
		{
			if (q->data_ == val)
			{
				p->next_ = q->next_;
				delete q;
				// 对指针q进行重置
				q = p->next_;
			}
			else
			{
				p = q;
				q = q->next_;
			}
		}
	}

	// 查找 O(n)
	bool find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			else
			{
				p = p->next_;
			}
		}

		return false;
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

	friend void ReverseList(CLink& list);
	friend bool GetLaskKNode(CLink& link, int k, int& val);
	friend void MergeLink(CLink& link1, CLink& link2);
};

// 单链表逆序
void ReverseList(CLink& list)
{
	Node* head = list.head_;
	Node* p = head->next_;
	if (p == nullptr) return;

	head->next_ = nullptr;

	while (p != nullptr)
	{
		Node* q = p->next_;
		// p指针指向的节点进行头插
		p->next_ = head->next_;
		head->next_ = p;
		p = q;
	}
}

// 求倒数第k个节点的值
bool GetLaskKNode(CLink& link, int k, int& val)
{
	// 初始指针都指向头节点，更方便
	Node* head = link.head_;
	Node* pre = head;
	Node* p = head;

	if (k < 1)
	{
		return false;
	}

	for (int i = 0; i < k; i++)
	{
		p = p->next_;
		if (p == nullptr)
		{
			return false;
		}
	}

	// pre在头节点，p在正数第k个节点
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}

	val = pre->data_;
	return true;
}

// 合并两个有序单链表
void MergeLink(CLink& link1, CLink& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr;

	while (p != nullptr && q != nullptr)
	{
		if (p->data_ < q->data_)
		{
			last->next_ = p;
			p = p->next_;
			last = last->next_;
		}
		else
		{
			last->next_ = q;
			q = q->next_;
			last = last->next_;
		}
	}

	if (p != nullptr)
	{
		last->next_ = p;
	}
	
	if (q != nullptr)
	{
		last->next_ = q;
	}
}

// 判断单链表是否存在环，存在返回环的入口节点
/*
* 方法一：简单粗暴，用额外哈希表存储节点地址，看是否重复出现相同地址
* 方法二：双指针-快慢指针
*/
bool IsLinkHasCircle(Node* head, int& val)
{
	Node* fast = head;
	Node* slow = head;

	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;

		if (slow == fast)
		{
			// 快慢指针再次相遇，代表存在环
			fast = head;
			while (slow != fast)
			{
				slow = slow->next_;
				fast = fast->next_;
			}

			val = slow->data_;
			return true;
		}
	}

	return false;
}


// 判断两个单链表是否相交，如果相交，返回相交节点的值
bool IsLinkHasMerge(Node* head1, Node* head2, int& val)
{
	int cnt1 = 0, cnt2 = 0;
	Node* p = head1->next_;
	Node* q = head2->next_;

	while (p != nullptr)
	{
		cnt1++;
		p = p->next_;
	}

	while (q != nullptr)
	{
		cnt2++;
		q = q->next_;
	}

	// 比较链表长度，较长的链表先前进相差步长，然后在开始两个链表一起前进
	p = head1;
	q = head2;
	if (cnt1 > cnt2)
	{
		// 第一个链表长
		int offset = cnt1 - cnt2;
		while (offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		// 第二个链表长
		int offset = cnt2 - cnt1;
		while (offset-- > 0)
		{
			q = q->next_;
		}
	}

	// 
	while (p != nullptr && q != nullptr)
	{
		if (p == q)
		{
			val = p->data_;
			return true;
		}
		p = p->next_;
		q = q->next_;
	}

	return false;
}

#if 0
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
	link.insertTail(23);
	link.insertHead(23);
	link.insertHead(23);

	link.show();

	link.removeAll(23);
	link.show();
	//ReverseList(link);
	//link.show();

	int kval;
	if (GetLaskKNode(link, 3, kval))
	{
		cout << "倒数第3个节点的值为：" << kval << endl;
	}
}
#endif

#if 0
int main()
{
	int arr[] = { 25, 37, 52, 78, 88, 92, 98, 108 };
	int brr[] = { 13, 23, 40, 56, 62, 77, 109 };

	CLink link1;
	CLink link2;

	for (int v : arr)
	{
		link1.insertTail(v);
	}

	for (int v : brr)
	{
		link2.insertTail(v);
	}

	link1.show();
	link2.show();

	MergeLink(link1, link2);
	link1.show();
	link2.show();
}
#endif

#if 0
int main()
{
	Node head;

	Node n1(25), n2(67), n3(32), n4(18);
	head.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	n4.next_ = &n2;

	int val;
	if (IsLinkHasCircle(&head, val))
	{
		cout << "链表存在环，环的入口节点是：" << val << endl;
	}
}
#endif

#if 1
int main()
{
	Node head1;
	Node n1(25), n2(67), n3(32), n4(18);
	head1.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;

	Node head2;
	Node n5(31);
	head2.next_ = &n5;
	n5.next_ = &n3;

	int val;
	if (IsLinkHasMerge(&head1, &head2, val))
	{
		cout << "链表相交，相交节点是：" << val << endl;
	}
}
#endif