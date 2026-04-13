#ifndef GRAPH_HPP
#define GRAPH_HPP
 
#include <vector>
#include <unordered_map>
 
template<typename T = int>
class Graph {
    std::unordered_map<T, std::vector<T>> adj;
    std::vector<T> nodes;
public:
    void add_node(T u) {
        if (adj.find(u) == adj.end()) {
            adj[u] = {};
            nodes.push_back(u);
        }
    }
 
    void add_edge(T u, T v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    typename std::vector<T>::iterator node_begin() {
        return nodes.begin();
    }
 
    typename std::vector<T>::iterator node_end() {
        return nodes.end();
    }
 
    typename std::vector<T>::iterator edge_begin(T u) {
        return adj[u].begin();
    }
 
    typename std::vector<T>::iterator edge_end(T u) {
        return adj[u].end();
    }
 
    int node_count() {
        return (int)nodes.size();
    }
};
 
#endif