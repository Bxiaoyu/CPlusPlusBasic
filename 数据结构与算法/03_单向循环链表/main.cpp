#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
* ����ѭ��������ͷ�ڵ㣩
*/
class CircleLink
{
public:
	CircleLink()
	{
		head_ = new Node();  // ͷ�ڵ�
		tail_ = head_;
		head_->next_ = head_;
	}

	~CircleLink()
	{
		Node* p = head_->next_;  // ָ���һ���ڵ�
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}

public:
	// β�巨
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_;
		tail_->next_ = node;
		tail_ = node;  // ����tailָ��ָ���µ�β�ڵ�
	}

	// ͷ�巨
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		// Ҫע�����������¶���tail_�ڵ�Ĵ���
		if (node->next_ == head_)
		{
			tail_ = node;
		}
	}

	// ɾ���ڵ�
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
				if (p->next_ == head_)  // ����ɾ������������һ���ڵ㣬Ҫ����tail_
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

	// ��ѯ
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

	// ��ӡ
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

	Node* head_;  // ָ��ͷ�ڵ�
	Node* tail_;  // ָ��β�ڵ�
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
* Լɪ�����⣨�����ò���ͷ���ĵ���ѭ��������leetcode���룩
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

	// pָ�����һ���ڵ㣬��Ϊû��ͷ�ڵ㣬���������Է�ֹk=1��m=1ʱ����p==q�жϴ���
	while (p->next_ != head)
	{
		p = p->next_;
	}

	// �ӵ�k���˿�ʼ������
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

		// ��ӡq
		cout << q->data_ << " ";

		if (p == q)  // �൱�������һ���ڵ���
		{
			delete q;
			break;
		}
		// ɾ��qָ��Ľڵ�
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