#ifndef GRAPHBASICS_SPARSEGRAPH_HPP
#define GRAPHBASICS_SPARSEGRAPH_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include "Edge.hpp"

using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::ostream;

// represents by adjacent list
class SparseGraph {
private:
    int numOfVertices;
    int numOfEdges;
    bool directed;

    // the adjacent list
    vector<list<Edge*>> adjacentList;
public:
    SparseGraph(int numOfVertices, bool directed) : numOfVertices(numOfVertices), directed(directed), numOfEdges(0) {
        this->adjacentList = vector<list<Edge*>>(numOfVertices);
    }

    ~SparseGraph() {
        for (int i = 0; i < numOfVertices; i++) {
            for (auto it = adjacentList[i].begin(); it != adjacentList[i].end(); it++) {
                delete *it;
            }
        }
    }

    int V() const {
        return numOfVertices;
    }

    int E() const {
        return numOfEdges;
    }

    bool isDirected() const {
        return directed;
    }

    bool hasEdge(int startIndex, int endIndex) {
        assert(startIndex >= 0 && startIndex < numOfVertices);
        assert(endIndex >= 0 && endIndex < numOfVertices);

        // for each edge start from startIndex
        for (auto it = adjacentList[startIndex].begin(); it != adjacentList[startIndex].end(); it++) {
            if ((*it)->theOtherEndPoint(startIndex) == endIndex) {
                return true;
            }
        }
        return false;
    }

    void addEdge(int startIndex, int endIndex, double weight) {
        assert(startIndex >= 0 && startIndex < numOfVertices);
        assert(endIndex >= 0 && endIndex < numOfVertices);

        // if there is an edge, the we update it
        if (this->hasEdge(startIndex, endIndex)) {
            auto it = adjacentList[startIndex].begin();
            while ((*it)->theOtherEndPoint(startIndex) != endIndex) {
                it++;
            }
            (*it)->setWeight(weight);
            if (startIndex != endIndex && !this->isDirected()) {
                auto it = adjacentList[endIndex].begin();
                while ((*it)->theOtherEndPoint(endIndex) != startIndex) {
                    it++;
                }
                (*it)->setWeight(weight);
            }
            return;
        }

        //add new edge
        auto it = adjacentList[startIndex].begin();
        while (it != adjacentList[startIndex].end() && (*it)->theOtherEndPoint(startIndex) < endIndex) {
            it++;
        }
        // it will insert before iterator.
        adjacentList[startIndex].insert(it, new Edge(startIndex, endIndex, weight));

        if (startIndex != endIndex && !this->isDirected()) {
            auto it = adjacentList[endIndex].begin();
            while (it != adjacentList[endIndex].end() && (*it)->theOtherEndPoint(endIndex) < startIndex) {
                it++;
            }

            adjacentList[endIndex].insert(it, new Edge(endIndex, startIndex, weight));
        }

        this->numOfEdges++;
    }

    void printGraph() {
        for (int i = 0; i < numOfVertices; i++) {
            cout << "Vertex " << i << ":\t";
            for (auto it = adjacentList[i].begin(); it != adjacentList[i].end(); it++) {
                cout << "(to:" << (*it)->theOtherEndPoint(i) << ", weight: " << (*it)->weight() << ")\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    class adjIterator {
    private:
        SparseGraph &graph;
        int vertex;
            
    public:
        adjIterator(SparseGraph &graph, int vertex) : graph(graph), vertex(vertex) {
            assert(vertex >= 0 && vertex < graph.numOfVertices);
        }

        ~adjIterator() {}

        auto begin() {
            return graph.adjacentList[vertex].begin();
        }

        auto end() {
            return graph.adjacentList[vertex].end();
        }

        void next(list<Edge*>::iterator& it) {
            it++;
        }
    };
};


#endif //GRAPHBASICS_SPARSEGRAPH_HPP
