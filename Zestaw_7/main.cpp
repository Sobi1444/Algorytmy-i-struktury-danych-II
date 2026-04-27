#include <iostream>
#include <cassert>
#include "connected.hpp"
 
int main() {
    // Graf nieskierowany niespójny z n=10
    // skladowa 0: 0,1,2,3
    // 1: 4,5,6
    // 2: 7,8
    // 3: 9
 
    Graph<int> G(false);
 
    for (int i = 0; i < 10; i++)
        G.add_node(i);
 
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G.add_edge(2, 3);
 
    G.add_edge(4, 5);
    G.add_edge(5, 6);
 
    G.add_edge(7, 8);
 
    auto algorithm = ConnectedComponents<int, Graph<int>>(G);
    algorithm.run();
 
    for (auto pair : algorithm.component)
        std::cout << pair.first << " component " << pair.second << std::endl;
 
    std::cout << "total components " << algorithm.ncc << std::endl;
 
    // wierzcholki w tej samej skladowej muszą miec ten sam numer
    assert(algorithm.component[0] == algorithm.component[1]);
    assert(algorithm.component[1] == algorithm.component[2]);
    assert(algorithm.component[2] == algorithm.component[3]);
 
    assert(algorithm.component[4] == algorithm.component[5]);
    assert(algorithm.component[5] == algorithm.component[6]);
 
    assert(algorithm.component[7] == algorithm.component[8]);
 
    // wierzchołki z roznych skladowych musza miec rozne numery
    assert(algorithm.component[0] != algorithm.component[4]);
    assert(algorithm.component[0] != algorithm.component[7]);
    assert(algorithm.component[0] != algorithm.component[9]);
    assert(algorithm.component[4] != algorithm.component[7]);
    assert(algorithm.component[4] != algorithm.component[9]);
    assert(algorithm.component[7] != algorithm.component[9]);
 
    // wszystkie skladowe
    assert(algorithm.ncc == 4);
 
    std::cout << "wszystkie testy OK" << std::endl;
 
    return 0;
}
