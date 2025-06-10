#include <iostream>

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

	// 递归前序遍历
	void preOrder()
	{
		cout << "[递归]前序遍历：";
		preOrder(root_);
		cout << endl;
	}

	// 递归中序遍历
	void inOrder()
	{
		cout << "[递归]中序遍历：";
		inOrder(root_);
		cout << endl;
	}

	// 递归后序遍历
	void postOrder()
	{
		cout << "[递归]后序遍历：";
		postOrder(root_);
		cout << endl;
	}

	// 递归层序遍历
	void levelOrder()
	{
		cout << "[递归]层序遍历：";
		levelOrder(root_);
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

private:
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
	void levelOrder(Node* node)
	{

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
};


int main()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BSTree<int> bst;
	for (auto v : arr)
	{
		bst.n_insert(v);
	}

	bst.preOrder();
	bst.inOrder();
	bst.postOrder();

	//bst.n_insert(12);
	//cout << bst.n_query(12) << endl;
	//bst.n_remove(12);
	//cout << bst.n_query(12) << endl;
	//bst.n_remove(34);
	//bst.n_remove(58);
	return 0;
}