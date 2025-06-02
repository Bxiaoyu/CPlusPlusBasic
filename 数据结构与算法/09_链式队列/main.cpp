#include <iostream>

using namespace std;

/*
* ��ʽ���У�����˫��ѭ������
*/

class LinkQueue
{
public:
	LinkQueue()
		: size_(0)
	{
		head_ = new Node();
		head_->pre_ = head_->next_ = head_;
	}

	~LinkQueue()
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

public:
	// ��ӣ���β�룬��ͷ��
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_;
		node->pre_ = head_->pre_;
		head_->pre_->next_ = node;
		head_->pre_ = node;
		size_++;
	}

	// ����
	void pop()
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";

		Node* p = head_->next_;
		head_->next_ = p->next_;
		p->next_->pre_ = head_;
		delete p;
		size_--;
	}

	// ��ȡ��ͷԪ��
	int front() const
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";
		return head_->next_->data_;
	}

	// ��ȡ��βԪ��
	int back() const
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";
		return head_->pre_->data_;
	}

	// �п�
	bool empty() const
	{
		return head_->next_ == head_;
	}

	// ��ȡԪ�ظ���
	int size() const
	{
		return size_;
	}
private:
	struct Node
	{
		Node(int data = 0)
			: data_(data)
			, pre_(nullptr)
			, next_(nullptr)
		{
		}

		int data_;
		Node* pre_;
		Node* next_;
	};

	Node* head_;
	int size_;  // ����Ԫ�ظ���
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkQueue que;

	for (int v : arr)
	{
		que.push(v);
	}

	cout << que.front() << endl;
	cout << que.back() << endl;

	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.front() << endl;
	cout << que.back() << endl;

	while (!que.empty())
	{
		cout << que.front() << " " << que.back() << endl;
		que.pop();
	}
	return 0;
}