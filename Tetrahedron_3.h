#ifndef TETRAHEDRON_3_H
#define TETRAHEDRON_3_H

#include "Triangle_3.h"
#include "Sphere_3.h"

template <typename T>
struct Tetrahedron_3 {
    typedef Point_3<T> Node;
    Node p0, p1, p2, p3;
    Triangle_3<T> e0, e1, e2, e3;
    Sphere_3<T> sphere;

    Tetrahedron_3(const Node& _p0, const Node& _p1, const Node& _p2, const Node& _p3)
        : p0{ _p0 },
        p1{ _p1 },
        p2{ _p2 },
        p3{ _p3 },
        e0{ _p0, _p1, _p2 },
        e1{ _p1, _p2, _p3 },
        e2{ _p0, _p2, _p3 },
        e3{ _p0, _p3, _p1 },
        sphere{}
    {
        const auto ax = p1.x - p0.x;
        const auto ay = p1.y - p0.y;
        const auto az = p1.z - p0.z;
        const auto bx = p2.x - p0.x;
        const auto by = p2.y - p0.y;
        const auto bz = p2.z - p0.z;
        const auto cx = p3.x - p0.x;
        const auto cy = p3.y - p0.y;
        const auto cz = p3.z - p0.z;

        const auto m = p1.x * p1.x - p0.x * p0.x + p1.y * p1.y - p0.y * p0.y + p1.z * p1.z - p0.z * p0.z;
        const auto u = p2.x * p2.x - p0.x * p0.x + p2.y * p2.y - p0.y * p0.y + p2.z * p2.z - p0.z * p0.z;
        const auto v = p3.x * p3.x - p0.x * p0.x + p3.y * p3.y - p0.y * p0.y + p3.z * p3.z - p0.z * p0.z;
        const auto vol = ax * (by * cz - bz * cy) - ay * (bx * cz - bz * cx) + az * (bx * cy - by * cx);

        sphere.x = ((by * cz - bz * cy) * m - (ay * cz - az * cy) * u + (ay * bz - az * by) * v) / (2 * vol);
        sphere.y = ((bz * cx - bx * cz) * m + (ax * cz - az * cx) * u - (ax * bz - az * bx) * v) / (2 * vol);
        sphere.z = ((bx * cy - by * cx) * m - (ax * cy - ay * cx) * u + (ax * by - ay * bx) * v) / (2 * vol);

        const auto dx = p0.x - sphere.x;
        const auto dy = p0.y - sphere.y;
        const auto dz = p0.z - sphere.z;
        sphere.radius = dx * dx + dy * dy + dz * dz;
    }
};


#endif //TETRAHEDRON_3_H