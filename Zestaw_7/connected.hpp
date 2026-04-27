#ifndef CONNECTED_HPP
#define CONNECTED_HPP
 
#include <unordered_map>
#include <vector>
#include <stack>
#include <cassert>
 
// prosta klasa grafu
template<typename T>
class Graph {
    std::unordered_map<T, std::vector<T>> adj;
    bool directed;
public:
    Graph(bool directed = false) : directed(directed) {}
 
    bool is_directed() const { return directed; }
 
    void add_node(T u) {
        if (adj.find(u) == adj.end())
            adj[u] = {};
    }
 
    void add_edge(T u, T v) {
        adj[u].push_back(v);
        if (!directed)
            adj[v].push_back(u);
    }
 
    std::vector<T> neighbors(T u) const {
        return adj.at(u);
    }
 
    typename std::unordered_map<T, std::vector<T>>::iterator node_begin() {
        return adj.begin();
    }
 
    typename std::unordered_map<T, std::vector<T>>::iterator node_end() {
        return adj.end();
    }
};

template<typename T, typename G>
class ConnectedComponents {
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::unordered_map<T, int> component;
    int ncc;
 
    ConnectedComponents(G& g) : graph(g), ncc(0) {
        assert(!graph.is_directed());
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
            visited[n_it->first] = false;
        }
    }
 
    ~ConnectedComponents() = default;
 
    void visit(T u) {
        // BFS zamiast DFS
        std::stack<T> s;
        s.push(u);
        visited[u] = true;
        component[u] = ncc;
        while (!s.empty()) {
            T v = s.top();
            s.pop();
            for (T w : graph.neighbors(v)) {
                if (!visited[w]) {
                    visited[w] = true;
                    component[w] = ncc;
                    s.push(w);
                }
            }
        }
    }
 
    void run() {
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
            T u = n_it->first;
            if (!visited[u]) {
                visit(u);
                ncc++;
            }
        }
    }
};
 
#endif
