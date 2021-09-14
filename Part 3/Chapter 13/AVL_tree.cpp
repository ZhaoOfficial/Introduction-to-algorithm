#include <iostream>
#include <random>
#include <ctime>
#include "AVL_tree.hpp"
 
using namespace std;
 
int main()
{
	avltree<int> t;
 
	int a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
 
	cout << "insertion, 1 - 8, 15 - 9" << endl;
	for (size_t i = 0; i < 8; ++i)
		t.insert(a[i]);
 
	for (size_t i = 15; i >= 8; --i)
		t.insert(a[i]);
	
	cout << "preorder" << endl;
	t.print(AVL_ORDER::PREORDER);
	cout << "inoder" << endl;
	t.print(AVL_ORDER::INORDER);
	cout << "postorder" << endl;
	t.print(AVL_ORDER::POSTORDER);
	
	cout << "deletion" << endl;
	for (size_t i = 0; i < 16; i += 2)
		t.erase(i);
	t.print();
	
	cout << "copy" << endl;
	avltree<int> t2(t);
	t2.print();
	
	cout << "operator=" << endl;
	avltree<int> t3;
	t3 = t;
	t.print();
	
	cout << "extrema" << endl;
	cout << "maximum:" << t.maximum()->value_field << endl;
	cout << "minimum:" << t.minimum()->value_field << endl;
	
	return 0;
 
}