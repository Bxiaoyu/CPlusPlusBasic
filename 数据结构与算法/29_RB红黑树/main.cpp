#include <iostream>
#include <queue>
using namespace std;

/*
* �����������ԣ�
* 1��ÿһ���ڵ㶼����ɫ�����Ǻ�ɫ���Ǻ�ɫ��
* 2��nullptr�Ǻ�ɫ��
* 3��Root���ڵ�����Ǻ�ɫ��
* 4�����ܳ��������ĺ�ɫ�ڵ㣬���׺�ɫ������һ�����Ǻ�ɫ����������к�ɫ�ڵ㣬���׿϶��Ǻ�ɫ��
* 5���Ӹ��ڵ㿪ʼ��������һ��Ҷ�ӽڵ��·���ϣ���ɫ�ڵ���������뱣��һ�¡�
*/

// �����
template<typename T>
class RBTree
{
public:
	RBTree() :root_(nullptr) {}

	~RBTree()
	{
		if (root_ != nullptr)
		{
			queue<Node*> q;
			q.push(root_);

			while (!q.empty())
			{
				Node* front = q.front();
				q.pop();
				if (front->left_ != nullptr)
				{
					q.push(front->left_);
				}
				if (front->right_ != nullptr)
				{
					q.push(front->right_);
				}

				delete front;
			}
		}
	}

	// �������
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}

		Node* node = new Node(val, parent, nullptr, nullptr, Color::RED);
		if (parent->data_ > val)
		{
			parent->left_ = node;
		}
		else
		{
			parent->right_ = node;
		}

		// ����²���ĺ�ɫ�ڵ㣬�丸�ڵ�Ҳ�Ǻ�ɫ���������������ʣ����в������
		if (Color::RED == color(parent))
		{
			fixAfterInsert(node);
		}
	}

	// ɾ������
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}

		if (cur == nullptr)
		{
			return;
		}

		// ɾ��ǰ���ڵ㣬�����
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;  // curָ��ǰ���ڵ�
		}

		// ɾ��curָ��Ľڵ㣬���һ�Ͷ�
		Node* child = cur->left_;  // ��childָ��Ϊ�յĺ���
		if (child == nullptr)
		{
			child = cur->right_;
		}

		// left,right,parent
		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				// root_ -> cur
				root_ = child;
			}
			else
			{
				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}

			Color c = color(cur);
			delete cur;

			if (c == Color::BLACK)  // ɾ�����Ǻ�ɫ�ڵ㣬Ҫ����ɾ����������
			{
				fixAfterRemove(child);
			}
		}
		else
		{
			if (cur->parent_ == nullptr)
			{
				delete cur;
				root_ = nullptr;
				return;
			}
			else
			{
				// ɾ����cur����Ҷ�ӽڵ�
				if (color(cur) == Color::BLACK)
				{
					fixAfterRemove(cur);
				}

				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = nullptr;
				}
				else
				{
					cur->parent_->right_ = nullptr;
				}

				delete cur;
			}
		}
	}

private:
	// �ڵ���ɫ
	enum class Color
	{
		BLACK,
		RED
	};

	// �ڵ�����
	struct Node
	{
		Node(T data = T(), Node* parent = nullptr, Node* left = nullptr, 
			Node* right = nullptr, Color color = Color::BLACK)
			: data_(data)
			, left_(left)
			, right_(right)
			, parent_(parent)
			, color_(color)
		{
		}

		T data_;
		Node* left_;
		Node* right_;
		Node* parent_;  // ָ��ǰ�ڵ�ĸ��ڵ�
		Color color_;   // �ڵ����ɫ 
	};

	Node* root_;  // ָ�������ĸ��ڵ�

