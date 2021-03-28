#include <iostream>

using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(): FirstChild(nullptr), NextSibling(nullptr) {}
    ~TreeNode() {}

    void AddChild(T data);
    void AddSibling(T data);

public:
    T Data;
    TreeNode<T>*   FirstChild;
    TreeNode<T>*   NextSibling;
};

template <typename T>
void TreeNode<T>::AddChild(T data) {
    if (this->FirstChild == nullptr) {
        this->FirstChild = new TreeNode<T>;
        FirstChild->Data = data;
    } else
        cout << "Node already has a child.\n";
    return;
}

template <typename T>
void TreeNode<T>::AddSibling(T data) {
    if (this->NextSibling == nullptr) {
        this->NextSibling = new TreeNode<T>;
        NextSibling->Data = data;
    } else
        cout << "Node already has a sibling.\n";
    return;
}

template <typename T>
class Tree {
public:
    Tree(T data);
    ~Tree();

    void AddChild(TreeNode<T>* node, T data);
    void AddSibling(TreeNode<T>* node, T data);
    T Retrieve(TreeNode<T>* node);
    void PrintTree();

    TreeNode<T>* Root;
private:
    void DeleteNode(TreeNode<T>* node);
    void PrintTreePreOrder(TreeNode<T>* node, size_t level);
    void PrintTreeInOrder(TreeNode<T>* node, size_t level);
    void PrintTreePostOrder(TreeNode<T>* node, size_t level);
};

template <typename T>
Tree<T>::Tree(T data) {
    Root = new TreeNode<T>;
    Root->Data = data;
}

template <typename T>
Tree<T>::~Tree() {
    DeleteNode(Root);
    delete Root;
}

template <typename T>
void Tree<T>::DeleteNode(TreeNode<T>* node) {
    if (node->FirstChild != nullptr) {
        DeleteNode(node->FirstChild);
        delete node->FirstChild;
    }
    if (node->NextSibling != nullptr) {
        DeleteNode(node->NextSibling);
        delete node->NextSibling;
    }
}

template <typename T>
void Tree<T>::PrintTree() {
    cout << "Pre-ordered" << endl;
    PrintTreePreOrder(Root, 0);
    cout << "\nIn-ordered" << endl;
    PrintTreeInOrder(Root, 0);
    cout << "\nPost-ordered" << endl;
    PrintTreePostOrder(Root, 0);
}

template <typename T>
void Tree<T>::PrintTreePreOrder(TreeNode<T>* node, size_t level) {
    cout << level << ' ' << Retrieve(node) << ' ';
    if (node->NextSibling != nullptr) {
        PrintTreePreOrder(node->NextSibling, level);
    }
    if (node->FirstChild != nullptr) {
        PrintTreePreOrder(node->FirstChild, level + 1);
    }
}

template <typename T>
void Tree<T>::PrintTreeInOrder(TreeNode<T>* node, size_t level) {
    if (node->NextSibling != nullptr) {
        PrintTreeInOrder(node->NextSibling, level);
    }
    cout << level << ' ' << Retrieve(node) << ' ';
    if (node->FirstChild != nullptr) {
        PrintTreeInOrder(node->FirstChild, level + 1);
    }
}

template <typename T>
void Tree<T>::PrintTreePostOrder(TreeNode<T>* node, size_t level) {
    if (node->NextSibling != nullptr) {
        PrintTreePostOrder(node->NextSibling, level);
    }
    if (node->FirstChild != nullptr) {
        PrintTreePostOrder(node->FirstChild, level + 1);
    }
    cout << level << ' ' << Retrieve(node) << ' ';
}

template <typename T>
void Tree<T>::AddChild(TreeNode<T>* node, T data) {
    node->AddChild(data);
}

template <typename T>
void Tree<T>::AddSibling(TreeNode<T>* node, T data) {
    node->AddSibling(data);
}

template <typename T>
T Tree<T>::Retrieve(TreeNode<T>* node) {
    return node->Data;
}

int main() {
    Tree<char>* tree = new Tree<char>{'A'};

    TreeNode<char>* A = tree->Root;
    tree->AddChild(A, 'B');

    TreeNode<char>* B = A->FirstChild;
    tree->AddSibling(B, 'C');

    TreeNode<char>* C = B->NextSibling;
    tree->AddSibling(C, 'D');

    TreeNode<char>* D = C->NextSibling;
    tree->AddSibling(D, 'E');
    tree->AddChild(D, 'H');

    TreeNode<char>* E = D->NextSibling;
    tree->AddSibling(E, 'F');
    tree->AddChild(E, 'I');
    TreeNode<char>* I = E->FirstChild;
    tree->AddSibling(I, 'J');
    TreeNode<char>* J = I->NextSibling;
    tree->AddChild(J, 'P');
    tree->AddSibling(J->FirstChild, 'Q');

    TreeNode<char>* F = E->NextSibling;
    tree->AddSibling(F, 'G');
    tree->AddChild(F, 'K');
    TreeNode<char>* K = F->FirstChild;
    tree->AddSibling(K, 'L');
    tree->AddSibling(K->NextSibling, 'M');

    TreeNode<char>* G = F->NextSibling;
    tree->AddChild(G, 'N');

    tree->PrintTree();
    delete tree;
}
