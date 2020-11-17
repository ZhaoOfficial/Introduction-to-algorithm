#ifndef GRAPHBASICS_TRAVERSE_HPP
#define GRAPHBASICS_TRAVERSE_HPP
#include <iostream>
#include <cassert>
#include <deque>
#include <memory.h>

using std::cout;
using std::endl;
using std::deque;

namespace MyGraph {

    template <typename Graph>
    class Traverse {
    private:
        Graph &G;
        // the starting node
        int source;
    public:
        Traverse(Graph &G, int source) : G(G), source(source) {}
        ~Traverse() {}

        void depthFirstSearch() {
            assert(this->source >= 0 && this->source < this->G.V());

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
            assert(this->source >= 0 && this->source < this->G.V());

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

    };

};




#endif // GRAPHBASICS_SPARSEGRAPH_HPP