private:
	// ��ȡ�ڵ���ɫ
	Color color(Node* node)
	{
		return node == nullptr ? Color::BLACK : node->color_;
	}

	// ���ýڵ���ɫ
	void setColor(Node* node, Color color)
	{
		node->color_ = color;
	}

	// ���ؽڵ������
	Node* left(Node* node)
	{
		return node->left_;
	}

	// ���ؽڵ���Һ���
	Node* right(Node* node)
	{
		return node->right_;
	}

	// ���ؽڵ�ĸ���
	Node* parent(Node* node)
	{
		return node->parent_;
	}

	// ����ת
	void leftRotate(Node* node)
	{
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			// node������Ǹ��ڵ�
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				// node�Ǹ��ڵ������
				node->parent_->left_ = child;
			}
			else
			{
				// node�Ǹ��ڵ���Һ���
				node->parent_->right_ = child;
			}
		}

		node->right_ = child->left_;
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}

		child->left_ = node;
		node->parent_ = child;
	}

	// ����ת
	void rightRotate(Node* node)
	{
		Node* child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			// nodeԭ�����Ǹ��ڵ�
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				// node�ڸ��ڵ����
				node->parent_->left_ = child;
			}
			else
			{
				// node�ڸ��ڵ��ұ�
				node->parent_->right_ = child;
			}
		}

		node->left_ = child->right_;
		if (child->right_ != nullptr)
		{
			child->right_->parent_ = node;
		}

		child->right_ = node;
		node->parent_ = child;
	}

	// ������Ĳ����������
	void fixAfterInsert(Node* node)
	{
		// �����ǰ��ɫ�ڵ�ĸ��ڵ�Ҳ�Ǻ�ɫ����������
		while (color(parent(node)) == Color::RED)
		{
			// ���үү���������ҵĸ���
			if (left(parent(parent(node))) == parent(node))
			{
				// ����Ľڵ�������������
				Node* uncle = right(parent(parent(node)));
				if (Color::RED == color(uncle))  // ���һ
				{
					setColor(parent(node), Color::BLACK);
					setColor(uncle, Color::BLACK);
					setColor(parent(parent(node)), Color::RED);
					node = parent(parent(node));  // �ֲ�������ϣ������������
				}
				else
				{
					// �ȴ��������
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}

					// ͳһ���������
					setColor(parent(node), Color::BLACK);
					setColor(parent(parent(node)), Color::RED);
					rightRotate(parent(parent(node)));
					break;  // �����Ѿ����
				}
			}
			else
			{
				// ����Ľڵ�������������
				Node* uncle = left(parent(parent(node)));
				if (Color::RED == color(uncle))  // ���һ
				{
					setColor(parent(node), Color::BLACK);
					setColor(uncle, Color::BLACK);
					setColor(parent(parent(node)), Color::RED);
					node = parent(parent(node));  // �ֲ�������ϣ������������
				}
				else
				{
					// �ȴ��������
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}

					// ͳһ���������
					setColor(parent(node), Color::BLACK);
					setColor(parent(parent(node)), Color::RED);
					leftRotate(parent(parent(node)));
					break;  // �����Ѿ����
				}
			}
		}

		// �˴�ǿ��rootΪ��ɫ�ڵ�
		setColor(root_, Color::BLACK);
	}
	
	// �������ɾ����������
	void fixAfterRemove(Node* node)
	{
		while (node	!= root_ && color(node) == Color::BLACK)
		{
			if (left(parent(node)) == node)
			{
				// ɾ���ĺ�ɫ�ڵ���������
				Node* brother = right(parent(node));
				if (color(brother) == Color::RED)  // �����
				{
					setColor(parent(node), Color::RED);
					setColor(brother, Color::BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}

				if (color(left(brother)) == Color::BLACK && color(right(brother)) == Color::BLACK)  // �����
				{
					setColor(brother, Color::RED);
					node = parent(node);
				}
				else
				{
					if (color(right(brother)) != Color::RED)  // �����
					{
						setColor(brother, Color::RED);
						setColor(left(brother), Color::BLACK);
						rightRotate(brother);
						brother = right(parent(node));
					}

					// ��ᵽ���һ
					setColor(brother, color(parent(node)));
					setColor(parent(node), Color::BLACK);
					setColor(right(brother), Color::BLACK);
					leftRotate(parent(node));
					break;
				}
			}
			else
			{
				// ɾ���ĺ�ɫ�ڵ���������
				Node* brother = left(parent(node));
				if (color(brother) == Color::RED)  // �����
				{
					setColor(parent(node), Color::RED);
					setColor(brother, Color::BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}

				if (color(left(brother)) == Color::BLACK && color(right(brother)) == Color::BLACK)  // �����
				{
					setColor(brother, Color::RED);
					node = parent(node);
				}
				else
				{
					if (color(left(brother)) != Color::RED)  // �����
					{
						setColor(brother, Color::RED);
						setColor(right(brother), Color::BLACK);
						leftRotate(brother);
						brother = left(parent(node));
					}

					// ��ᵽ���һ
					setColor(brother, color(parent(node)));
					setColor(parent(node), Color::BLACK);
					setColor(left(brother), Color::BLACK);
					rightRotate(parent(node));
					break;
				}
			}
		}

		// ���nodeָ��Ľڵ��Ǻ�ɫ��ֱ��Ϳ�ɺ�ɫ����������
		setColor(node, Color::BLACK);
	}
};

int main()
{
	RBTree<int> rb;
	for (int i = 1; i <= 10; ++i)
	{
		rb.insert(i);
	}

	rb.remove(9);
	rb.remove(10);
	rb.remove(5);
	rb.remove(3);

	return 0;
}