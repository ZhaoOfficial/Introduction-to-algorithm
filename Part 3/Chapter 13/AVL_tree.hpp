#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

enum class AVL_ORDER {
    PREORDER,
    INORDER,
    POSTORDER
};

template <typename T>
class avltree_node {
public:
    avltree_node(const T& value) : value_field(value) {}
    ~avltree_node() {}

    avltree_node* left;
    avltree_node* right;
    avltree_node* parent;
    int height;
    T value_field;

    static avltree_node* minimum(avltree_node* node_ptr) {
        while (node_ptr->left != nullptr) {
            node_ptr = node_ptr->left;
        }
        return node_ptr;
    }

    static avltree_node* maximum(avltree_node* node_ptr) {
        while (node_ptr->right != nullptr) {
            node_ptr = node_ptr->right;
        }
        return node_ptr;
    }
};

template <typename T, typename Compare = std::less<T>>
class avltree {
public:
    avltree() : node_count(0) {
        header = get_node();
        avltree_initialize();
    }
    avltree(const avltree& other) : node_count(0) {
        header = get_node();
        if (other.root() == nullptr) {
            avltree_initialize();
        }
        else {
            root() = avltree_copy(other.root(), header);
            leftmost() = minimum(root());
            rightmost() = maximum(root());
            node_count = other.node_count;
        }
    }
    avltree& operator=(const avltree& other) {
        if (this != &other) {
            clear();
            if (other.root() == nullptr) {
                root() = nullptr;
                leftmost() = nullptr;
                rightmost() = nullptr;
                node_count = 0;
            }
            else {
                root() = avltree_copy(other.root(), header);
                leftmost() = minimum(root());
                rightmost() = maximum(root());
                node_count = other.node_count;
            }
        }
        return *this;
    }
    ~avltree() { clear(); }

    avltree_node<T>* header;
    size_t node_count;
    Compare comp;
    static const int ALLOW_IMBALANCE = 1;

private:
    avltree_node<T>* get_node() {
        return static_cast<avltree_node<T>*>(malloc(sizeof(avltree_node<T>)));
    }
    avltree_node<T>* create_node(const T& node_value) {
        avltree_node<T>* temp = get_node();
        new(&value(temp))T(node_value);
        left(temp) = nullptr;
        right(temp) = nullptr;
        return temp;
    }
    avltree_node<T>* clone_node(avltree_node<T>* node_ptr) {
        avltree_node<T>* temp = new avltree_node<T>(value(node_ptr));
        temp->height = node_ptr->height;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->parent = nullptr;
        return temp;
    }
    void destroy_node(avltree_node<T>* node_ptr) {
        node_ptr->~avltree_node<T>();
    }
    void put_node(avltree_node<T>* node_ptr) {
        free(node_ptr);
    }

    void avltree_initialize() {
        header->height = -1;
        root() = nullptr;
        leftmost() = header;
        rightmost() = header;
    }
    avltree_node<T>* avltree_copy(avltree_node<T>* src, avltree_node<T>* dst) {
        // new node
        avltree_node<T>* top = clone_node(src);
        // parent of new node
        top->parent = dst;

        if (right(src) != nullptr) {
            // recursion of right child
            right(top) = avltree_copy(right(src), top);
        }
        // check left child
        dst = top;
        src = left(src);

        // if left child exists
        while (src != nullptr) {
            // left child copy
            avltree_node<T>* src_copy = clone_node(src);
            left(dst) = src_copy;
            parent(src_copy) = dst;
            if (right(src) != nullptr) {
                // recursion of right child of left child
                right(src_copy) = avltree_copy(right(src), src_copy);
            }
            dst = src_copy;
            src = left(src);
        }

        return top;
    }

    avltree_node<T>*& root() const { return header->parent; }
    avltree_node<T>*& leftmost() const { return header->left; }
    avltree_node<T>*& rightmost() const { return header->right; }

    static avltree_node<T>*& left(avltree_node<T>* node_ptr) {
        return node_ptr->left;
    }
    static avltree_node<T>*& right(avltree_node<T>* node_ptr) {
        return node_ptr->right;
    }
    static avltree_node<T>*& parent(avltree_node<T>* node_ptr) {
        return node_ptr->parent;
    }
    static int height(avltree_node<T>* node_ptr) {
        return node_ptr == nullptr ? -1 : node_ptr->height;
    }
    static T& value(avltree_node<T>* node_ptr) {
        return node_ptr->value_field;
    }
    static avltree_node<T>* minimum(avltree_node<T>* node_ptr) {
        return avltree_node<T>::minimum(node_ptr);
    }
    static avltree_node<T>* maximum(avltree_node<T>* node_ptr) {
        return avltree_node<T>::maximum(node_ptr);
    }

public:
    bool empty() const { return node_count == 0; }
    avltree_node<T>* minimum() const { return minimum(root()); }
    avltree_node<T>* maximum() const { return maximum(root()); }
    size_t size() const { return node_count; }

