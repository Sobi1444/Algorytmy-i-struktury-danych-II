#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "graph.hpp"
#include "bfs.hpp"
 
// generuje spojny graf losowy z n wierzchokkami
Graph<int> generate_connected_graph(int n) {
    Graph<int> g;
 
    for (int i = 0; i < n; i++)
        g.add_node(i);
 
    // najpierw tworzymy drzewo spinajace zeby byla spojnosc zapewniona
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++)
        perm[i] = i;
 
    for (int i = n - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(perm[i], perm[j]);
    }
 
    for (int i = 1; i < n; i++)
        g.add_edge(perm[i - 1], perm[i]);
 
    // dodanie losowych krawedzi
    int extra = n;
    for (int k = 0; k < extra; k++) {
        int u = std::rand() % n;
        int v = std::rand() % n;
        if (u != v)
            g.add_edge(u, v);
    }
 
    return g;
}
 
int main() {
    std::srand(std::time(nullptr));
 
    const int n = 10;
    Graph<int> g = generate_connected_graph(n);
 
    auto bfs = BFS<int, Graph<int>>(g);
    bfs.run(0);
 
    std::cout << "BFS preorder:  ";
    for (auto& node : bfs.preorder)
        std::cout << node << " ";
    std::cout << "\n";
 
    std::cout << "BFS postorder: ";
    for (auto& node : bfs.postorder)
        std::cout << node << " ";
    std::cout << "\n";
 
    // testy
    assert(bfs.preorder.size() == n);
    assert(bfs.postorder.size() == n);
    // pierwszy odwiedzony to wierzcholek startowy
    assert(bfs.preorder[0] == 0);
 
    std::cout << "Testy OK\n";
 
    return 0;
}