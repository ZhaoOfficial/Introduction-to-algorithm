#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


class DisjointSet {
public:
    DisjointSet(int size) : size(size) {
        for (int i = 0; i < size; i++) {
            root.push_back(i);
        }
    }

    virtual ~DisjointSet() {}

    int Find(int id) {
        while (id != root[id]) {
            id = root[id];
        }
        return id;
    }

    int FindWithPathCompression(int id) {
        if (id == root[id]) {
            return id;
        }
        id = FindWithPathCompression(root[id]);
        return root[id];
    }

    void GetUnion(int first, int second) {
        int a = FindWithPathCompression(first);
        int b = FindWithPathCompression(second);
        if (a != b) {
            root[b] = a;
        }
    }

private:
    vector<int> root;
    int size;
}