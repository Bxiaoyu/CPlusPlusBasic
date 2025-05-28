#include <iostream>

using namespace std;

/*
* ��������ͷ���
*/

// �ڵ�����
struct Node
{
	Node(int data = 0) :data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// ������
class CLink
{
public:
	CLink()
	{
		// ��head_��ʼ��ָ��ͷ�ڵ�
		head_ = new Node();
	}

	~CLink()
	{
		// �ڵ���ͷ�
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
	// ����β�巨 O(n)
	void insertTail(int val)
	{
		// ���ҵ���ǰ�����β�ڵ�(������β�ڵ��ַ��Ϊnullptr)
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// �����½ڵ�
		Node* node = new Node(val);
		// ���½ڵ����β�ڵ����
		p->next_ = node;
	}

	// �����ͷ�巨 O(1)
	void insertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}

	// ����ڵ��ɾ����ɾ����һ��ƥ��Ľڵ�
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

	// ����ڵ�ɾ����ɾ������ڵ�
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
				// ��ָ��q��������
				q = p->next_;
			}
			else
			{
				p = q;
				q = q->next_;
			}
		}
	}

	// ���� O(n)
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

	// ��ӡ����
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
	Node* head_;  // ָ������ͷ�ڵ�

	friend void ReverseList(CLink& list);
	friend bool GetLaskKNode(CLink& link, int k, int& val);
	friend void MergeLink(CLink& link1, CLink& link2);
};

// ����������
void ReverseList(CLink& list)
{
	Node* head = list.head_;
	Node* p = head->next_;
	if (p == nullptr) return;

	head->next_ = nullptr;

	while (p != nullptr)
	{
		Node* q = p->next_;
		// pָ��ָ��Ľڵ����ͷ��
		p->next_ = head->next_;
		head->next_ = p;
		p = q;
	}
}

// ������k���ڵ��ֵ
bool GetLaskKNode(CLink& link, int k, int& val)
{
	// ��ʼָ�붼ָ��ͷ�ڵ㣬������
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

	// pre��ͷ�ڵ㣬p��������k���ڵ�
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}

	val = pre->data_;
	return true;
}

// �ϲ�������������
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

// �жϵ������Ƿ���ڻ������ڷ��ػ�����ڽڵ�
/*
* ����һ���򵥴ֱ����ö����ϣ��洢�ڵ��ַ�����Ƿ��ظ�������ͬ��ַ
* ��������˫ָ��-����ָ��
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
			// ����ָ���ٴ�������������ڻ�
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


// �ж������������Ƿ��ཻ������ཻ�������ཻ�ڵ��ֵ
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

	// �Ƚ������ȣ��ϳ���������ǰ��������Ȼ���ڿ�ʼ��������һ��ǰ��
	p = head1;
	q = head2;
	if (cnt1 > cnt2)
	{
		// ��һ������
		int offset = cnt1 - cnt2;
		while (offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		// �ڶ�������
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
		cout << "������3���ڵ��ֵΪ��" << kval << endl;
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
		cout << "������ڻ���������ڽڵ��ǣ�" << val << endl;
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
		cout << "�����ཻ���ཻ�ڵ��ǣ�" << val << endl;
	}
}
#endif