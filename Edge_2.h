#ifndef EDGE_2_H
#define EDGE_2_H

#include "Point_2.h"


template <typename T>
struct Edge_2 {
    typedef Point_2<T> Node;
    Node p0, p1;

    Edge_2(Node const& _p0, Node const& _p1) : p0{_p0}, p1{_p1} {}

    friend ostream& operator<<(ostream& os, const Edge_2& e)
    {
        os << "p0: [" << e.p0 << " ] p1: [" << e.p1 << "]";
        return os;
    }

    bool operator==(const Edge_2& other) const
    {
        return ((other.p0 == p0 && other.p1 == p1) || (other.p0 == p1 && other.p1 == p0));
    }
};

#endif //EDGE_2_H