#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <limits>
#include "../Chapter 23/Edge.hpp"

using std::cout;
using std::endl;
using std::pair;
using std::queue;
using std::vector;
using std::priority_queue;
using std::numeric_limits;

const double DOUBLE_MAX = numeric_limits<double>::max();

template <typename Graph>
class ShortestPath {
private:
    Graph &G;

public:
    ShortestPath(Graph &G) : G(G) {}
    ~ShortestPath() {}

    // O(|V|) memory
    // O(|V|^2 + |E|) time 
    // if we use a binary heap to find
    // the smallest unchecked vertex
    // O(|V|ln|V| + |E|ln|V|)
    // Fibonacci heap O(|E| + |V|ln|V|)

    void Dijkstra(int startIndex, int endIndex) {

        int n = this->G.V(), m = 1;
        assert(this->G.isDirected());
        assert(startIndex >= 0 && startIndex < n);
        assert(endIndex >= 0 && endIndex < n);


        vector<pair<double, bool>> dist(n, std::make_pair(DOUBLE_MAX, false));
        vector<int> from(n, -1);

        queue<Edge> AllEdges;
        typename Graph::adjIterator adj(G, startIndex);
        for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
            AllEdges.push(**it);
        }
        dist[startIndex].first = 0.0;


        Edge current;
        while (m < n && !AllEdges.empty()) {
            while (!AllEdges.empty()) {
                current = AllEdges.front();
                AllEdges.pop();

                int res = dist[current.startPoint()].first + current.weight();
                if (res < dist[current.endPoint()].first) {
                    dist[current.endPoint()].first = res;
                    from[current.endPoint()] = current.startPoint();
                }
            }
            dist[current.startPoint()].second = true;

            int findMin;
            double localMin = DOUBLE_MAX;
            for (int i = 0; i < n; i++) {
                if (dist[i].second == false) {
                    if (dist[i].first <= localMin) {
                        findMin = i;
                        localMin = dist[i].first;
                    }
                }
            }

            typename Graph::adjIterator adj(G, findMin);
            for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                AllEdges.push(**it);
            }

            m++;
        }

        vector<int> stack;
        while (endIndex != -1) {
            stack.push_back(endIndex);
            endIndex = from[endIndex];
        }

        if (stack.size() == 1) {
            cout << "No Path!" << endl;
        }
        else {
            cout << "Start from source " << startIndex << ": ";
            for (auto it = stack.rbegin(); it != stack.rend(); it++) {
                cout << *it << ' ';
            }
            cout << endl;
        }

    }

};

#endif // SHORTEST_PATH_HPP
