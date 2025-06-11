#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// BST树代码实现
template<typename T, typename Comp=less<T>>
class BSTree
{
public:
	BSTree(Comp	comp = Comp()) : root_(nullptr), comp_(comp) {}

	~BSTree() {}

public:
	// 非递归插入操作
	void n_insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;  // 记录父节点
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				// 不插入元素相同的值
				return;
			}
			else if (comp_(cur->data_, val))  // 小于关系
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		if (comp_(val, parent->data_))  // 小于
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}

	// 递归插入操作
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}

	// 非递归删除操作
	void n_remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;  // 找到待删除节点
			}
			else if (comp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		// 没找到待删除节点
		if (cur == nullptr)
		{
			return;
		}

		// 情况3，删除前驱节点（归结为情况1，2）
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;  // 让cur指向前驱节点，转化为情况1，2
		}

		// cur指向删除节点，parent指向其父节点，统一处理情况1或者2
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)  // 特殊情况，表示删除的是根节点
		{
			root_ = child;
		}
		else
		{
			// 把待删除节点的孩子（nullptr或者not nullptr）写入其父节点相应地址域中
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}

		delete cur;  // 删除当前节点
	}

	// 递归删除操作
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}

	// 非递归查询操作
	bool n_query(const T& val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (comp_(cur->data_, val))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}

		return false;
	}

	// 递归查询操作
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}

	// 递归前序遍历
	void preOrder()
	{
		cout << "[递归]前序遍历：";
		preOrder(root_);
		cout << endl;
	}

	// 非递归前序遍历
	void n_preOrder()
	{
		cout << "[非递归]前序遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		stack<Node*> s;
		s.push(root_);
		while (!s.empty())
		{
			Node* p = s.top();
			s.pop();
			cout << p->data_ << " ";  // V
			if (p->right_ != nullptr)  // R 右孩子先入栈
			{
				s.push(p->right_);
			}
			if (p->left_ != nullptr)  // L
			{
				s.push(p->left_);
			}
		}
		cout << endl;
	}

	// 递归中序遍历（升序过程）
	void inOrder()
	{
		cout << "[递归]中序遍历：";
		inOrder(root_);
		cout << endl;
	}

	// 非递归中序遍历
	void n_inOrder()
	{
		cout << "[非递归]中序遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		stack<Node*> s;
		Node* cur = root_;
		while (cur != nullptr || !s.empty())
		{
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_;
			}
			else
			{
				Node* top = s.top();
				s.pop();
				cout << top->data_ << " ";
				cur = top->right_;
			}
		}
		cout << endl;
	}

	// 递归后序遍历
	void postOrder()
	{
		cout << "[递归]后序遍历：";
		postOrder(root_);
		cout << endl;
	}

	// 非递归后续遍历
	void n_postOrder()
	{
		cout << "[非递归]后续遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		stack<Node*> s1;
		stack<Node*> s2;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();

			s2.push(top);  // V
			if (top->left_ != nullptr)  // L
			{
				s1.push(top->left_);
			}
			if (top->right_ != nullptr)  // R
			{
				s1.push(top->right_);  
			}
		}

		while (!s2.empty())
		{
			cout << s2.top()->data_ << " ";
			s2.pop();
		}

		cout << endl;
	}

	// 递归层序遍历
	void levelOrder()
	{
		cout << "[递归]层序遍历：";
		int h = high();  // 树的层数
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);  // 递归调用树的层数
		}
		cout << endl;
	}

	// 非递归层序遍历
	void n_levelOrder()
	{
		cout << "[非递归]层序遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		queue<Node*> que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			cout << front->data_ << " ";
			if (front->left_ != nullptr)
			{
				que.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				que.push(front->right_);
			}
		}

		cout << endl;
	}

	// 递归求二叉树层数（高度）
	int high()
	{
		return high(root_);
	}

	// 递归求二叉树节点个数
	int number()
	{
		return number(root_);
	}

	// 求满足区间的元素值[i,j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}

	// 判断二叉树是否是BST树
	bool isBSTree()
	{
		return isBSTree(root_);
	}

public:
	// 节点定义
	struct Node
	{
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{
		}

		T data_;       // 数据域
		Node* left_;   // 左孩子域
		Node* right_;  // 右孩子域
	};

	Node* root_;  // 指向BST树的根节点
	Comp comp_;   // 函数对象

