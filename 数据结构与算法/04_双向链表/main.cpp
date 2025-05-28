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
private:
	Node* head_;  // 指向头节点
};