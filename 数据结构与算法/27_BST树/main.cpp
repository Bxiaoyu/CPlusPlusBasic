#include <iostream>

using namespace std;

// BST������ʵ��
template<typename T, typename Comp=less<T>>
class BSTree
{
public:
	BSTree(Comp	comp = Comp()) : root_(nullptr), comp_(comp) {}

	~BSTree() {}

public:
	// �ǵݹ�������
	void n_insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;  // ��¼���ڵ�
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				// ������Ԫ����ͬ��ֵ
				return;
			}
			else if (comp_(cur->data_, val))  // С�ڹ�ϵ
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

		if (comp_(val, parent->data_))  // С��
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}

	// �ǵݹ�ɾ������
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
				break;  // �ҵ���ɾ���ڵ�
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

		// û�ҵ���ɾ���ڵ�
		if (cur == nullptr)
		{
			return;
		}

		// ���3��ɾ��ǰ���ڵ㣨���Ϊ���1��2��
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
			cur = pre;  // ��curָ��ǰ���ڵ㣬ת��Ϊ���1��2
		}

		// curָ��ɾ���ڵ㣬parentָ���丸�ڵ㣬ͳһ�������1����2
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)  // �����������ʾɾ�����Ǹ��ڵ�
		{
			root_ = child;
		}
		else
		{
			// �Ѵ�ɾ���ڵ�ĺ��ӣ�nullptr����not nullptr��д���丸�ڵ���Ӧ��ַ����
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}

		delete cur;  // ɾ����ǰ�ڵ�
	}

	// �ǵݹ��ѯ����
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

	// �ݹ�ǰ�����
	void preOrder()
	{
		cout << "[�ݹ�]ǰ�������";
		preOrder(root_);
		cout << endl;
	}

	// �ݹ��������
	void inOrder()
	{
		cout << "[�ݹ�]���������";
		inOrder(root_);
		cout << endl;
	}

	// �ݹ�������
	void postOrder()
	{
		cout << "[�ݹ�]���������";
		postOrder(root_);
		cout << endl;
	}

	// �ݹ�������
	void levelOrder()
	{
		cout << "[�ݹ�]���������";
		levelOrder(root_);
		cout << endl;
	}

	// �ݹ���������������߶ȣ�
	int high()
	{
		return high(root_);
	}

	// �ݹ���������ڵ����
	int number()
	{
		return number(root_);
	}

private:
	// �ڵ㶨��
	struct Node
	{
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{
		}

		T data_;       // ������
		Node* left_;   // ������
		Node* right_;  // �Һ�����
	};

	Node* root_;  // ָ��BST���ĸ��ڵ�
	Comp comp_;   // ��������

private:
	// �ݹ�ǰ����� VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";  // ����V
			preOrder(node->left_);       // L
			preOrder(node->right_);      // R
		}
	}

	// �ݹ�������� LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);        // L
			cout << node->data_ << " ";  // ����V
			inOrder(node->right_);       // R
		}
	}

	// �ݹ�������� LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);      // L
			postOrder(node->right_);     // R
			cout << node->data_ << " ";  // ����V
		}
	}

	// �ݹ�������
	void levelOrder(Node* node)
	{

	}

	// �ݹ��������������������nodeΪ���ڵ�������ĸ߶ȣ�
	int high(Node* node)
	{
		if (node == nullptr) return 0;
		int left = high(node->left_);  // L
		int right = high(node->right_);  // R
		return left > right ? left + 1 : right + 1;  // V
	}

	// �ݹ���������ڵ����
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