private:
	// 递归前序遍历 VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";  // 操作V
			preOrder(node->left_);       // L
			preOrder(node->right_);      // R
		}
	}

	// 递归中序遍历 LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);        // L
			cout << node->data_ << " ";  // 操作V
			inOrder(node->right_);       // R
		}
	}

	// 递归后续遍历 LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);      // L
			postOrder(node->right_);     // R
			cout << node->data_ << " ";  // 操作V
		}
	}

	// 递归层序遍历
	void levelOrder(Node* node, int i)
	{
		if (node == nullptr)
		{
			return;
		}

		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}

		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}

	// 递归求二叉树层数（即求以node为根节点的子树的高度）
	int high(Node* node)
	{
		if (node == nullptr) return 0;
		int left = high(node->left_);  // L
		int right = high(node->right_);  // R
		return left > right ? left + 1 : right + 1;  // V
	}

	// 递归求二叉树节点个数
	int number(Node* node)
	{
		if (node == nullptr) return 0;
		int left = number(node->left_);
		int right = number(node->right_);
		return left + right + 1;
	}

	// 递归插入实现
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			// 递归结束，找到插入位置，生成新节点并返回其地址
			return new Node(val);
		}

		if (node->data_ == val)  // 不插入重复元素
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = insert(node->right_, val);
		}
		else
		{
			node->left_ = insert(node->left_, val);
		}

		return node;
	}

	// 递归查询实现
	Node* query(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			return query(node->right_, val);
		}
		else
		{
			return query(node->left_, val);
		}
	}

	// 递归删除实现
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->data_ == val)
		{
			// 情况3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				// 找前驱节点
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}

				node->data_ = pre->data_;
				// 通过递归直接删除前驱节点
				node->left_ = remove(node->left_, pre->data_);
			}
			else  // 情况1，2
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else  // 删除的是没有孩子的节点，叶子节点
				{
					return nullptr;
				}
			}
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = remove(node->right_, val);
		}
		else
		{
			node->left_ = remove(node->left_, val);
		}

		return node;  // 把当前节点返回给父节点
	}

	// 求满足区间的元素值[i,j]
	void findValues(Node* node, vector<T>& vec, int i, int j)
	{
		if (node == nullptr)
		{
			return;
		}

		// 在当前节点的左子树中搜索
		if (node->data_ > i)
		{
			findValues(node->left_, vec, i, j);  // L
		}
		
		if (node->data_ >= i && node->data_ <= j)
		{
			vec.push_back(node->data_);  // V  存储满足区间元素的值
		}

		// 在当前节点的右子树中搜索
		if (node->data_ < j)
		{
			findValues(node->right_, vec, i, j);  // R
		}
	}

	// 判断二叉树是否是BST树
	bool isBSTree(Node* node)
	{
		if (node == nullptr)
		{
			return true;
		}

		// V
		if (node->left_ != nullptr && comp_(node->data_, node->left_->data_))
		{
			return false;
		}

		if (node->right_ != nullptr && comp_(node->right_->data_, node->data_))
		{
			return false;
		}

		if (!isBSTree(node->left_))  // L 判断当前节点的左子树
		{
			return false;
		}

		return isBSTree(node->right_);  // R 判断当前节点的右子树
	}
};

void test01() // 测试是否是BST树
{
	using Node = BSTree<int>::Node;
	BSTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(60);
	Node* node3 = new Node(30);
	Node* node4 = new Node(80);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node2->left_ = node3;
	node2->right_ = node4;

	cout << bst.isBSTree() << endl;
}

int main()
{
	test01();
	//int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	//BSTree<int> bst;
	//for (auto v : arr)
	//{
	//	//bst.n_insert(v);
	//	bst.insert(v);
	//}

	//vector<int> vec;
	//bst.findValues(vec, 10, 60);
	//for (auto val : vec)
	//{
	//	cout << val << " ";
	//}
	//cout << endl;

	//bst.preOrder();
	//bst.n_preOrder();
	//bst.inOrder();
	//bst.n_inOrder();
	//bst.postOrder();
	//bst.n_postOrder();
	//bst.levelOrder();
	//bst.n_levelOrder();
	//cout << bst.high() << endl;
	//cout << bst.number() << endl;
	//cout << bst.query(24) << endl;
	//cout << bst.query(12) << endl;

	//bst.insert(12);
	//bst.remove(12);
	//bst.remove(34);
	//bst.remove(58);
	//bst.inOrder();

	//bst.n_insert(12);
	//cout << bst.n_query(12) << endl;
	//bst.n_remove(12);
	//cout << bst.n_query(12) << endl;
	//bst.n_remove(34);
	//bst.n_remove(58);
	return 0;
}