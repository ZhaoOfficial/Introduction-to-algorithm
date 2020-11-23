#ifndef MINIMUM_SPANNINING_TREE_HPP
#define MINIMUM_SPANNINING_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <locale>
#include "Edge.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::numeric_limits;
using std::priority_queue;

const double DOUBLE_MAX = numeric_limits<double>::max();

template <typename Graph>
class MinimalSpanningTree {
private:
    // it will not call copy constructor
    // also it will not call destructor 
    Graph &G;

public:
    MinimalSpanningTree(Graph &G) : G(G) {
        assert(!G.isDirected());        
    }

    ~MinimalSpanningTree() {}

    // O(|V|^2 + |E|) we need to check all the neighbors, no optimal
    // O(|E|ln|V| + |V|ln|V|) binary heap, O(|V|) size.
    // O(|E| + |V|ln|V|) Fibonacci heap.
    void prim() {
        priority_queue<Edge*, vector<Edge*>, std::less<Edge*>> edge;
        int m = 1, n = G.V();
        bool* inTree = new bool[n] { false };
        int* from = new int[n]{ 0 };

        typename Graph::adjIterator adj(G, 0);
        for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
            edge.push(*it);
        }
        inTree[0] = true;

        Edge* current;
        while (m < n) {
            current = edge.top();
            edge.pop();
            if (!inTree[current->endPoint()]) {
                inTree[current->endPoint()] = true;
                from[current->endPoint()] = current->startPoint();
                typename Graph::adjIterator adj(G, current->endPoint());
                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!inTree[(*it)->endPoint()]) {
                        edge.push(*it);
                    }
                }
                m++;
            }
        }

        cout << "vertex: ";
        for (int i = 0; i < n; i++) {
            cout << i << ' ';
        }
        cout << "\nfrom  : ";
        for (int i = 0; i < n; i++) {
            cout << from[i] << ' ';
        }
        cout << endl;

        delete from;
        delete inTree;
    }


    // 
    void kruskal(int startIndex) {

    }

};

#endif // MINIMUM_SPANNINING_TREE_HPP