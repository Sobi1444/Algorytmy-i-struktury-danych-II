#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <set>
#include <cassert>
#include <cstdlib>
 
// prosta lista sasiedztwa z wagami
struct Edge {
    int to;
    float weight;
};
 
class Graph {
public:
    std::unordered_map<int, std::vector<Edge>> adj;
 
    void addEdge(int u, int v, float w) {
        adj[u].push_back({v, w});
        if (adj.find(v) == adj.end()) adj[v] = {};
    }
 
    std::vector<int> vertices() const {
        std::vector<int> vs;
        for (auto& p : adj) vs.push_back(p.first);
        return vs;
    }
};
 
template <typename T, typename G>
class Dijkstra {
    G& graph;
public:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, float> distance;
 
    Dijkstra(G& g) : graph(g) {}
    ~Dijkstra() = default;
 
    void run(T s) {
        const float INF = std::numeric_limits<float>::infinity();
 
        for (auto u : graph.vertices()) {
            distance[u] = INF;
            parent[u] = -1;
        }
        distance[s] = 0;
 
        // Q jako set par(dystans, wierzch) - minimum zawsze na poczatku
        std::set<std::pair<float, T>> Q;
        for (auto u : graph.vertices())
            Q.insert({distance[u], u});
 
        // krok 2: relaksacja krawedzi
        while (!Q.empty()) {
            auto it = Q.begin();
            float du = it->first;
            T u = it->second;
            Q.erase(it);
 
            for (auto& e : graph.adj[u]) {
                float alt = du + e.weight;
                if (alt < distance[e.to]) {
                    // zmiana priorytetu: usun stary wpis i wstaw nowy
                    Q.erase({distance[e.to], e.to});
                    distance[e.to] = alt;
                    parent[e.to] = u;
                    Q.insert({alt, e.to});
                }
            }
        }
    }
};
 
// testy na prostym grafie o znanych odleglosciach
void tests() {
    // graf: 0->1 (2), 0->2 (5), 1->2 (1), 1->3 (7), 2->3 (3)
    // najkrotsze od 0: d[0]=0, d[1]=2, d[2]=3, d[3]=6
    Graph G;
    G.addEdge(0, 1, 2);
    G.addEdge(0, 2, 5);
    G.addEdge(1, 2, 1);
    G.addEdge(1, 3, 7);
    G.addEdge(2, 3, 3);
 
    auto alg = Dijkstra<int, Graph>(G);
    alg.run(0);
 
    assert(alg.distance[0] == 0);
    assert(alg.distance[1] == 2);
    assert(alg.distance[2] == 3);
    assert(alg.distance[3] == 6);
 
    // poprzednicy
    assert(alg.parent[0] == -1);
    assert(alg.parent[1] == 0);
    assert(alg.parent[2] == 1);
    assert(alg.parent[3] == 2);
 
    // wierzcholek nieosiagalny
    Graph G2;
    G2.addEdge(0, 1, 1);
    G2.addEdge(2, 3, 1); // skladowa rozlaczna
 
    auto alg2 = Dijkstra<int, Graph>(G2);
    alg2.run(0);
 
    assert(alg2.distance[0] == 0);
    assert(alg2.distance[1] == 1);
    assert(alg2.distance[2] == std::numeric_limits<float>::infinity());
    assert(alg2.distance[3] == std::numeric_limits<float>::infinity());
 
    std::cout << "wszystkie testy OK\n";
}
 
int main() {
    tests();
 
    srand(42);
 
    Graph G;
    int n = 10;
 
    // losowy graf skierowany wazny
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && rand() % 3 == 0) {
                float w = (float)(rand() % 20 + 1);
                G.addEdge(u, v, w);
            }
        }
    }
 
    int source = 0;
 
    auto algorithm = Dijkstra<int, Graph>(G);
    algorithm.run(source);
 
    std::cout << "najkrotsze odleglosci od wierzcholka " << source << ":\n";
    for (auto& pair : algorithm.distance) {
        std::cout << "  wierzcholek " << pair.first << " : dystans = ";
        if (pair.second == std::numeric_limits<float>::infinity())
            std::cout << "inf";
        else
            std::cout << pair.second;
        std::cout << ", poprzednik = " << algorithm.parent[pair.first] << "\n";
    }
 
    return 0;
}
