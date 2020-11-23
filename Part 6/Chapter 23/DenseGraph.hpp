#ifndef GRAPHBASICS_DENSEGRAPH_HPP
#define GRAPHBASICS_DENSEGRAPH_HPP

#include <cassert>
#include <iostream>
#include <vector>
#include "Edge.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;


// represents by adjacent matrix
class DenseGraph {
private:
    int numOfVertices, numOfEdges;
    bool directed;
    // the adjacent matrix
    vector<vector<Edge*>> adjacentMatrix;
public:
    DenseGraph(int numOfVertices, bool directed) : numOfVertices(numOfVertices), directed(directed), numOfEdges(0) {
        adjacentMatrix = vector<vector<Edge*>>(numOfVertices, vector<Edge*>(numOfVertices, nullptr));
    }

    ~DenseGraph() {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {
                if (adjacentMatrix[i][j]) {
                    delete adjacentMatrix[i][j];
                }
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

    void addEdge(int startIndex, int endIndex, double weight) {
        assert(startIndex >= 0 && startIndex < numOfVertices);
        assert(endIndex >= 0 && endIndex < numOfVertices);

        // if there is an edge, the we update it
        if (this->hasEdge(startIndex, endIndex)) {
            adjacentMatrix[startIndex][endIndex]->setWeight(weight);
            if (startIndex != endIndex && !this->isDirected()) {
                adjacentMatrix[endIndex][startIndex]->setWeight(weight);
            }
            return;
        }

        //add new edge
        adjacentMatrix[startIndex][endIndex] = new Edge(startIndex, endIndex, weight);
        if (startIndex != endIndex && !this->isDirected()) {
            adjacentMatrix[endIndex][startIndex] = new Edge(endIndex, startIndex, weight);
        }
        this->numOfEdges++;
    }

    bool hasEdge(int startIndex, int endIndex) {
        assert(startIndex >= 0 && startIndex < numOfVertices);
        assert(endIndex >= 0 && endIndex < numOfVertices);

        return adjacentMatrix[startIndex][endIndex] != nullptr;
    }

    void printGraph() {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {
                if (adjacentMatrix[i][j]) {
                    cout << adjacentMatrix[i][j]->weight() << "\t";
                }
                else {
                    cout << "NAN\t";
                }
            }
            cout << endl;
        }
    }

    class adjIterator {
    private:
        DenseGraph& graph;
        int vertex;

    public:
        adjIterator(DenseGraph& graph, int vertex) : graph(graph), vertex(vertex) {
            assert(vertex >= 0 && vertex < graph.numOfVertices);
        }

        ~adjIterator() {};

        // since the first element of one particular row is not always valid,
        // then we need to find the first valid element
        auto begin() {
            auto it = graph.adjacentMatrix[vertex].begin();
            next(it);
            return it;
        }

        auto end() {
            return graph.adjacentMatrix[vertex].end();
        }

        void next(vector<Edge*>::iterator& it) {
            it++;
            while (it != graph.adjacentMatrix[vertex].end() && *it == nullptr) {
                it++;
            }
        }
    };
};

#endif //GRAPHBASICS_DENSEGRAPH_HPP
