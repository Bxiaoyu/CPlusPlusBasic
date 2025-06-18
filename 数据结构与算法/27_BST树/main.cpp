#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
#include <functional>

using namespace std;

// BST������ʵ��
template<typename T, typename Comp=less<T>>
class BSTree
{
public:
	BSTree(Comp	comp = Comp()) : root_(nullptr), comp_(comp) {}

	~BSTree() 
	{
		// �������˼���ͷ�BST�����нڵ���Դ
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

	// �ݹ�������
	void insert(const T& val)
	{
		root_ = insert(root_, val);
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

	// �ݹ�ɾ������
	void remove(const T& val)
	{
		root_ = remove(root_, val);
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

	// �ݹ��ѯ����
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}

	// �ݹ�ǰ�����
	void preOrder()
	{
		cout << "[�ݹ�]ǰ�������";
		preOrder(root_);
		cout << endl;
	}

	// �ǵݹ�ǰ�����
	void n_preOrder()
	{
		cout << "[�ǵݹ�]ǰ�������";
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
			if (p->right_ != nullptr)  // R �Һ�������ջ
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

	// �ݹ����������������̣�
	void inOrder()
	{
		cout << "[�ݹ�]���������";
		inOrder(root_);
		cout << endl;
	}

	// �ǵݹ��������
	void n_inOrder()
	{
		cout << "[�ǵݹ�]���������";
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

	// �ݹ�������
	void postOrder()
	{
		cout << "[�ݹ�]���������";
		postOrder(root_);
		cout << endl;
	}

	// �ǵݹ��������
	void n_postOrder()
	{
		cout << "[�ǵݹ�]����������";
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

	// �ݹ�������
	void levelOrder()
	{
		cout << "[�ݹ�]���������";
		int h = high();  // ���Ĳ���
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);  // �ݹ�������Ĳ���
		}
		cout << endl;
	}

	// �ǵݹ�������
	void n_levelOrder()
	{
		cout << "[�ǵݹ�]���������";
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

	// �����������Ԫ��ֵ[i,j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}

	// �ж϶������Ƿ���BST��
	bool isBSTree()
	{
		Node* node = nullptr;
		return isBSTree(root_, node);
	}

	// �ж϶�����������
	bool isChildTree(BSTree<T, Comp>& child)
	{
		if (child.root_ == nullptr)
		{
			return true;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}

		if (cur == nullptr)
		{
			return false;
		}

		return isChildTree(cur, child.root_);
	}

	// ����������Ƚڵ�
	int getLCA(int val1, int val2)
	{
		Node* node =  getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw "No LCA!";
		}
		else
		{
			return node->data_;
		}
	}

	// ����ת
	void mirrorFlip()
	{
		mirrorFlip(root_);
	}

	// ����Գ�
	bool mirrorSymmetry()
	{
		if (root_ == nullptr)
		{
			return true;
		}

		return mirrorSymmetry(root_->left_, root_->right_);
	}

	// �ؽ�������
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _rebuild(pre, i, j, in, m, n);
	}

	// �ж�ƽ����
	bool isBalance()
	{
		int l = 0;
		bool flag = true;
		isBalance(root_, l, flag);
		return flag;
	}

	// ����������k���ڵ�
	int getVal(int k)
	{
		int i = 1;
		Node* node = getVal(root_, k);
		if (node == nullptr)
		{
			string err = "no No.";
			err += k;
			throw err;
		}
		else
		{
			return node->data_;
		}
	}

public:
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

	// �ݹ����ʵ��
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			// �ݹ�������ҵ�����λ�ã������½ڵ㲢�������ַ
			return new Node(val);
		}

		if (node->data_ == val)  // �������ظ�Ԫ��
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

	// �ݹ��ѯʵ��
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

	// �ݹ�ɾ��ʵ��
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->data_ == val)
		{
			// ���3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				// ��ǰ���ڵ�
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}

