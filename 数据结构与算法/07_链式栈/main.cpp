#include <iostream>

using namespace std;

/*
* ��ʽջ
*/
class LinkStack
{
public:
	LinkStack():size_(0)
	{
		head_ = new Node();
	}

	~LinkStack()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

public:
	// ��ջ������ͷ�巨��O(1)
	void push(int val)
	{
		// head_->1
		// head_->2->1
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}

	// ��ջ���� O(1)
	void pop()
	{
		if (head_->next_ == nullptr)
			throw "Stack is empty!";

		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}

	// ��ȡջ��Ԫ��
	int top() const
	{
		if (head_->next_ == nullptr)
			throw "Stack is empty!";
		return head_->next_->data_;
	}

	// �п�
	bool empty() const
	{
		return head_->next_ == nullptr;
	}

	// ջԪ�ظ���
	int size() const
	{
		return size_;
	}
private:
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;  // ͷ�ڵ�
	int size_;    // ջԪ�ظ���
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkStack s;

	for (int v : arr)
	{
		s.push(v);
	}

	cout << "stack size = " << s.size() << endl;

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << "stack size = " << s.size() << endl;
	cout << "ջ" << (s.empty() ? "��" : "�ǿ�") << endl;
}