    void print(AVL_ORDER order = AVL_ORDER::INORDER) const {
        if (empty()) {
            cout << "Empty Tree!" << endl;
        }
        else {
            switch (order) {
                case AVL_ORDER::PREORDER:
                    preorder(header->parent);
                    break;
                case AVL_ORDER::INORDER:
                    inorder(header->parent);
                    break;
                case AVL_ORDER::POSTORDER:
                    postorder(header->parent);
                    break;
                default:
                    break;
            }
            cout << endl;
        }
    }
    void preorder(avltree_node<T>* node_ptr) const {
        if (node_ptr != nullptr) {
            cout << value(node_ptr) << ' ';
            preorder(left(node_ptr));
            preorder(right(node_ptr));
        }
    }
    void inorder(avltree_node<T>* node_ptr) const {
        if (node_ptr != nullptr) {
            inorder(left(node_ptr));
            cout << value(node_ptr) << ' ';
            inorder(right(node_ptr));
        }
    }
    void postorder(avltree_node<T>* node_ptr) const {
        if (node_ptr != nullptr) {
            postorder(left(node_ptr));
            postorder(right(node_ptr));
            cout << value(node_ptr) << ' ';
        }
    }

    bool contains(const T& node_value) const { contains(node_value, root()); }
    void insert(const T& node_value) { insert(node_value, header, root()); }
    void erase(const T& node_value) { erase(node_value, root()); }
    void clear() { clear(root()); }

    inline void update_height(avltree_node<T>*& node_ptr) {
        node_ptr->height = std::max(height(left(node_ptr)), height(right(node_ptr))) + 1;
    }
    void rotate_with_left(avltree_node<T>*& node_ptr);
    void rotate_with_right(avltree_node<T>*& node_ptr);
    void double_rotate_with_left(avltree_node<T>*& node_ptr);
    void double_rotate_with_right(avltree_node<T>*& node_ptr);
    void balance(avltree_node<T>*& node_ptr) {
        if (node_ptr == nullptr)
            return;

	    // if the height of the left child > the height of the right child + 1
        if (height(left(node_ptr)) - height(right(node_ptr)) > ALLOW_IMBALANCE) {
            // judge if the height of the left tree of the left child
            // > the height of the right tree of the left child
            if (height(left(left(node_ptr))) >= height(right(left(node_ptr)))) {
                rotate_with_left(node_ptr);
            }
            else {
                double_rotate_with_left(node_ptr);
            }
        }
        else if (height(right(node_ptr)) - height(left(node_ptr)) > ALLOW_IMBALANCE) {
            if (height(right(right(node_ptr))) >= height(left(right(node_ptr)))) {
                rotate_with_right(node_ptr);
            }
            else {
                double_rotate_with_right(node_ptr);
            }
        }

        update_height(node_ptr);
    }

private:
    bool contains(const T& node_value, avltree_node<T>*& node_ptr) const {
        if (node_ptr == nullptr)
            return false;
        else if (comp(node_value, value(node_ptr)))
            return contains(node_value, left(node_ptr));
        else if (comp(value(node_ptr), node_value))
            return contains(node_value, right(node_ptr));
        else
            return true;
    }
    
    void insert(const T& node_value, avltree_node<T>*& parent_node, avltree_node<T>*& current_node) {
        if (current_node == nullptr) {
            current_node = create_node(node_value);
            parent(current_node) = parent_node;
            ++node_count;
        }
        else if (comp(node_value, value(current_node)))
            insert(node_value, current_node, left(current_node));
        else if (comp(value(current_node), node_value))
            insert(node_value, current_node, right(current_node));

        balance(current_node);
    }

