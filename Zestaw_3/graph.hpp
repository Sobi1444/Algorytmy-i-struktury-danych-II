#ifndef GRAPH_HPP
#define GRAPH_HPP
 
#include <vector>
#include <iostream>
#include <cassert>
#include "edge.hpp"
 
class Graph {
    bool skierowany;
    std::vector<std::vector<int>> macierz;
 
public:
    Graph(int n, bool skierowany = false) : skierowany(skierowany) {
        macierz = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    }
 
    ~Graph() { clear(); }
 
    bool is_directed() const { return skierowany; }
 
    int v() const { return macierz.size(); }
 
    int e() const {
        int licznik = 0;
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                licznik += macierz[u][w];
        return skierowany ? licznik : licznik / 2;
    }
 
    int degree(int u) {
        assert(has_node(u));
        int licznik = 0;
        for (int w = 0; w < v(); w++)
            if (macierz[u][w]) licznik++;
        return licznik;
    }
 
    int indegree(int u) {
        assert(has_node(u));
        int licznik = 0;
        for (int w = 0; w < v(); w++)
            if (macierz[w][u]) licznik++;
        return licznik;
    }
 
    int outdegree(int u) {
        assert(has_node(u));
        int licznik = 0;
        for (int w = 0; w < v(); w++)
            if (macierz[u][w]) licznik++;
        return licznik;
    }
 
    void add_node(int u) {
        assert(0 <= u && u < v());
    }
 
    void del_node(int u) {
        assert(has_node(u));
        for (int w = 0; w < v(); w++) {
            macierz[u][w] = 0;
            macierz[w][u] = 0;
        }
    }
 
    bool has_node(int u) const {
        return 0 <= u && u < v();
    }
 
    void add_edge(int u, int w, float weight = 1.0) {
        assert(has_node(u) && has_node(w));
        macierz[u][w] = 1;
        if (!skierowany) macierz[w][u] = 1;
    }
 
    void add_edge(Edge<int> kr) { add_edge(kr.source, kr.target); }
 
    void del_edge(int u, int w) {
        assert(has_node(u) && has_node(w));
        macierz[u][w] = 0;
        if (!skierowany) macierz[w][u] = 0;
    }
 
    void del_edge(Edge<int> kr) { del_edge(kr.source, kr.target); }
 
    bool has_edge(int u, int w) const { return macierz[u][w] == 1; }
    bool has_edge(Edge<int> kr) const { return macierz[kr.source][kr.target] == 1; }
 
    float weight(int u, int w) const { return macierz[u][w]; }
    float weight(Edge<int> kr) const { return macierz[kr.source][kr.target]; }
 
    void clear() {
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                macierz[u][w] = 0;
    }
 
    void display() const {
        std::cout << (skierowany ? "skierowany" : "nieskierowany") << "\n";
        for (int u = 0; u < v(); u++) {
            for (int w = 0; w < v(); w++)
                std::cout << macierz[u][w] << " ";
            std::cout << "\n";
        }
    }
};
 
#endif