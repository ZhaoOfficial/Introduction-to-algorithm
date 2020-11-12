#ifndef AVL_TREE_H
#define AVL_TREE_H
#include<iostream>

using namespace std;

template <typename T>
class AVLTree
{
public:
	enum ORDER {
		PREORDER,
		INORDER,
		POSTORDER
	};
public:
	AVLTree() : root(nullptr) {}
	AVLTree(const AVLTree& rhs) {
		root = clone(rhs.root);
	}
	~AVLTree() {
		makeEmpty();
	}

	// return the height of the tree
	// if the tree is empty, return -1
	int getHeight() const {
		return root->height;
	}

	// recursively findMin
	const T& findMin() const {
		return findMin(root)->data;
	}

	// Iteratively findMax
	const T& findMax() const {
		return findMax(root)->data;
	}

	// recursively search
	bool contains(const T& x) const {
		return contains(x, root);
	}

	bool isEmpty() const {
		return  nullptr == root;
	}

	// traverse the tree, default inorder
	void printTree(ORDER order = INORDER, ostream& out = cout) const {
		if (isEmpty())
			out << "Empty tree!" << endl;
		else {
			switch (order) { 
				case PREORDER:
					preOrder(root, cout);
					break; 
				case INORDER:
					inOrder(root, cout);
					break;
				case POSTORDER:
					postOrder(root, cout);
					break;
				default:
					cerr << "It should be PREORDER, INORDER or POSTORDER!" << endl;
					break;
			}
		}
		cout << endl;	
	}

	// clear
	void makeEmpty() {
		makeEmpty(root);
	}

	void insert(const T& x) {
		insert(x, root);
	}

	void remove(const T& x) {
		remove(x, root);
	}

	// deep copy
	const AVLTree & operator=(const AVLTree& rhs) {
		if (this != &rhs) {
			AVLNode* temp = clone(rhs.root);
			makeEmpty();
			root = temp;
		}
		return* this;
	}

private:
	struct AVLNode {
		T data;
		AVLNode* left;
		AVLNode* right;
		int height;

		AVLNode(const T& thedata, AVLNode* lt, AVLNode* rt, int h = 0)
		 : data(thedata), left(lt), right(rt), height(h) {}
	};

	AVLNode* root;
	static const int ALLOW_IMBALANCE = 1;

	int max (int a, int b) {
		return a >= b ? a : b; 
	}

	inline int height(AVLNode* t) const {
		return nullptr == t ? -1 : t->height;
	}

	void insert(const T& x, AVLNode*& t);

	void remove(const T&x, AVLNode*& t);
	
	AVLNode* findMin(AVLNode* t) const;

	AVLNode* findMax(AVLNode* t) const;

	bool contains(const T& x, AVLNode* t) const;

	void makeEmpty(AVLNode*& t);

	void preOrder(AVLNode* t, ostream& out) const;

	void inOrder(AVLNode* t, ostream& out) const;

	void postOrder(AVLNode* t, ostream& out) const;

	AVLNode* clone(AVLNode* t) const;

	void balance(AVLNode*& t);

	void rotateWithRightChild(AVLNode*& k2);

	void rotateWithLeftChild(AVLNode*& k2);

	void doubleWithLeftChild(AVLNode*& k3);

	void doubleWithRightChild(AVLNode*& k3);

	// updateHeight
	inline void updateHeight(AVLNode*& t) {
		t->height = max(height(t->left), height(t->right)) + 1;
	}

};

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::clone(typename AVLTree<T>::AVLNode* t) const {
	if (t == nullptr)
		return nullptr;

	return new AVLNode(t->data, clone(t->left), clone(t->right));
}

template <typename T>
void AVLTree<T>::preOrder(typename AVLTree<T>::AVLNode* t, ostream& out) const {
	if (nullptr != t) {	
		out << t->data << ' ';
		preOrder(t->left, out);
		preOrder(t->right, out);
	}
}

template <typename T>
void AVLTree<T>::inOrder(typename AVLTree<T>::AVLNode* t, ostream& out) const {
	if (nullptr != t) {
		inOrder(t->left, out);
		out << t->data << ' ';
		inOrder(t->right, out);
	}
}

template <typename T>
void AVLTree<T>::postOrder(typename AVLTree<T>::AVLNode* t, ostream& out) const {
	if (nullptr != t) {
		postOrder(t->left, out);
		postOrder(t->right, out);
		out << t->data << ' ';
	}
}

