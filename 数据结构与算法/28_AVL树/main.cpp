/*
* AVL����ƽ����
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
* AVL��Ϊ��ά���ڵ�ƽ�����������ֽڵ���ת����
* �ڵ�ʧ���ԭ��
* 1�����ӵ�������̫���ˣ�����������
* 2���Һ��ӵ�������̫���ˣ�����������
* 3�����ӵ�������̫���ˣ�����-����ת��������ƽ�⣩
* 4���Һ��ӵ�������̫���ˣ�����-����ת��������ƽ�⣩
*/

// AVL��
template<typename T>
class AVLTree
{
public:

private:
	// ����AVL���ڵ�����
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
		int height_;   // ��¼�ڵ�߶�ֵ
	};

	Node* root_;  // ָ����ڵ�

private:
	// ���ؽڵ�߶�ֵ
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}

	// ����ת�������Բ���nodeΪ���������ת�����������µĸ��ڵ㷵��
	Node* rightRotate(Node* node)
	{
		// �ڵ���ת
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;

		// �߶ȸ���
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;

		// ������ת��������µĸ��ڵ�
		return child;
	}

	// ����ת�������Բ���nodeΪ���������ת�����������µĸ��ڵ㷵��
	Node* leftRotate(Node* node)
	{
		// �ڵ���ת
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;

		// �߶ȸ���
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;

		// ������ת��������µĸ��ڵ�
		return child;
	}
};

int main()
{
	return 0;
}