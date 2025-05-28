#include <iostream>

using namespace std;

/*
* ˫������
*/

// ����˫������Ľڵ�����
struct Node
{
	Node(int data = 0)
		: data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{
	}

	int data_;    // ������
	Node* pre_;   // ָ��ǰһ���ڵ�
	Node* next_;  // ָ���һ���ڵ�
};

// ˫������
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
private:
	Node* head_;  // ָ��ͷ�ڵ�
};