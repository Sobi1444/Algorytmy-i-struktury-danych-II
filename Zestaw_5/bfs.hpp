#ifndef BFS_HPP
#define BFS_HPP
 
#include <vector>
#include <queue>
#include <unordered_map>
 
template<typename T, typename G>
class BFS {
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::vector<T> preorder;
    std::vector<T> postorder;
 
    BFS(G& g) : graph(g) {
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
            visited[*n_it] = false;
        }
    }
 
    ~BFS() = default;
 
    void run(T u = T()) {
        if (u != T()) {
            visit(u);
        } else {
            for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
                if (!visited[*n_it])
                    visit(*n_it);
            }
        }
    }
 
    void visit(T s) {
        visited[s] = true;
        preorder.push_back(s);
 
        std::queue<T> q;
        q.push(s);
 
        while (!q.empty()) {
            T u = q.front();
            q.pop();
 
            for (auto e_it = graph.edge_begin(u); e_it != graph.edge_end(u); ++e_it) {
                T v = *e_it;
                if (!visited[v]) {
                    visited[v] = true;
                    preorder.push_back(v);
                    q.push(v);
                }
            }
 
            postorder.push_back(u);
        }
    }
};
 
#endif