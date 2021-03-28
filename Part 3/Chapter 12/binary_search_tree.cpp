#include <iostream>

#include "binary_search_tree.hpp"

using namespace std;

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
    tree.levelOrder();
    tree.erase(&h);
	cout << endl;

    return 0;
}
