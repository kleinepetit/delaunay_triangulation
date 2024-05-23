#ifndef POINT_2_H
#define POINT_2_H

#include<algorithm>
#include<iostream>
#include<vector>
#include "Accuracy.h"

template <typename T>
struct Point_2 {
    T x, y;

    Point_2() : x{0}, y{0} {}
    Point_2(T _x, T _y) : x{_x}, y{_y} {}

    template <typename U>
    Point_2(U _x, U _y) : x{static_cast<T>(_x)}, y{static_cast<T>(_y)}
    {}   

    friend ostream& operator<<(ostream& os, const Point_2<T>& p)
    {
        os << "x=" << p.x << "  y=" << p.y;
        return os;
    }

    bool operator==(const Point_2<T>& other) const
    {
        return (other.x == x && other.y == y);
    }

    bool operator!=(const Point_2<T>& other) const 
    {
        return !operator==(other); 
    }
};

#endif //POINT_2_H