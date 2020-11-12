// A red black tree is a tree which satisfy that:
// 1. Each node is either red or black.
// 2. The root node is black.
// 3. If the node is red, then its children nodes are black.
// 4. Define a null path within a binary tree as any path starting from the root where the last node is not a full node.
// Each null path must have the same number of black nodes.

// secondary theorem
// 1. A red node is a full node or a leaf node (by contradiction).
// 2. If a node has exactly one child, then it is black (by contradiction) and the child is a red (by contradiction) leaf (by contradiction) node.
// 3. A black tree is a perfect tree.
// 4. A tree with all its leaf nodes are red is a complete tree.


// basic node types:
//      b          b          b          b          b
//                /          / \        / \        / \ 
//               r          b   b      r   r      b   b
//                                               /
//                                              r
//
//      b          b          b          b          b          b
//     / \        / \        / \        / \        / \        / \ 
//    b   b      r   b      b   b      b   b      r   b      r   b
//   / \        / \        /   /      / \ /      / \        / \ /
//  r   r      b   b      r   r      r   rr     b   b      b   br
//                                             /
//                                            r
//

// k represent the number of black nodes per null path and h = 2k – 1 represent the height of the worst-case tree
// F(1) = 2
// F(k) = F(k – 1) + 2 + 2(2^{k – 1} – 1)
//      = F(k - 1) + 2^{k}
//      = 2^{k + 1} - 2
// n = 2^{\frac{h + 3}{2}} - 2
// h = 2 log[2](n + 2) - 3 = O(ln(n))



#include <iostream>
#define RED  1
#define BLACK 0

using std::cin;
using std::cout;
using std::endl;
using std::swap;


template <typename T>
class RBnode {
public:
    RBnode() : left(nullptr), right(nullptr), parent(nullptr) {}
    RBnode(T data, RBnode* left = nullptr, RBnode* right = nullptr, RBnode* p = nullptr) : data(data), left(left), right(right), p(p) {}
    ~RBnode() {}
    
    T getData() const {
        if (this->data)
            return this->data;
    }
    
    void setColor(bool color) {
        this->color = color;
    }
    
    RBnode* left() const {
        return lchild;
    }
    
    RBnode* right() const {
        return rchild;
    }
    
    RBnode* parent() const {
        return p;
    }
private:
    bool color;
    T data;
    RBnode* lchild;
    RBnode* rchild;
    RBnode* p;
};

template <typename T>
class RBTree {
public:
    enum ORDER {
		PREORDER,
		INORDER,
		POSTORDER
	};

    RBTree() {
        this->root = new RBnode();
        root->setColor(BLACK);
    }
    RBTree(const RBTree& other) {
        this->root = clone(other.root);
    }
    ~RBTree() {
        makeEmpty();
    }

    const RBTree& operator=(const RBTree& other) {
		if (this != &other) {
			RBTree* temp = clone(other.root);
			makeEmpty();
			root = temp;
		}
		return *this;
	}

    const T& findMin() const {
		return findMin(root)->data;
	}

	const T& findMax() const {
		return findMax(root)->data;
	}

    bool contains(const T& x) const {
		return contains(x, root);
	}

	bool isEmpty() const {
		return  nullptr == root;
	}

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

    void makeEmpty() {
		makeEmpty(this->root);
	}

    void insert(const T& x) {
		insert(x, this->root);
	}

	void remove(const T& x) {
		remove(x, this->root);
	}



private:
    RBnode root;

    RBnode* clone(RBnode* other) const {
        if (other == nullptr)
            return nullptr;
        return new RBnode(other->getData(), clone(other->left()), clone(other->right()), clone(other->parent()));
    }

    void preOrder(RBnode* root, ostream& out) {
        if (nullptr != root) {	
            out << root->getData() << ' ';
            preOrder(root->left(), out);
            preOrder(root->right(), out);
        }
    }

    void inOrder(RBnode* root, ostream& out) {
        if (nullptr != root) {
            inOrder(root->left(), out);
            out << root->getData() << ' ';
            inOrder(root->right(), out);
        }
    }

    void postOrder(RBnode* root, ostream& out) {
        if (nullptr != root) {
            postOrder(root->left(), out);
            postOrder(root->right(), out);
            cout << root->getData() << ' ';
        }
    }

    void makeEmpty(RBnode* root) {
        if (root != nullptr) {
            makeEmpty(root->left());
            makeEmpty(root->right());
            delete root;
        }
        root = nullptr;
    }

    RBnode* findMin(RBnode* root) {
        auto temp = root;
        if (temp != nullptr) {
            while (temp->left() != nullptr) {
                temp = temp->left();
            }
        }
        return temp;
    }

    RBnode* findMax(RBnode* root) {
        auto temp = root;
        if (temp != nullptr) {
            while (temp->right() != nullptr) {
                temp = temp->right();
            }
        }
        return temp;
    }


    
};


int main() {
    
}