    void erase(const T& node_value, avltree_node<T>*& node_ptr) {
        if (node_ptr == nullptr)
            return;
        
        if (comp(node_value, value(node_ptr)))
            erase(node_value, left(node_ptr));
        else if (comp(value(node_ptr), node_value))
            erase(node_value, right(node_ptr));
        else if (left(node_ptr) != nullptr && right(node_ptr) != nullptr) {
            // if both are not nullptr
            // get the minimum in the right
            value(node_ptr) = value(minimum(node_ptr->right));
            erase(value(node_ptr), right(node_ptr));
        }
        else {
            // if only one subtree, then this one gets promoted
            avltree_node<T>* old_node = node_ptr;
            if (left(node_ptr) != nullptr)
                node_ptr = left(node_ptr);
            else
                node_ptr = right(node_ptr);

            if (node_ptr != nullptr)
                parent(node_ptr) = parent(old_node);
            destroy_node(old_node);
            put_node(old_node);
            --node_count;
        }

        balance(node_ptr);
    }
    
    void clear(avltree_node<T>*& node_ptr) {
        if (node_ptr != nullptr) {
            clear(left(node_ptr));
            clear(right(node_ptr));
            destroy_node(node_ptr);
            put_node(node_ptr);
            node_ptr = nullptr;
        }
    }

};

// rotate with left child
// if it is inserted into the left subtree of the left subtree
//       |                       |
//       k2                      k1
//      /  \                    /  \
//     k1   Z      ------>     X   k2
//    /  \                    /   / \
//   X    Y                  X'  Y   Z
//  /
// X'
// X' may be at the left of the X or right of the X
// here `node_ptr` is `k2`
template <typename T, typename Compare>
void avltree<T, Compare>::rotate_with_left(avltree_node<T>*& node_ptr) {
    avltree_node<T>* k1 = left(node_ptr);
    avltree_node<T>* k2 = node_ptr;

    left(k2) = right(k1);
    if (right(k1) != nullptr)
        parent(right(k1)) = k2;
    right(k1) = k2;
    if (left(parent(k2)) == k2) {
        left(parent(k2)) = k1;
    }
    else {
        right(parent(k2)) = k1;
    }
    parent(k1) = parent(k2);
    parent(k2) = k1;

    k2->height = std::max(height(left(k2)), height(right(k2))) + 1;
    k1->height = std::max(height(left(k1)), height(k2)) + 1;
    node_ptr = k1;
}

// rotate with right child
// if it is inserted into the right subtree of the right subtree
//       |                             |
//      K2                             K1
//     /  \                           /  \
//    X    k1         ----->         K2   Z
//         / \                      /  \   \
//        Y   Z                    X    Y   Z'
//             \
//              Z'
// Z' may be at the left of the Z or right of the Z
// here `node_ptr` is `k2`
template <typename T, typename Compare>
void avltree<T, Compare>::rotate_with_right(avltree_node<T>*& node_ptr) {
    avltree_node<T>* k1 = right(node_ptr);
    avltree_node<T>* k2 = node_ptr;

    right(k2) = left(k1);
    if (left(k1) != nullptr)
        parent(left(k1)) = k2;
    left(k1) = k2;
    if (left(parent(k2)) == k2) {
        left(parent(k2)) = k1;
    }
    else {
        right(parent(k2)) = k1;
    }
    parent(k1) = parent(k2);
    parent(k2) = k1;

    k2->height = std::max(height(left(k2)), height(right(k2))) + 1;
    k1->height = std::max(height(k2), height(right(k1))) + 1;
    node_ptr = k1;
}

// if it is inserted into the right subtree of the left subtree
//       k3                k3              k2
//      /  \              /  \            /  \
//     k1   C    --->    k2   C  --->    k1   k3
//    / \               /               / \     \
//   A   k2            k1              A   B     C
//       /            / \
//      B            A   B
// here `node_ptr` is `k3`
template <typename T, typename Compare>
void avltree<T, Compare>::double_rotate_with_left(avltree_node<T>*& node_ptr) {
    rotate_with_right(right(node_ptr));
    rotate_with_left(node_ptr);
}

// if it is inserted into the left subtree of the right subtree
//       k3              k3                 k2
//      /  \            /  \               /  \
//     A    k1   --->  A    k2     --->  k3    k1
//         / \             /  \         /  \     \
//        K2  C           B    k1      A    B     C
//       /                      \
//      B                        C
// here `node_ptr` is `k3`
template <typename T, typename Compare>
void avltree<T, Compare>::double_rotate_with_right(avltree_node<T>*& node_ptr) {
    rotate_with_left(right(node_ptr));
    rotate_with_right(node_ptr);
}

#endif //! AVL_TREE_H
