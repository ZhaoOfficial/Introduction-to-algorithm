#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class DisjointSet;

template <typename T>
class node {
public:
    node() : root(nullptr), next(nullptr) {}
    node(T data) : data(data), root(nullptr), next(nullptr) {}
    ~node() {}

    DisjointSet<T>* root;
    T data;
    node* next;
};

template <typename T>
class DisjointSet {
public:
    DisjointSet() : head(nullptr), tail(nullptr) {}
    ~DisjointSet() {}

    void MakeSet(T value) {
        node<T>* new_node = new node<T>(value);
        new_node->root = this;

        if (head == nullptr)
            head = new_node;
        else
            tail->next = new_node;

        tail = new_node;
    }

    DisjointSet* FindSet(T value) {
        node<T>* temp = this->head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return this;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    DisjointSet* FindSet(node<T>* target) {
        return target->root;
    }

    DisjointSet& GetUnion(DisjointSet<T> other) {
        this->tail->next = other->head;
        node<T>* temp = other->head;
        while (temp != nullptr) {
            temp->root = this;
        }
        return *this;
    }

    node<T>* head;
    node<T>* tail;
};

int main() {
    return 0;
}
