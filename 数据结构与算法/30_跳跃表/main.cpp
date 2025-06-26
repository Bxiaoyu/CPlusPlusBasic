#include <iostream>

using namespace std;

// ��Ծ��SkipList
class SkipList
{
public:
	SkipList()
	{
		head_ = new HeadNode(1);
	}

	~SkipList()
	{
		int level = head_->level_;
		for (int i = 0; i < level; i++)
		{
			Node* cur = head_->next_;
			while (cur != nullptr)
			{
				Node* tmp = cur->next_;
				delete cur;
				cur = tmp;
			}

			cur = head_;
			head_ = static_cast<HeadNode*>(head_->down_);
			delete cur;
		}
	}

public:
	// ��������
	bool find(int data)
	{
		Node* pre = head_;
		Node* cur = pre->next_;

		for (;;)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
					continue;
				}
				else if (cur->data_ == data)
				{
					return true;
				}
			}

			// cur == nullptr
			if (pre->down_ == nullptr)
			{
				// pre��cur�Ѿ���������һ���ĩβ��
				break;
			}

			pre = pre->down_;
			cur = pre->next_;
		}

		return false;
	}

	// ��������
	void add(int data)
	{
		// �Ȳ��������Ƿ����
		if (find(data))
		{
			return;
		}

		// ��Ӳ�ң�data������Ӽ���
		int level = getLevel();
		if (level > head_->level_)
		{
			// level����ʱ��SkipListֻ����һ��
			level = head_->level_ + 1;
			HeadNode* hnode = new HeadNode(level);
			hnode->down_ = head_;
			head_ = hnode;
		}

		// �ȴ���level���data�ڵ㣬�޸�downָ����
		Node** nodeList = new Node* [level];
		for (int i = level - 1; i >= 0;i--)
		{
			nodeList[i] = new Node(data);
			if (i < level - 1)
			{
				// �ϲ�ڵ��downָ���򣬴洢�²�ڵ�ĵ�ַ
				nodeList[i]->down_ = nodeList[i + 1];
			}
		}

		Node* head = head_;
		for (int i = head_->level_; i > level; i--)
		{
			head = head->down_;
		}

		// head��ָ����Ҫ����ڵ��������
		Node* pre = head;
		Node* cur = pre->next_;

		for (int i = 0; i < level; i++)
		{
			while (cur != nullptr && cur->data_ < data)
			{
				pre = cur;
				cur = cur->next_;
			}

			// �½ڵ���뵽pre��cur�м�
			nodeList[i]->next_ = cur;
			pre->next_ = nodeList[i];

			pre = pre->down_;
			if (pre != nullptr)
			{
				cur = pre->next_;
			}
		}

		delete[] nodeList;
		nodeList = nullptr;
	}

	// ɾ������
	void remove(int data)
	{
		Node* pre = head_;
		Node* cur = pre->next_;

		for (;;)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
					continue;
				}
				else if (cur->data_ == data)
				{
					// ɾ��curָ��Ľڵ�
					pre->next_ = cur->next_;
					delete cur;
				}
			}

			if (pre->down_ == nullptr)
			{
				break;
			}

			// cur == nullptr ��ǰ��û��data�ڵ�
			pre = pre->down_;
			if (head_->next_ == nullptr)
			{
				delete head_;
				head_ = static_cast<HeadNode*>(pre);
			}
			cur = pre->next_;
		}
	}

	// ��ӡ
	void show() const
	{
		Node* head = head_;
		while (head != nullptr)
		{
			Node* cur = head->next_;
			while (cur != nullptr)
			{
				cout << cur->data_ << " ";
				cur = cur->next_;
			}
			cout << endl;
			head = head->down_;
		}
		cout << endl;
	}

private:
	struct Node
	{
		Node(int data = int())
			: data_(data)
			, next_(nullptr)
			, down_(nullptr)
		{
		}

		int data_;    // ������
		Node* next_;  // ָ��ͬһ���һ���ڵ��ָ����
		Node* down_;  // ָ����һ����ͬ�ڵ��ָ����
	};

	// ��Ծ���ͷ�ڵ�����
	struct HeadNode : public Node
	{
		HeadNode(int level)
			: level_(level)
		{
		}
		int level_;
	};

private:
	HeadNode* head_;  // ָ���������ϲ������ͷ�ڵ�

private:
	int getLevel() const
	{
		int level = 1;
		while (rand() % 2 == 1)
		{
			level++;
		}
		return level;
	}
};

int main()
{
	SkipList list;
	srand(time(nullptr));

	for (int i = 0; i < 20; i++)
	{
		list.add(rand() % 100);
	}

	list.add(50);
	list.show();

	list.remove(50);
	list.show();

	return 0;
}