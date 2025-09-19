#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Node
{
	int val_;
	Node* next_;
	Node(int x) :val_(x), next_(nullptr) {}
};


Node* init_link(initializer_list<int> list)
{
	Node* head = nullptr;
	Node* p = nullptr;
	for (int v : list)
	{
		if (head == nullptr)
		{
			head = new Node(v);
			p = head;
		}
		else
		{
			p->next_ = new Node(v);
			p = p->next_;
		}
	}

	return head;
}

Node* merge_two_link(Node* p1, Node* p2)
{
	Node* head = nullptr;
	if (p1 == nullptr)
	{
		return p2;
	}

	if (p2 == nullptr)
	{
		return p1;
	}

	if (p1->val_ > p2->val_)
	{
		head = p2;
		p2 = p2->next_;
	}
	else
	{
		head = p1;
		p1 = p1->next_;
	}

	Node* p = head;
	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1->val_ > p2->val_)
		{
			p->next_ = p2;
			p = p2;
			p2 = p2->next_;
		}
		else
		{
			p->next_ = p1;
			p = p1;
			p1 = p1->next_;
		}
	}

	if (p1 != nullptr)
		p->next_ = p1;

	if (p2 != nullptr)
		p->next_ = p2;

	return head;
}

Node* merge_link(vector<Node*> link, int i, int j)
{
	if (i >= j)  // 子问题划分只剩一个链表了
	{
		return link[i];
	}

	int mid = (i + j) / 2;
	Node* left = merge_link(link, i, mid);
	Node* right = merge_link(link, mid + 1, j);
	return merge_two_link(left, right);  // 归结成合并两个有序链表
}

#if 0
int main()
{
	Node* p1 = init_link({ 3,6,8 });
	Node* p2 = init_link({ 2,4 });
	Node* p3 = init_link({ 1,5,9 });
	Node* p4 = init_link({ 0,7 });
	Node* p5 = init_link({ 10 });
	vector<Node*> vec;
	vec.push_back(p1);
	vec.push_back(p2);
	vec.push_back(p3);
	vec.push_back(p4);
	vec.push_back(p5);

	Node* p = merge_link(vec, 0, vec.size() - 1);

	for (Node* c = p; c != nullptr; c = c->next_)
	{
		cout << c->val_ << " ";
	}
	cout << endl;
}
#endif