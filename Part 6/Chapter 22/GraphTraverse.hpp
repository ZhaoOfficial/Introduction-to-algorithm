#ifndef GRAPHBASICS_TRAVERSE_HPP
#define GRAPHBASICS_TRAVERSE_HPP
#include <iostream>
#include <cassert>
#include <deque>
#include <vector>
#include <memory.h>

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

        void depthFirstSearch() {
            bool *isVisited = new bool[this->G.V()]{false};
            
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

        void breadthFirstSearch() {
            bool *isVisited = new bool[this->G.V()]{false};
            
            deque<int> queue;
            cout << "BFS with source " << this->source << ": ";
            queue.push_back(this->source);
            isVisited[this->source] = true;

            while (!queue.empty()) {
                int current = queue.front();
                typename Graph::adjIterator adj(this->G, current);

                for (auto it = adj.begin(); it != adj.end(); adj.next(it)) {
                    if (!isVisited[(*it)->endPoint()]) {
                        queue.push_back((*it)->endPoint());
                        isVisited[(*it)->endPoint()] = true;
                        cout << (*it)->endPoint() << ' ';
                    }
                }
                queue.pop_front();
            }
            cout << endl;
            delete [] isVisited;
        }

        void path(int endIndex) {
            bool *isVisited = new bool[G.V()]{false};
            // distance from source
            int *dist = new int[G.V()];
            int *from = new int[G.V()];
            
            memset(dist, -1, sizeof(int) * G.V());
            memset(from, -1, sizeof(int) * G.V());

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
            while (endIndex != this->source) {
                stack.push_back(endIndex);
                endIndex = from[endIndex];
            }

            if (stack.empty()) {
                cout << "No Path!" << endl;
            }
            else {
                cout << "Start from source " << this->source << ": ";
                for (auto it = stack.rbegin(); it != stack.rend(); it++) {
                    cout << *it << ' ';
                }
                cout << endl;
            }
            
            delete [] isVisited;
            delete [] dist;
            delete [] from;
        }
    };

};




#endif // GRAPHBASICS_SPARSEGRAPH_HPP
