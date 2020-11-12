#ifndef GRAPHBASICS_DENSEGRAPH_H
#define GRAPHBASICS_DENSEGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>
#include "Edge.h"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;

namespace MyGraph {

    // represents by adjacent matrix
    template<typename T>
    class DenseGraph {
    private:
        int numOfVertices, numOfEdges;
        bool directed;
        // the adjacent matrix
        vector<vector<Edge<T>*>> adjacentMatrix;
    public:
        DenseGraph(int numOfVertices, bool directed) : numOfVertices(numOfVertices), directed(directed), numOfEdges(0) {

            adjacentMatrix = vector<vector<Edge<T>* >>(numOfVertices, vector<Edge<T> *>(numOfVertices, nullptr));

        }

        ~DenseGraph() {
            for (int i = 0; i < numOfVertices; i++) {
                for (int j = 0; j < numOfVertices; j++) {
                    if (adjacentMatrix[i][j])
                        delete adjacentMatrix[i][j];
                }
            }
        }

        int V() {
            return numOfVertices;
        };

        int E() {
            return numOfEdges;
        };

        void addEdge(int start, int end, T weight) {
            assert(start >= 0 && start < numOfVertices);
            assert(end >= 0 && end < numOfVertices);

            // if there is an edge, the we update it
            if (this->hasEdge(start, end)) {
                adjacentMatrix[start][end]->setWeight(weight);
                if (start != end && !directed) {
                    adjacentMatrix[end][start]->setWeight(weight);
                }
                numOfEdges--;
            }

            //add new edge
            adjacentMatrix[start][end] = new Edge<T>(start, end, weight);
            if (start != end && !directed) {
                adjacentMatrix[end][start] = new Edge<T>(end, start, weight);
            }
            numOfEdges++;
        }

        bool hasEdge(int start, int end) {
            assert(start >= 0 && start < numOfVertices);
            assert(end >= 0 && end < numOfVertices);
            return adjacentMatrix[start][end] != NULL;
        }

        void printGraph() {
            for (int i = 0; i < numOfVertices; i++) {
                for (int j = 0; j < numOfVertices; j++) {
                    if (adjacentMatrix[i][j])
                        cout << adjacentMatrix[i][j]->weight() << "\t";
                    else
                        cout << "NAN\t";
                }
                cout << endl;
            }
        }

        class adjIterator {
        private:
            DenseGraph& graph;
            int vertex;
            int index;

        public:
            adjIterator(DenseGraph& graph, int vertex) : graph(graph) {
                assert(vertex >= 0 && vertex < graph.numOfVertices);
                this->index = -1;
                this->vertex = vertex;
            }

            ~adjIterator() {};

            // since the first element of one particular row is not always valid,
            // then we need to find the first valid element
            Edge<T> *begin() {
                return next();
            }

            // iterate until we find a valid element.
            Edge<T> *next() {
                index++;
                for (; index < graph.V(); index++) {
                    if (graph.adjacentMatrix[vertex][index]) {
                        return graph.adjacentMatrix[vertex][index];
                    }
                }
                return nullptr;
            }

            bool isEnd() {
                return index >= graph.V();
            }
        };
    };
};

#endif //GRAPHBASICS_DENSEGRAPH_H
