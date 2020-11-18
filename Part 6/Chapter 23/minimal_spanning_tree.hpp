#include <iostream>
#include <cassert>
#include "../Chapter 22/DenseGraph.hpp"
#include "../Chapter 22/SparseGraph.hpp"

using std::cin;
using std::cout;
using std::endl;


namespace MyGraph {

    template <typename Graph>
    class MinimumSpanniningTree {
    private:
        Graph G;
    public:
        MinimumSpanniningTree(Graph &G) : G(G) {
            assert(!G.isDirected());        
        }

        virtual ~MinimumSpanniningTree() {}

        // 
        void prim(int startIndex) {
            

        }



        void dijkstra(int startIndex) {

        }

    };
};

