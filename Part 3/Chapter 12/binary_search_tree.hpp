#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

#include "binary_tree.hpp"

using namespace std;

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
    BinarySearchTree() : BinaryTree<T>() {}
    BinarySearchTree(Node<T>* root) : BinaryTree<T>(root) {}
    ~BinarySearchTree() {}
    
	Node<T>* recursive_search(T& value);
    Node<T>* recursive_search(T&& value);
    Node<T>* iterative_search(T& value);
	Node<T>* iterative_search(T&& value);
    Node<T>* recursive_minimum(Node<T>* node = nullptr);
    Node<T>* recursive_maximum(Node<T>* node = nullptr);
    Node<T>* iterative_minimum(Node<T>* node = nullptr);
    Node<T>* iterative_maximum(Node<T>* node = nullptr);
    void insert(Node<T>* node);
    void erase(Node<T>* node);

private:
    void transplant(Node<T>*& src, Node<T>*& dst);
};

template <typename T>
Node<T>* BinarySearchTree<T>::recursive_search(T& value) {
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

template <typename T>
Node<T>* BinarySearchTree<T>::recursive_search(T&& value) {
    return recursive_search(value);
}

template <typename T>
Node<T>* BinarySearchTree<T>::iterative_search(T& value) {
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

template <typename T>
Node<T>* BinarySearchTree<T>::iterative_search(T&& value) {
    return iterative_search(value);
}

template <typename T>
Node<T>* BinarySearchTree<T>::recursive_minimum(Node<T>* node) {
    if (node == nullptr)
        node = this->root;
    return (node->left() == nullptr) ? node : BinarySearchTree<T>(node->left()).recursive_minimum(node->left());
}

template <typename T>
Node<T>* BinarySearchTree<T>::recursive_maximum(Node<T>* node) {
    if (node == nullptr)
        node = this->root;
    return (node->right() == nullptr) ? node : BinarySearchTree<T>(node->right()).recursive_maximum(node->right());
}

template <typename T>
Node<T>* BinarySearchTree<T>::iterative_minimum(Node<T>* node) {
    if (node == nullptr)
        node = this->root;
    Node<T>* temp = node;
    while (temp->left() != nullptr) {
        temp = temp->left();
    }
    return temp;
}

template <typename T>
Node<T>* BinarySearchTree<T>::iterative_maximum(Node<T>* node) {
    if (node == nullptr)
        node = this->root;
    Node<T>* temp = node;
    while (temp->right() != nullptr) {
        temp = temp->right();
    }
    return temp;
}

template <typename T>
void BinarySearchTree<T>::insert(Node<T>* node) {
    
    Node<T>* temp = this->root;
    Node<T>* last = temp;
    // find well placed position
    while (temp != nullptr) {
        last = temp; // the position to place
        if (node->retrieve() < temp->retrieve())
            temp = temp->left();
        else
            temp = temp->right();
    }
    // root
    if (last == nullptr)
        this->root = node;
    else if (node->retrieve() < last->retrieve())
        last->lchild = node;
    // always place the same value at right
    else
        last->rchild = node;
    node->upper = last;
}

template <typename T>
void BinarySearchTree<T>::erase(Node<T>* node) {
    // left is null
    if (node->left() == nullptr)
        transplant(node->rchild, node);
    // left is not null, right is null
    else if (node->right() == nullptr)
        transplant(node->rchild, node);
    // neither is null
    else {
        // find proper postion to transparent
        Node<T>* temp = iterative_minimum(node->right());
        // use min node in right child tree
        if (temp->parent() != node) {
            transplant(temp->rchild, temp);
            temp->rchild = node->rchild;
            temp->rchild->upper = temp;
        }
        transplant(temp, node);
        temp->lchild = node->lchild;
        temp->lchild->upper = temp;
    }
}

template <typename T>
void BinarySearchTree<T>::transplant(Node<T>*& src, Node<T>*& dst) {
    // root
    if (dst == this->root)
        this->root = src;
    // on the left
    else if (dst == dst->parent()->left())
        dst->upper->lchild = src;
    // on the right
    else
        dst->upper->rchild = src;
    // set parent
    if (src != nullptr)
        src->upper = dst->parent();    
}

#endif //!BINARY_SEARCH_TREE_HPP
