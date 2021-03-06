
#ifndef POINT_H
#define POINT_H

#include <iostream>

template <typename T>
struct Point {
    T x;
    T y;

    Point() : x(0), y(0) {};
    Point(T x, T y) : x(x), y(y) {};
    Point(const Point<T> &other) : x(other.x), y(other.y) {};
    ~Point() {};

    std::tuple<T,T> toTupple() const {
        return std::make_tuple(x,y);
    }

};

template <typename T>
std::ostream & operator<< (std::ostream &os, const Point<T> &point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}


template <typename T>
Point<T> operator*(const Point<T> &pt, T alpha) {
    return Point<T>(pt.x*alpha, pt.y*alpha);
}


#endif /* end of include guard: POINT_H */
