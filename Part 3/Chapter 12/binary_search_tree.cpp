#include <iostream>
#include "binary_tree.hpp"

using namespace std;

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
    BinarySearchTree() : BinaryTree<T>() {}
    BinarySearchTree(Node<T>* root) : BinaryTree<T>(root) {}
    ~BinarySearchTree() {}

    
	Node<T>* recursive_search(T& value) {
		if (this->root == nullptr || this->root->retrieve() == value) {
			return this->root;
		}
        if (this->root->retrieve() > value) {
            BinarySearchTree<T> leftTree(this->root->left());
            return leftTree.recursive_search(value);
        }
        else {
            BinarySearchTree<T> rightTree(this->root->right());
            return rightTree.recursive_search(value);
        }
	}

    Node<T>* recursive_search(T&& value) {
        return recursive_search(value);
    }

    Node<T>* iterative_search(T& value) {
        Node<T>* temp = this->root;
        while (temp != nullptr && temp->retrieve() != value) {
            if (temp->retrieve() > value) {
                temp = temp->left();
            }
            else {
                temp = temp->right();
            }
        }
        return temp;
    }

	Node<T>* iterative_search(T&& value) {
        return iterative_search(value);
    }

    Node<T>* recursive_minimum() {
        return (this->root->left() == nullptr) ? this->root : BinarySearchTree<T>(this->root->left()).recursive_minimum();
    }

    Node<T>* recursive_maximum() {
        return (this->root->right() == nullptr) ? this->root : BinarySearchTree<T>(this->root->right()).recursive_maximum();
    }

    Node<T>* iterative_minimum() {
        Node<T>* temp = this->root;
        while (temp->left() != nullptr) {
            temp = temp->left();
        }
        return temp;
    }

    Node<T>* iterative_maximum() {
        Node<T>* temp = this->root;
        while (temp->right() != nullptr) {
            temp = temp->right();
        }
        return temp;
    }

    void insert(Node<T>* value) {
    	Node<T>* temp = this->root;
        Node<T>* last = temp;
        if (temp == nullptr) {
            temp = value;
        }
        
        while (temp != nullptr) {
        	if (value->retrieve() < temp->retrieve()) {
                last = temp;
	        	temp = temp->left();
	        }
	        else if (value->retrieve() > temp->retrieve()) {
                last = temp;
	        	temp = temp->right();
	        }
	        else {
	            return;
	        } 
		}
        if (temp == nullptr) {
            if (value->retrieve() < last->retrieve()) {
                last->lchild = value;
	        }
	        else if (value->retrieve() > last->retrieve()) {
                last->rchild = value;
	        }
        }
    }

    void erase(T& value) {

    }
};

int main() {
    Node<int> g(8);
    Node<int> f(5);
    Node<int> e(3);
    Node<int> d(1);
    Node<int> c(6, &f, &g);
    Node<int> b(2, &d, &e);
    Node<int> a(4, &b, &c);

    BinarySearchTree<int> tree(&a);
    tree.inOrder();
	cout << endl;
    cout << tree.iterative_minimum()->retrieve() << endl;
    cout << tree.recursive_maximum()->retrieve() << endl;
    cout << tree.recursive_search(1)->retrieve() << endl;
    cout << tree.iterative_search(2)->retrieve() << endl;

    Node<int> h(7);
    tree.insert(&h);
    tree.inOrder();
	cout << endl;

    return 0;
}