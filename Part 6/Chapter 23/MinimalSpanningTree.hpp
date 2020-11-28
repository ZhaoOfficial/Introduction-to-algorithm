#ifndef MINIMUM_SPANNINING_TREE_HPP
#define MINIMUM_SPANNINING_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include "Edge.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::sort;
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
        priority_queue<Edge, vector<Edge>, std::greater<Edge>> edge;
        int m = 1, n = G.V();
        double sum = 0.0;
        vector<bool> inTree(n, false);
        vector<int> from(n, 0);

        typename Graph::adjIterator adj(G, 0);
        for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
            edge.push(**it);
        }
        inTree[0] = true;

        Edge current;
        while (m < n) {
            current = edge.top();
            edge.pop();
            if (!inTree[current.endPoint()]) {
                inTree[current.endPoint()] = true;
                sum += current.weight();
                from[current.endPoint()] = current.startPoint();
                typename Graph::adjIterator adj(G, current.endPoint());
                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!inTree[(*it)->endPoint()]) {
                        edge.push(**it);
                    }
                }
                m++;
            }
        }

        cout << "Prim       : ";
        for (int i = 0; i < n; i++) {
            cout << i << ' ';
        }
        cout << "\nparent node: ";
        for (int i = 0; i < n; i++) {
            cout << from[i] << ' ';
        }
        cout << "\nsum of tree: " << sum << endl;
    }


    // O(|E|ln|E|) sorting the edge and disjoint set
    // for finding the connection component
    void kruskal() {
        int m = 1, n = G.V();
        double sum = 0.0;
        vector<int> component;
        vector<int> from(n, 0);

        vector<Edge> edge;
        for (int i = 0; i < n; i++) {
            component.push_back(i);
            typename Graph::adjIterator adj(G, i);
            for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                if ((**it).endPoint() > i) {
                    edge.push_back(**it);
                }
            }
        }

        sort(edge.begin(), edge.end());

        auto it = edge.begin();
        while (m < n) {
            if (getf(component, (*it).startPoint()) != getf(component, (*it).endPoint())) {
                merge(component, (*it).startPoint(), (*it).endPoint());
                from[(*it).endPoint()] = (*it).startPoint();
                sum += (*it).weight();
                m++;
            }
            it++;
        }

        cout << "Kruskal    : ";
        for (int i = 0; i < n; i++) {
            cout << i << ' ';
        }
        cout << "\nparent node: ";
        for (int i = 0; i < n; i++) {
            cout << from[i] << ' ';
        }
        cout << "\nsum of tree: " << sum << endl;
    }

private:


    int getf(vector<int>& component, int a) {
        if (component[a] == a) {
            return a;
        }
        a = getf(component, component[a]);
        return a;
    }

    void merge(vector<int>& component, int a, int b) {
        int u = getf(component, a);
        int v = getf(component, b);
        if (u != v) {
            component[v] = u;
        }
    }
};
#endif // MINIMUM_SPANNINING_TREE_HPP