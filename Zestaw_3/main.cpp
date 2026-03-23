#include <iostream>
#include <cassert>
#include "graph.hpp"
 
int main() {
    // graf nieskierowany
    Graph G(4);
    assert(!G.is_directed());
    assert(G.v() == 4);
    assert(G.e() == 0);
 
    G.add_edge(0, 1);
    G.add_edge(0, 2);
    G.add_edge(0, 3);
    G.add_edge(1, 2);
    G.add_edge(2, 3);
 
    assert(G.e() == 5);
    assert(G.has_edge(0, 1));
    assert(G.has_edge(1, 0)); // symetria
    assert(!G.has_edge(1, 3));
 
    assert(G.degree(0) == 3);
    assert(G.degree(1) == 2);
 
    G.del_edge(0, 2);
    assert(!G.has_edge(0, 2));
    assert(!G.has_edge(2, 0));
    assert(G.e() == 4);
 
    G.del_node(0);
    assert(!G.has_edge(0, 1));
    assert(G.e() == 2);
 
    G.clear();
    assert(G.e() == 0);
 
    // graf skierowany
    Graph GS(4, true);
    assert(GS.is_directed());
 
    GS.add_edge(0, 1);
    GS.add_edge(0, 3);
    GS.add_edge(1, 2);
    GS.add_edge(2, 0);
    GS.add_edge(2, 3);
 
    assert(GS.e() == 5);
    assert(GS.has_edge(0, 1));
    assert(!GS.has_edge(1, 0));
    assert(GS.outdegree(0) == 2);
    assert(GS.indegree(0) == 1);
    assert(GS.outdegree(3) == 0);
    assert(GS.indegree(3) == 2);
 
    // metody z Edge
    Edge<int> krawedz(1, 2);
    assert(GS.has_edge(krawedz));
    GS.del_edge(krawedz);
    assert(!GS.has_edge(krawedz));
    GS.add_edge(krawedz);
    assert(GS.has_edge(krawedz));
 
    GS.display();
 
    std::cout << "Wszystkie testy OK\n";
    return 0;
}