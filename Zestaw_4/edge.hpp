#ifndef EDGE_HPP
#define EDGE_HPP

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

#endif