// postOrder
template <typename T>
void AVLTree<T>::makeEmpty(typename AVLTree<T>::AVLNode*& t) {
	if (t != nullptr) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::findMin(typename AVLTree<T>::AVLNode* t) const {
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::findMax(typename AVLTree<T>::AVLNode* t) const {
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}

// keep the balance of the tree
template <typename T>
void AVLTree<T>::remove(const T& x, typename AVLTree<T>::AVLNode*& t) {
	if (t == nullptr)
		return;

	if (x < t->data)
		remove(x, t->left);
	else if (t->data < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) {
		// if both are not nullptr
		// get the minimum in the right
		t->data = findMin(t->right)->data;
		remove(t->data, t->right);
	}
	else {
		// if one subtree is nullptr
		// the other one gets promoted
		auto oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}

	balance(t);
}

template <typename T>
void AVLTree<T>::insert(const T& x,	typename AVLTree<T>::AVLNode*& t) {
	if (nullptr == t)
		t = new AVLNode(x, nullptr, nullptr);
	else if (x < t->data) {
		insert(x, t->left);
	}
	else if (t->data < x) {
		insert(x, t->right);
	}
	// do nothing if find x in the tree

	balance(t); // check if it is balanced, update the height
}

template <typename T>
void AVLTree<T>::balance(typename AVLTree<T>::AVLNode*& t) {
	if (nullptr == t)
		return;
	// if the height of the left > the height of the right + 1
	if (height(t->left) - height(t->right) > AVLTree<T>::ALLOW_IMBALANCE) {
		// judge if the height of the left of the left
		// > the height of the right of the left
		if (height(t->left->left) >= height(t->left->right)) {
			rotateWithLeftChild(t); 
		}
		else { 
			doubleWithLeftChild(t);
		}
	}
	else if (height(t->right) - height(t->left) > AVLTree<T>::ALLOW_IMBALANCE)
	{
		if (height(t->right->right) >= height(t->right->left)) {
			rotateWithRightChild(t);
		}
		else {
			doubleWithRightChild(t);
		}
	}
	// do nothing if it is AVLTree

	updateHeight(t);
}

template <typename T>
bool AVLTree<T>::contains(const T& x, typename AVLTree<T>::AVLNode* t) const {
	if (t == nullptr)
		return false;
	else if (x < t->data)
		return contains(x, t->left);
	else if (t->data < x)
		return contains(x, t->right);
	else
		return true;
}

// rotate with left child
// if it is inserted into the left subtree of the left subtree
//       k2                      k1
//      /  \                    /  \
//     k1   Z      ------>     X    k2
//    /  \                    /     / \
//   X    Y                  X'    Y   Z
//  /
// X'
// X' may be at the left of the X or right of the X
template <typename T>
void AVLTree<T>::rotateWithLeftChild(typename AVLTree<T>::AVLNode*& k2) {
	auto k1 = k2->left;

	k2->left = k1->right; 
	k1->right = k2;
	// updateHeight
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;

	// change the root
	k2 = k1;
}


// rotate with right child
// if it is inserted into the right subtree of the right subtree
//      K2                             K1
//     /  \                           /  \
//    X    k1         ----->         K2   Z
//         / \                      /  \   \
//        Y   Z                    X    Y   Z'
//             \
//              Z'
// Z' may be at the left of the Z or right of the Z
template <typename T>
void AVLTree<T>::rotateWithRightChild(typename AVLTree<T>::AVLNode*& k2) {
	auto k1 = k2->right;

	k2->right = k1->left;
	k1->left = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(k2->height, height(k1->right)) + 1; 

	k2 = k1;
}

// if it is inserted into the right subtree of the left subtree
//       k3                k3              k2
//      /  \              /  \            /  \
//     k1   C    --->    k2   C  --->    k1   k3
//    / \               /               / \     \
//   A   k2            k1              A   B     C
//       /            / \
//      B            A   B
template <typename T>
void AVLTree<T>::doubleWithLeftChild(typename AVLTree<T>::AVLNode*& k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

// if it is inserted into the left subtree of the right subtree
//       k3              k3                 k2
//      /  \            /  \               /  \
//     A    k1   --->  A    k2     --->  k3    k1
//         / \             /  \         /  \     \
//        K2  C           B    k1      A    B     C
//       /                      \
//      B                        C

template <typename T>
void AVLTree<T>::doubleWithRightChild(typename AVLTree<T>::AVLNode*& k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}

#endif  //AVL_TREE_H