#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "SparseGraph.hpp"
#include "DenseGraph.hpp"
#include "MinimalSpanningTree.hpp"

using namespace std;

int main() {
    int vertices = 9;
    int egdes = 14;
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
    //denseGraph.addEdge(0, 1, (double)4);
    //denseGraph.addEdge(0, 7, (double)8);
    //denseGraph.addEdge(1, 7, (double)11);
    //denseGraph.addEdge(1, 2, (double)8);
    //denseGraph.addEdge(2, 3, (double)7);
    //denseGraph.addEdge(2, 5, (double)4);
    //denseGraph.addEdge(2, 8, (double)2);
    //denseGraph.addEdge(3, 4, (double)9);
    //denseGraph.addEdge(3, 5, (double)14);
    //denseGraph.addEdge(4, 5, (double)10);
    //denseGraph.addEdge(5, 6, (double)2);
    //denseGraph.addEdge(6, 7, (double)1);
    //denseGraph.addEdge(6, 8, (double)6);
    //denseGraph.addEdge(7, 8, (double)7);

    MinimalSpanningTree<SparseGraph> MinimalSpanningTreeSparseGraph(sparseGraph);
    sparseGraph.printGraph();
    MinimalSpanningTreeSparseGraph.prim();
    MinimalSpanningTreeSparseGraph.kruskal();

    MinimalSpanningTree<DenseGraph> MinimalSpanningTreeDenseGraph(denseGraph);
    denseGraph.printGraph();
    MinimalSpanningTreeDenseGraph.prim();
    MinimalSpanningTreeDenseGraph.kruskal();

    return 0;
}
