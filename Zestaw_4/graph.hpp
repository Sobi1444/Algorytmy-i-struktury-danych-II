#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "edge.hpp"
#include "basegraph.hpp"
#include "iterator.hpp"

class Graph : public BaseGraph<int> {
    bool skierowany;
    std::vector<std::vector<int>> lista_sasiedztwa;

public:
    class NodeIterator : public Iterator<int> {
        const Graph *graf;
        int aktualny;
    public:
        NodeIterator(const Graph *g, int u) : graf(g), aktualny(u) {}
        int operator*() const override { return aktualny; }
        NodeIterator& operator++() { ++aktualny; return *this; }
        bool operator!=(const NodeIterator& o) const { return aktualny != o.aktualny; }
    };

    class EdgeIterator : public Iterator<Edge<int>> {
        const Graph *graf;
        int u, w;
        void next() {
            while (u < graf->v()) {
                if (w < (int)graf->lista_sasiedztwa[u].size()) return;
                ++u;
                w = 0;
            }
        }
    public:
        EdgeIterator(const Graph *g, int u = 0, int w = 0) : graf(g), u(u), w(w) {
            if (u < graf->v()) next();
        }
        Edge<int> operator*() const override { return Edge<int>(u, graf->lista_sasiedztwa[u][w]); }
        EdgeIterator& operator++() { ++w; next(); return *this; }
        bool operator!=(const EdgeIterator& o) const { return u != o.u || w != o.w; }
    };

    class AdjacentIterator : public Iterator<int> {
        const Graph *graf;
        int wierzcholek, indeks;
    public:
        AdjacentIterator(const Graph *g, int u, int i = 0) : graf(g), wierzcholek(u), indeks(i) {}
        int operator*() const override { return graf->lista_sasiedztwa[wierzcholek][indeks]; }
        AdjacentIterator& operator++() { ++indeks; return *this; }
        bool operator!=(const AdjacentIterator& o) const { return indeks != o.indeks; }
    };

    NodeIterator node_begin() const { return NodeIterator(this, 0); }
    NodeIterator node_end() const { return NodeIterator(this, v()); }
    EdgeIterator edge_begin() const { return EdgeIterator(this); }
    EdgeIterator edge_end() const { return EdgeIterator(this, v(), 0); }
    AdjacentIterator adj_begin(int u) const { return AdjacentIterator(this, u, 0); }
    AdjacentIterator adj_end(int u) const { return AdjacentIterator(this, u, lista_sasiedztwa[u].size()); }

    Graph(int n, bool skierowany = false) : skierowany(skierowany) {
        lista_sasiedztwa = std::vector<std::vector<int>>(n);
    }
    ~Graph() { clear(); }

    bool is_directed() const override { return skierowany; }
    int v() const override { return lista_sasiedztwa.size(); }
    int e() const override {
        int licznik = 0;
        for (int u = 0; u < v(); u++) licznik += lista_sasiedztwa[u].size();
        return skierowany ? licznik : licznik / 2;
    }
    int degree(int u) override { assert(has_node(u)); return lista_sasiedztwa[u].size(); }
    int indegree(int u) override {
        assert(has_node(u));
        int licznik = 0;
        for (int w = 0; w < v(); w++) {
            for (int s : lista_sasiedztwa[w]) {
                if (s == u) licznik++;
            }
        }
        return licznik;
    }
    int outdegree(int u) override { assert(has_node(u)); return lista_sasiedztwa[u].size(); }
    void add_node(int u) override { assert(0 <= u && u < v()); }
    void del_node(int u) override {
        assert(has_node(u));
        lista_sasiedztwa[u].clear();
        for (int w = 0; w < v(); w++) {
            auto& l = lista_sasiedztwa[w];
            l.erase(std::remove(l.begin(), l.end(), u), l.end());
        }
    }
    bool has_node(int u) const override { return 0 <= u && u < v(); }
    void add_edge(int u, int w, float weight = 1.0) override {
        assert(has_node(u) && has_node(w) && !has_edge(u, w));
        lista_sasiedztwa[u].push_back(w);
        if (!skierowany) lista_sasiedztwa[w].push_back(u);
    }
    void add_edge(Edge<int> kr) override { add_edge(kr.source, kr.target); }
    void del_edge(int u, int w) override {
        assert(has_node(u) && has_node(w));
        auto& l = lista_sasiedztwa[u];
        l.erase(std::remove(l.begin(), l.end(), w), l.end());
        if (!skierowany) {
            auto& l2 = lista_sasiedztwa[w];
            l2.erase(std::remove(l2.begin(), l2.end(), u), l2.end());
        }
    }
    void del_edge(Edge<int> kr) override { del_edge(kr.source, kr.target); }
    bool has_edge(int u, int w) const override {
        assert(has_node(u) && has_node(w));
        for (int s : lista_sasiedztwa[u]) if (s == w) return true;
        return false;
    }
    bool has_edge(Edge<int> kr) const override { return has_edge(kr.source, kr.target); }
    float weight(int u, int w) const override { return has_edge(u, w) ? 1.0 : 0.0; }
    float weight(Edge<int> kr) const override { return weight(kr.source, kr.target); }
    void clear() override {
        for (int u = 0; u < v(); u++) lista_sasiedztwa[u].clear();
    }
    void display() const override {
        std::cout << (skierowany ? "skierowany" : "nieskierowany") << "\n";
        for (int u = 0; u < v(); u++) {
            std::cout << u << ": ";
            for (int w : lista_sasiedztwa[u]) std::cout << w << " ";
            std::cout << "\n";
        }
    }
};

#endif