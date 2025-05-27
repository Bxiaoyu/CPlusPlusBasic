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