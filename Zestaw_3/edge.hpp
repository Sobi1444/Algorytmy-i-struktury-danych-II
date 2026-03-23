#ifndef EDGE_HPP
#define EDGE_HPP
 
#include <iostream>
 
template <typename T>
class Edge {
public:
    T source;
    T target;
    float waga;
 
    Edge(T s, T t, float w = 1.0) : source(s), target(t), waga(w) {}
    ~Edge() {}
    Edge(const Edge& e) : source(e.source), target(e.target), waga(e.waga) {}
 
    Edge operator~() const { return Edge(target, source, waga); }
 
    Edge& operator=(const Edge& other) {
        source = other.source;
        target = other.target;
        waga = other.waga;
        return *this;
    }
 
    bool operator==(const Edge& e) { return source == e.source && target == e.target && waga == e.waga; }
    bool operator!=(const Edge& e) { return !(*this == e); }
 
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        os << "(" << e.source << "->" << e.target << ")";
        return os;
    }
};
 
#endif