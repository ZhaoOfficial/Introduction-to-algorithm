#ifndef GRAPHBASICS_SPARSEGRAPH_H
#define GRAPHBASICS_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include "Edge.h"

using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::ostream;

namespace MyGraph {

    // represents by adjacent list
    template<typename T>
    class SparseGraph {
    private:
        int numOfVertices, numOfEdges;
        bool directed;
        // the adjacent list
        vector<list<Edge<T>*>> adjacentList;
    public:
        SparseGraph(int numOfVertices, bool directed) : numOfVertices(numOfVertices), directed(directed), numOfEdges(0) {

            adjacentList = vector<list<Edge<T>* >>(numOfVertices);

        }

        ~SparseGraph() {
            for (int i = 0; i < numOfVertices; i++) {
                for (auto it = adjacentList[i].begin(); it != adjacentList[i].end(); it++) {
                    delete *it; //?????????????
                }
            }
        }

        int V() {//返回图中节点的数量
            return numOfVertices;
        }

        int E() {//返回图中边的数量
            return numOfEdges;
        }

        bool hasEdge(int start, int last) {//判断v节点与w节点之间是否存在边
            assert(start >= 0 && start < numOfVertices);
            assert(last >= 0 && last < numOfVertices);
            for (auto it = adjacentList[start].begin(); it != adjacentList[start].end(); it++)
                if ((*it)->theOtherEndPoint(start) == last)
                    return true;
            return false;
        }

        void addEdge(int start, int last, T weight) {
            assert(start >= 0 && start < numOfVertices);
            assert(last >= 0 && last < numOfVertices);

            // if there is an edge, the we update it
            if (this->hasEdge(start, last)) {
                for (auto it = adjacentList[start].begin(); it != adjacentList[start].end(); )
                    if ((*it)->theOtherEndPoint(start) == last) {
                        delete* it;
                        it = adjacentList[start].erase(it);
                    }
                    else
                        it++;

                if (start != last && !directed) {
                    for (auto it = adjacentList[last].begin(); it != adjacentList[last].end(); )
                        if ((*it)->theOtherEndPoint(start) == start) {
                            delete* it;
                            adjacentList[last].erase(it);
                        }
                        else
                            it++;
                }
                numOfEdges--;
            }

            //add new edge
            auto it = adjacentList[start].begin();
            while (it != adjacentList[start].end() && (*it)->theOtherEndPoint(start) < last)
                it++;

            if (it == adjacentList[start].end())
                adjacentList[start].push_back(new Edge<T>(start, last, weight));
            else
            // it will insert before iterator.
                adjacentList[start].insert(it, new Edge<T>(start, last, weight));

            if (start != last && !directed) {
                auto it = adjacentList[last].begin();
                while (it != adjacentList[last].end() && (*it)->theOtherEndPoint(last) < start)
                    it++;

                if (it == adjacentList[last].end())
                    adjacentList[last].push_back(new Edge<T>(last, start, weight));
                else
                    adjacentList[last].insert(it, new Edge<T>(last, start, weight));
            }

            numOfEdges++;
        }

        void printGraph() {
            for (int i = 0; i < numOfVertices; i++) {
                cout << "Vertex " << i << ":\t";
                for (auto it = adjacentList[i].begin(); it != adjacentList[i].end(); it++)
                    cout << "(to:" << (*it)->theOtherEndPoint(i) << ", weight: " << (*it)->weight() << ")\t";
                cout << endl;
            }
            cout << endl;
        }

        class adjIterator {
        private:
            SparseGraph &graph;
            int vertex;
            typename list<Edge<T>*>::iterator it;
        public:
            adjIterator(SparseGraph &graph, int vertex) : graph(graph) {
                assert(vertex >= 0 && vertex < graph.numOfVertices);
                this->vertex = vertex;
                it = graph.adjacentList[vertex].begin();
            }

            ~adjIterator() {}

            Edge<T> *begin() {
                if (it != graph.adjacentList[vertex].end()) 
                    return *it;
                return nullptr;
            }

            Edge<T> *next() {
                it++;
                if (it != graph.adjacentList[vertex].end()) {
                    return *it;
                }
                return nullptr;
            }

            bool isEnd() {
                return it == graph.adjacentList[vertex].end();
            }
        };
    };
};


#endif //GRAPHBASICS_SPARSEGRAPH_H
