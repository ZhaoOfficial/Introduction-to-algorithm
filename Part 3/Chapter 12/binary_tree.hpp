#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <deque>

using namespace std;

template <typename T>
class Node {
public:
	T data;
	Node<T>* lchild;
	Node<T>* rchild;
	Node<T>* upper;

	Node(T& data, Node<T>* left = nullptr, Node<T>* right = nullptr) : data(data), lchild(left), rchild(right), upper(nullptr) {
		if (left != nullptr)
			left->upper = this;
		if (right != nullptr)
			right->upper = this;
	}

	Node(T&& data, Node<T>* left = nullptr, Node<T>* right = nullptr): data(data), lchild(left), rchild(right), upper(nullptr) {
		if (left != nullptr)
			left->upper = this;
		if (right != nullptr)
			right->upper = this;
	}

	T& retrieve() { return data; }
	Node<T>* left() const { return lchild; }
	Node<T>* right() const { return rchild; }
	Node<T>* parent() const { return upper; }

	bool is_leaf() const { return left() == nullptr && right() == nullptr; }
	int height() const {
		return is_leaf() ? 0 : max(left()->height(), right()->height()) + 1;
	}
	int size() const {
		return 1 + (left() == nullptr ? 0 : left()->size()) + (right() == nullptr ? 0 : right()->size());
	}
};

template <typename T>
class BinaryTree {
public:
	BinaryTree() {}
	BinaryTree(Node<T>* root) : root(root) {}
	~BinaryTree() {}

	void breadthFirst() const {
		if (this->root == nullptr)
			return;
		deque<Node<T>*> nodes;
		nodes.push_back(root);
		Node<T>* temp;
		while (nodes.size() > 0) {
			temp = nodes.front();
			nodes.pop_front();
			cout << temp->retrieve () << ' ';
			if (temp->left())
				nodes.push_back(temp->left());
			if (temp->right())
				nodes.push_back(temp->right());
		}
	}
	
	void depthFirst() const {
		if (this->root == nullptr)
			return;
		deque<Node<T>*> nodes;
		nodes.push_back(root);
		Node<T>* temp;
		while (nodes.size() > 0) {
			temp = nodes.back();
			nodes.pop_back();
			cout << temp->retrieve () << ' ';
			if (temp->right())
				nodes.push_back(temp->right());
			if (temp->left())
				nodes.push_back(temp->left());
		}
	}

	void levelOrder() const {
		breadthFirst();
	}

	void preOrder() const {
		if (this->root == nullptr)
			return;
		cout << this->root->retrieve() << ' ';
		BinaryTree<T> leftTree(this->root->left());
		leftTree.preOrder();
		BinaryTree<T> rightTree(this->root->right());
		rightTree.preOrder();
	}

	void inOrder() const {
		if (this->root == nullptr)
			return;
		BinaryTree<T> leftTree(this->root->left());
		leftTree.inOrder();
		cout << this->root->retrieve() << ' ';
		BinaryTree<T> rightTree(this->root->right());
		rightTree.inOrder();
	}

	void postOrder() const {
		if (this->root == nullptr)
			return;
		BinaryTree<T> leftTree(this->root->left());
		leftTree.postOrder();
		BinaryTree<T> rightTree(this->root->right());
		rightTree.postOrder();
		cout << this->root->retrieve() << ' ';
	}

protected:
	Node<T>* root;
};

#endif // BINARY_TREE_HPP