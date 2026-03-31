#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T>
class Iterator {
public:
    Iterator() = default;
    ~Iterator() = default;
    virtual T operator*() const = 0;
};

#endif