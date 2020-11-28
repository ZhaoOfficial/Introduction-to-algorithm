#ifndef GRAPHBASICS_TRAVERSE_HPP
#define GRAPHBASICS_TRAVERSE_HPP

#include <iostream>
#include <cassert>
#include <deque>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::deque;

namespace MyGraph {

    template <typename Graph>
    class Traverse {
    private:
        Graph &G;
        // the starting node
        int source;
    public:
        Traverse(Graph &G, int source) : G(G), source(source) {
            assert(this->source >= 0 && this->source < this->G.V());
        }
        ~Traverse() {}

        // O(|V| + |E|)
        void depthFirstSearch() {
            vector<bool> isVisited(this->G.V(), false);
            deque<int> stack;
            cout << "DFS with source " << this->source << ": ";
            stack.push_back(this->source);
            isVisited[this->source] = true;

            while (!stack.empty()) {
                restart: int current = stack.back();
                typename Graph::adjIterator adj(this->G, current);
                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!isVisited[(*it)->endPoint()]) {
                        current = (*it)->endPoint();
                        stack.push_back(current);
                        isVisited[(*it)->endPoint()] = true;
                        cout << (*it)->endPoint() << ' ';
                        goto restart;
                    }
                }

                stack.pop_back();
            }
            cout << endl;
            delete[] isVisited;
        }

        // O(|V| + |E|)
        void breadthFirstSearch() {
            vector<bool> isVisited(this->G.V(), false);
            deque<int> queue;
            cout << "BFS with source " << this->source << ": ";
            queue.push_back(this->source);
            isVisited[this->source] = true;

            while (!queue.empty()) {
                int current = queue.front();
                queue.pop_front();
                typename Graph::adjIterator adj(this->G, current);

                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!isVisited[(*it)->endPoint()]) {
                        queue.push_back((*it)->endPoint());
                        isVisited[(*it)->endPoint()] = true;
                        cout << (*it)->endPoint() << ' ';
                    }
                }
            }
            cout << endl;
        }

        void path(int endIndex) {
            vector<bool> isVisited(this->G.V(), false);
            // distance from source
            vector<int> dist(this->G.V(), -1);
            vector<int> from(this->G.V(), -1);
            
            deque<int> queue;
            queue.push_back(this->source);
            isVisited[this->source] = true;
            dist[this->source] = 0;

            while (!queue.empty()) {
                int current = queue.front();
                typename Graph::adjIterator adj(G, current);

                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!isVisited[(*it)->endPoint()]) {
                        queue.push_back((*it)->endPoint());
                        isVisited[(*it)->endPoint()] = true;
                        from[(*it)->endPoint()] = current;
                        dist[(*it)->endPoint()] = dist[current] + 1;
                    }
                }
                queue.pop_front();
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
                auto it = stack.rbegin();
                cout << "Start from source " << *it << ": ";
                for (it++; it != stack.rend(); it++) {
                    cout << *it << ' ';
                }
                cout << endl;
            }

        }
    };

};

#endif // GRAPHBASICS_SPARSEGRAPH_HPP
