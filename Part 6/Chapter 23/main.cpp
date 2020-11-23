#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "SparseGraph.hpp"
#include "DenseGraph.hpp"
#include "MinimalSpanningTree.hpp"

using namespace std;

int main() {
    int vertices = 5;
    int egdes = 10;
    srand(time(NULL));

    //sparseGraph
    SparseGraph sparseGraph(vertices, false);
    for (int i = 0; sparseGraph.E() < egdes; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        while (a == b) {
            a = rand() % vertices;
            b = rand() % vertices;
        }
        sparseGraph.addEdge(a, b, (double)i);
    }

    //DenseGraph
    DenseGraph denseGraph(vertices, false);
    for (int i = 0; denseGraph.E() < egdes; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        while (a == b) {
            a = rand() % vertices;
            b = rand() % vertices;
        }
        denseGraph.addEdge(a, b, (double)i);
    }

    MinimalSpanningTree<SparseGraph> MinimalSpanningTreeSparseGraph(sparseGraph);
    MinimalSpanningTreeSparseGraph.prim();

    MinimalSpanningTree<DenseGraph> MinimalSpanningTreeDenseGraph(denseGraph);
    MinimalSpanningTreeDenseGraph.prim();

    return 0;
}
