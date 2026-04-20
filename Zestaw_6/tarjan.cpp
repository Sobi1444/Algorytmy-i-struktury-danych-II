#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <stdexcept>
 
// prosty graf skierowany na listach sasiedztwa
// T to typ wierzcholka
template<typename T>
class Graph {
public:
    std::vector<T> nodes;
    std::unordered_map<T, std::vector<T>> adj;
 
    // dodaj wierzcholek jesli jeszcze nie istnieje
    void add_node(T u) {
        if (adj.find(u) == adj.end()) {
            nodes.push_back(u);
            adj[u] = {};
        }
    }
 
    void add_edge(T u, T v) {
        add_node(u);
        add_node(v);
        adj[u].push_back(v);
    }
 
    int v() const { return (int)nodes.size(); }
 
    // struktura krawedzi do weryfikacji
    struct Edge {
        T source;
        T target;
    };
 
    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        for (const T& node : nodes) {
            for (const T& nb : adj.at(node)) {
                result.push_back({node, nb});
            }
        }
        return result;
    }
};
 
// kolory do DFS
enum Color { WHITE, GREY, BLACK };
 
// DFSVisit
// post_action(u) to L.append(u)
template<typename T>
void DFSVisit(Graph<T>& graph, T u,
              std::unordered_map<T, Color>& color,
              std::vector<T>& L) {
 
    color[u] = GREY;
 
    for (const T& v : graph.adj[u]) {
        if (color[v] == WHITE) {
            DFSVisit(graph, v, color, L);
        } else if (color[v] == GREY) {
            // krawedz powrotna - graf ma cykl, nie jest dagiem
            throw std::runtime_error("Graf ma cykl - nie jest dagiem!");
        }
    }
 
    color[u] = BLACK;
    L.push_back(u); // post_action
}
 
// algorytm Tarjana
template<typename T, typename G>
std::vector<T> topsort_dfs(G& graph) {
    std::unordered_map<T, Color> color;
    std::vector<T> L; // lista wynikowa
 
    for (const T& u : graph.nodes) {
        color[u] = WHITE;
    }
 
    for (const T& u : graph.nodes) {
        if (color[u] == WHITE) {
            DFSVisit(graph, u, color, L);
        }
    }
 
    // odwrocenie listy
    std::reverse(L.begin(), L.end());
 
    return L;
}
 
// funkcja weryfikujaca poprawnosc sortowania
template<typename T>
void verify(Graph<T>& graph, std::vector<T>& sorted_nodes) {
    // dlugosc listy musi byc rowna liczbie wierzcholkow
    assert((int)sorted_nodes.size() == graph.v());
 
    std::unordered_map<T, int> idx;
    for (int i = 0; i < (int)sorted_nodes.size(); ++i) {
        idx[sorted_nodes[i]] = i;
    }
 
    for (auto& e : graph.edges()) {
        assert(idx[e.source] < idx[e.target]);
    }
}
 
// test 1: dag z przykladu n=10
void test_dag_podstawowy() {
    Graph<int> G;
 
    G.add_edge(0, 1);
    G.add_edge(0, 3);
    G.add_edge(1, 2);
    G.add_edge(3, 4);
    G.add_edge(4, 1);
    G.add_edge(4, 5);
    G.add_edge(5, 2);
    G.add_edge(6, 0);
    G.add_edge(7, 6);
    G.add_edge(8, 7);
    G.add_edge(9, 8);
 
    assert(G.v() == 10);
 
    std::vector<int> sorted_nodes = topsort_dfs<int>(G);
 
    std::cout << "Test 1 - porzadek topologiczny: ";
    for (int u : sorted_nodes) std::cout << u << " ";
    std::cout << std::endl;
 
    verify(G, sorted_nodes);
    std::cout << "Test 1 OK" << std::endl;
}
 
// test 2: prosty lancuch liniowy 0->1->2->...->9
void test_lancuch_liniowy() {
    Graph<int> G;
    for (int i = 0; i < 9; ++i) {
        G.add_edge(i, i + 1);
    }
 
    assert(G.v() == 10);
 
    std::vector<int> sorted_nodes = topsort_dfs<int>(G);
 
    std::cout << "Test 2 - lancuch liniowy: ";
    for (int u : sorted_nodes) std::cout << u << " ";
    std::cout << std::endl;
 
    // dla lancucha wynik musi byc dokladnie 0 1 2 ... 9
    for (int i = 0; i < 10; ++i) {
        assert(sorted_nodes[i] == i);
    }
 
    verify(G, sorted_nodes);
    std::cout << "Test 2 OK" << std::endl;
}
 
// test 3: graf z wieloma zrodlami bez krawedzi miedzy nimi
void test_wiele_zrodel() {
    Graph<int> G;
    // wierzcholki 0..4 jako zrodla, wszystkie ida do 5
    for (int i = 0; i < 5; ++i) {
        G.add_edge(i, 5);
    }
    // 5 idzie do 6..9
    for (int i = 6; i < 10; ++i) {
        G.add_edge(5, i);
    }
 
    assert(G.v() == 10);
 
    std::vector<int> sorted_nodes = topsort_dfs<int>(G);
 
    std::cout << "Test 3 - wiele zrodel: ";
    for (int u : sorted_nodes) std::cout << u << " ";
    std::cout << std::endl;
 
    verify(G, sorted_nodes);
    std::cout << "Test 3 OK" << std::endl;
}
 
// test 4: wykrywanie cyklu - powinien rzucic wyjatek
void test_wykrywanie_cyklu() {
    Graph<int> G;
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G.add_edge(2, 0); // cykl: 0->1->2->0
 
    bool zlapano_wyjatek = false;
    try {
        topsort_dfs<int>(G);
    } catch (const std::runtime_error&) {
        zlapano_wyjatek = true;
    }
 
    assert(zlapano_wyjatek);
    std::cout << "Test 4 - wykryto cykl OK" << std::endl;
}
 
int main() {
    test_dag_podstawowy();
    test_lancuch_liniowy();
    test_wiele_zrodel();
    test_wykrywanie_cyklu();
 
    std::cout << "\nWszystkie testy przeszly." << std::endl;
    return 0;
}