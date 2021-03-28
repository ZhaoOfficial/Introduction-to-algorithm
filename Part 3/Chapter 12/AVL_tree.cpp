#include <iostream>
#include <random>
#include <ctime>
#include "AVL_tree.hpp"
 
using namespace std;
 
int main()
{
	AVLTree<int> t;
 
	int a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
 
	cout << "insertion, 1 - 8, 15 - 9" << endl;
	for (size_t i = 0; i < 8; ++i)
	{
		t.insert(a[i]);
	}
 
	for (size_t i = 15; i >= 8; --i)
	{
		t.insert(a[i]);
	}
	
	cout << "inoder" << endl;
	t.printTree(AVLTree<int>::INORDER);
	cout << "preorder" << endl;
	t.printTree(AVLTree<int>::PREORDER);
	
	cout << "deletion" << endl;
	for (size_t i = 0; i < 16; i+=2)
	{
		t.remove(i);
	}
	t.printTree();
	
	cout << "copy" << endl;
	AVLTree<int> t2(t);
	t2.printTree();
	
	cout << "operator=" << endl;
	AVLTree<int> t3;
	t3 = t;
	t.printTree();
	
	cout << "extrema" << endl;
	cout << "maximum:" << t.findMax() << endl;
	cout << "minimum:" << t.findMin() << endl;
	
	return 0;
 
}