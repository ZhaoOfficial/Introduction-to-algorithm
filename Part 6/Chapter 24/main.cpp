#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "../Chapter 23/SparseGraph.hpp"
#include "../Chapter 23/DenseGraph.hpp"
#include "ShortestPath.hpp"

using namespace std;

int main() {

    int vertices = 10;
    int egdes = 25;
    srand(time(NULL));

    //sparseGraph
    SparseGraph sparseGraph(vertices, true);
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
    DenseGraph denseGraph(vertices, true);
    for (int i = 0; denseGraph.E() < egdes; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        while (a == b) {
            a = rand() % vertices;
            b = rand() % vertices;
        }
        denseGraph.addEdge(a, b, (double)i);
    }

    ShortestPath<SparseGraph> ShortestPathSparseGraph(sparseGraph);
    sparseGraph.printGraph();
    ShortestPathSparseGraph.Dijkstra(0, vertices - 1);

    ShortestPath<DenseGraph> ShortestPathDenseGraph(denseGraph);
    denseGraph.printGraph();
    ShortestPathDenseGraph.Dijkstra(0, vertices - 1);


    return 0;
}