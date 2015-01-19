
#ifndef INTERVAL_H
#define INTERVAL_H

#include <cassert>

template <typename T>
struct Interval {
    T inf;
    T sup;
    
    Interval(T inf, T sup) : inf(inf), sup(sup) { assert(inf < sup); }
    Interval(const Interval<T> &other) : inf(other.inf), sup(other.sup) {}
    ~Interval() {}
    
    template <typename S>
    explicit Interval(const Interval<S> &other) : inf(static_cast<T>(other.inf)), sup(static_cast<T>(other.sup)) {}

    int upperInteger() const { return ceil(sup); }
    int lowerInteger() const { return floor(inf); }
};

template <typename T>
std::ostream & operator<< (std::ostream &os, const Interval<T> &interval) {
    os << "[" << interval.inf << "," << interval.sup << "]";
    return os;
}

#endif /* end of include guard: INTERVAL_H */