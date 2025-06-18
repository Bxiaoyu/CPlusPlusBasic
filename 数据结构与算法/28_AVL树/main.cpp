/*
* AVL二叉平衡树
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
* AVL树为了维护节点平衡引入了四种节点旋转操作
* 节点失衡的原因：
* 1、左孩子的左子树太高了：做右旋操作
* 2、右孩子的右子树太高了：做左旋操作
* 3、左孩子的右子树太高了：做左-右旋转操作（左平衡）
* 4、右孩子的左子树太高了：做右-左旋转操作（右平衡）
*/

// AVL树
template<typename T>
class AVLTree
{
public:

private:
	// 定义AVL树节点类型
	struct Node
	{
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{
		}

		T data_;
		Node* left_;
		Node* right_;
		int height_;   // 记录节点高度值
	};

	Node* root_;  // 指向根节点

private:
	// 返回节点高度值
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}

	// 右旋转操作，以参数node为轴进行右旋转操作，并把新的根节点返回
	Node* rightRotate(Node* node)
	{
		// 节点旋转
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;

		// 高度更新
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;

		// 返回旋转后的子树新的根节点
		return child;
	}

	// 左旋转操作，以参数node为轴进行左旋转操作，并把新的根节点返回
	Node* leftRotate(Node* node)
	{
		// 节点旋转
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;

		// 高度更新
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;

		// 返回旋转后的子树新的根节点
		return child;
	}
};

int main()
{
	return 0;
}