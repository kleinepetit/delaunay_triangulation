#ifndef Triangle_3_H
#define Triangle_3_H

#include "Point_3.h"

template <typename T>
struct Triangle_3 {
    typedef Point_3<T> Node;
    Node p0, p1, p2;

    Triangle_3(Node const& _p0, Node const& _p1, Node const& _p2) : p0{_p0}, p1{_p1}, p2{ _p2 } {}

    friend ostream& operator<<(ostream& os, const Triangle_3& e)
    {
        os << "p0: [" << e.p0 << " ] p1: [" << e.p1 << "] p2: [" << e.p2 << "]";
        return os;
    }

    bool operator==(const Triangle_3& other) const
    {
        return ((other.p0 == p0 && other.p1 == p1 && other.p2 == p2) || (other.p0 == p1 && other.p1 == p0 && other.p2 == p2) 
             || (other.p0 == p0 && other.p1 == p2 && other.p2 == p1) || (other.p0 == p2 && other.p1 == p0 && other.p2 == p1)
             || (other.p0 == p1 && other.p1 == p2 && other.p2 == p0) || (other.p0 == p2 && other.p1 == p1 && other.p2 == p0));
    }
};

#endif //Triangle_3_H