				node->data_ = pre->data_;
				// ͨ���ݹ�ֱ��ɾ��ǰ���ڵ�
				node->left_ = remove(node->left_, pre->data_);
			}
			else  // ���1��2
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
				else  // ɾ������û�к��ӵĽڵ㣬Ҷ�ӽڵ�
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

		return node;  // �ѵ�ǰ�ڵ㷵�ظ����ڵ�
	}

	// �����������Ԫ��ֵ[i,j]
	void findValues(Node* node, vector<T>& vec, int i, int j)
	{
		if (node == nullptr)
		{
			return;
		}

		// �ڵ�ǰ�ڵ��������������
		if (node->data_ > i)
		{
			findValues(node->left_, vec, i, j);  // L
		}
		
		if (node->data_ >= i && node->data_ <= j)
		{
			vec.push_back(node->data_);  // V  �洢��������Ԫ�ص�ֵ
		}

		// �ڵ�ǰ�ڵ��������������
		if (node->data_ < j)
		{
			findValues(node->right_, vec, i, j);  // R
		}
	}

	// �ж϶������Ƿ���BST��������BST���������ʱ������ص�
	bool isBSTree(Node* node, Node*& pre)
	{
		if (node == nullptr)
		{
			return true;
		}

		if (!isBSTree(node->left_, pre))  // L �жϵݹ�����������������Ѿ���������������ֱ�ӷ���
		{
			return false;
		}

		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_))  // ��Ҫ�ж�ʹ�ݹ����������
			{
				return false;
			}
		}
		pre = node;  // �������������ǰ���ڵ�

		return isBSTree(node->right_, pre);  // R
	}

	// �ж��Ƿ�������
	bool isChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}

		if (father == nullptr)  // �����еĽڵ㣬��ǰ������û��
		{
			return false;
		}

		if (child == nullptr)
		{
			return true;
		}

		// �ж�ֵ��ͬ
		if (father->data_ != child->data_)  // V
		{
			return false;
		}

		return isChildTree(father->left_, child->left_) && isChildTree(father->right_, child->right_);  // L R
	}

	// ����������Ƚڵ�
	Node* getLCA(Node* node, int val1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (comp_(node->data_, val1) && comp_(node->data_, val2))
		{
			return getLCA(node->right_, val1, val2);
		}
		else if (comp_(val1, node->data_) && comp_(val2, node->data_))
		{
			return getLCA(node->left_, val1, val2);
		}
		else
		{
			return node;
		}
	}

	// ����ת
	void mirrorFlip(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		// V
		Node* tmp = node->left_;
		node->left_ = node->right_;
		node->right_ = tmp;

		mirrorFlip(node->left_);   // L
		mirrorFlip(node->right_);  // R
	}

	// ����Գ�
	bool mirrorSymmetry(Node* node1, Node* node2)
	{
		if (node1 == nullptr && node2 == nullptr)
		{
			return true;
		}

		if (node1 == nullptr || node2 == nullptr)
		{
			return false;
		}
		
		if (node1->data_ != node2->data_)
		{
			return false;
		}

		return mirrorSymmetry(node1->left_, node2->right_)
			&& mirrorSymmetry(node1->right_, node2->left_);
	}

	// �ؽ�������
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}

		// ������ǰ�����ĸ��ڵ�
		Node* node = new Node(pre[i]);  // ��ǰ��ĵ�һ�����ִ����������ڵ� V
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])  // ��������������������ڵ���±�k
			{
				node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1);   // L
				node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);  // R
				return node;
			}
		}

		return node;
	}

	// �ж�ƽ�������ݹ�����У���¼�ڵ�߶�ֵ�����ؽڵ�߶�ֵ
	int isBalance(Node* node, int l, bool& flag)
	{
		if (node == nullptr)
		{
			return 1;
		}

		int left = isBalance(root_->left_, l + 1, flag);    // L
		if (!flag)
		{
			return left;
		}

		int right = isBalance(root_->right_, l + 1, flag);  // R
		if (!flag)
		{
			return right;
		}

		// V
		if (abs(left - right) > 1)  // �ڵ�ʧ��
		{
			flag = false;
		}

		return max(left, right);
	}

	// ����������k���ڵ�
	int i = 1;
	Node* getVal(Node* node, int k)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		Node* left = getVal(node->right_, k);  // R
		if (left != nullptr)
		{
			return left;
		}

		// V
		if (i++ == k)  // ��VRL��˳���£��ҵ�������K��Ԫ��
		{
			return node;
		}

		return getVal(node->left_, k);  // L
	}

};

void test01() // �����Ƿ���BST��
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

void test02() // ���������ж�����
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	using Node = BSTree<int>::Node;
	BSTree<int> bst1;
	bst1.root_ = new Node(67);
	Node* node1 = new Node(62);
	Node* node2 = new Node(69);
	Node* node3 = new Node(60);
	bst1.root_->left_ = node1;
	bst1.root_->right_ = node2;
	node1->left_ = node3;

	cout << bst.isChildTree(bst1) << endl;
}

void test03() // ����LCA����
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	cout << bst.getLCA(64, 62) << endl;
}

void test04() // ���Ծ���Գ�
{
	using Node = BSTree<int>::Node;
	BSTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(20);
	Node* node3 = new Node(10);
	Node* node4 = new Node(15);
	Node* node5 = new Node(15);
	Node* node6 = new Node(10);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node1->left_ = node3;
	node1->right_ = node4;
	node2->left_ = node5;
	//node2->right_ = node6;

	cout << bst.mirrorSymmetry() << endl;
}

void test05() // �����ؽ�������
{
	BSTree<int> bst;
	int pre[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	int in[] = { 0,5,24,34,41,58,62,64,67,69,78 };
	bst.rebuild(pre, 0, 10, in, 0, 10);
	bst.preOrder();
	bst.inOrder();
}

void test06()
{
	using Elm = pair<int, string>;
	using Func = function<bool(Elm, Elm)>;
	BSTree<Elm, Func> bst([](Elm p1, Elm p2)->bool
		{
			return p1.first > p2.first;
		}
	);
}

int main()
{
	//test05();
	//test04();
	//test03();
	//test02();
	//test01();

	//int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	//BSTree<int> bst;
	//for (auto v : arr)
	//{
	//	//bst.n_insert(v);
	//	bst.insert(v);
	//}

	//bst.inOrder();
	//cout << bst.getVal(2) << endl;
	//bst.mirrorFlip();
	//bst.inOrder();

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