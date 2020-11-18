#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "SparseGraph.hpp"
#include "DenseGraph.hpp"
#include "GraphTraverse.hpp"
// #include "Path.hpp"
// #include "shortPath.hpp"

using namespace std;
using namespace MyGraph;

int main() {
    int vertices = 20;
    int egdes = 100;
    srand(time(NULL));

    //sparseGraph
    SparseGraph<double> sparseGraph(vertices, false);
    for (int i = 0; sparseGraph.E() < egdes; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        while (a == b) {
            a = rand() % vertices;
            b = rand() % vertices;
        }
        sparseGraph.addEdge(a, b, (double)i);
    }
    for (int v = 0; v < vertices; v++) {
        cout << v << ": " << endl;
        // iterator
        SparseGraph<double>::adjIterator it1(sparseGraph, v);
        for (auto w = it1.begin(); w != it1.end(); it1.next(w))
            cout << **w;
        cout << endl;
    }
    sparseGraph.printGraph();

    //DenseGraph
    DenseGraph<double> denseGraph(vertices, false);
    for (int i = 0; denseGraph.E() < egdes; i++) {
        int a = rand() % vertices;
        int b = rand() % vertices;
        while (a == b) {
            a = rand() % vertices;
            b = rand() % vertices;
        }
        denseGraph.addEdge(a, b, (double)i);
    }
    for (int v = 0; v < vertices; v++) {
        cout << v << ": " << endl;
        DenseGraph<double>::adjIterator it2(denseGraph, v);
        for (auto w = it2.begin(); w != it2.end(); it2.next(w))
            cout << **w;
        cout << endl;
    }

    denseGraph.printGraph();

    Traverse<SparseGraph<double>> traverseSparseGraph(sparseGraph, 0);
    traverseSparseGraph.depthFirstSearch();
    traverseSparseGraph.breadthFirstSearch();
    traverseSparseGraph.path(19);

    Traverse<DenseGraph<double>> traverseDenseGraph(denseGraph, 0);
    traverseDenseGraph.depthFirstSearch();
    traverseDenseGraph.breadthFirstSearch();
    traverseDenseGraph.path(19);

    return 0;
}
