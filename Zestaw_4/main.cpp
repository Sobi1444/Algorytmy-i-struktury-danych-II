#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    Graph G(4, true);

    G.add_edge(0, 1);
    G.add_edge(0, 3);
    G.add_edge(1, 2);
    G.add_edge(2, 0);
    G.add_edge(2, 3);

    G.display();

    assert(G.v() == 4);
    assert(G.e() == 5);
    assert(G.has_edge(0, 1));
    assert(!G.has_edge(3, 0));
    assert(G.outdegree(0) == 2);
    assert(G.indegree(0) == 1);

    std::cout << "wierzcholki: ";
    for (auto it = G.node_begin(); it != G.node_end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "krawedzie: ";
    for (auto it = G.edge_begin(); it != G.edge_end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "sasiedzi 0: ";
    for (auto it = G.adj_begin(0); it != G.adj_end(0); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    Graph H(4);
    H.add_edge(0, 1);
    H.add_edge(0, 2);
    H.add_edge(0, 3);
    H.add_edge(1, 2);
    H.add_edge(2, 3);

    assert(H.e() == 5);
    assert(H.degree(0) == 3);

    H.del_edge(0, 1);
    assert(!H.has_edge(0, 1));
    assert(!H.has_edge(1, 0));

    H.del_node(2);
    assert(!H.has_edge(0, 2));

    return 0;
}