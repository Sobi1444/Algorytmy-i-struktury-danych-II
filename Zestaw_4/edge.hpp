#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

template <typename T>
class Edge {
public:
    T source;
    T target;
    float weight;
    
    Edge(T s, T t, float w = 1.0) : source(s), target(t), weight(w) {}
    
    bool operator==(const Edge& other) const {
        return source == other.source && target == other.target;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Edge<T>& edge) {
    os << "(" << edge.source << "," << edge.target << ")";
    return os;
}

#endif