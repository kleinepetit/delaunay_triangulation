#ifndef POINT_3_H
#define POINT_3_H

#include<algorithm>
#include<iostream>
#include<vector>
#include "Accuracy.h"

using namespace std;

template <typename T>
struct Point_3 {
    T x, y, z;

    Point_3() : x{ 0 }, y{ 0 } ,z { 0 } {}
    Point_3(T _x, T _y, T _z) : x{ _x }, y{ _y } ,z { _z } {}

    template <typename U>
    Point_3(U _x, U _y, U _z) : x{ static_cast<T>(_x) }, y{ static_cast<T>(_y) }, z{ static_cast<T>(_z) }
    {}

    friend ostream & operator<<(ostream & os, const Point_3<T>&p)
    {
        os << "x=" << p.x << "  y=" << p.y << "  z=" << p.z;
        return os;
    }

    bool operator==(const Point_3<T>&other) const
    {
        return (other.x == x && other.y == y && other.z == z);
    }

    bool operator!=(const Point_3<T>&other) const
    {
        return !operator==(other);
    }
    };

#endif //POINT_3_H