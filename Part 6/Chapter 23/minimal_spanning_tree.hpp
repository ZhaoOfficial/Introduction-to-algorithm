#ifndef MINIMUM_SPANNINING_TREE_HPP
#define MINIMUM_SPANNINING_TREE_HPP

#include <iostream>
#include <cassert>
#include "../Chapter 22/Edge.hpp"

using std::cin;
using std::cout;
using std::endl;


namespace MyGraph {

    template <typename Graph>
    class MinimumSpanniningTree {
    private:
        Graph G;

    public:
        MinimumSpanniningTree(Graph &G) : G(G), minSum(0) {
            assert(!G.isDirected());        
        }

        virtual ~MinimumSpanniningTree() {}

        // 
        void prim(int startIndex) {
            

        }


        // 
        void dijkstra(int startIndex) {

        }

    };
};

#endif // MINIMUM_SPANNINING_TREE_HPP