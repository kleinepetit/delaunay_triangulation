#ifndef TRIANGULATE_3_H
#define TRIANGULATE_3_H

#include "Mesh_3.h"

template <typename T, typename = enable_if_t<is_floating_point<T>::value>>
Mesh_3<T> Triangulate_3(const vector<Point_3<T>>& points)
{
    typedef Point_3<T> Node;
    if (points.size() < 4) {
        return Mesh_3<T>{};
    }
    auto xmin = points[0].x;
    auto xmax = xmin;
    auto ymin = points[0].y;
    auto ymax = ymin;
    auto zmin = points[0].z;
    auto zmax = zmin;
    for (auto const& pt : points) {
        xmin = min(xmin, pt.x);
        xmax = max(xmax, pt.x);
        ymin = min(ymin, pt.y);
        ymax = max(ymax, pt.y);
        zmin = min(zmin, pt.z);
        zmax = max(zmax, pt.z);
    }

    const auto dx = xmax - xmin;
    const auto dy = ymax - ymin;
    const auto dz = zmax - zmin;
    const auto dmax = (dx > dy ? dx : dy) > dz ? (dx > dy ? dx : dy) : dz;
    const auto midx = (xmin + xmax) / static_cast<T>(2.);
    const auto midy = (ymin + ymax) / static_cast<T>(2.);
    const auto midz = (zmin + zmax) / static_cast<T>(2.);

    /* Init Delaunay triangulation. */
    auto d = Mesh_3<T>{};

    const auto p0 = Node{ midx - 20 * dmax, midy - dmax, midz - dmax};
    const auto p1 = Node{ midx, midy + 20 * dmax ,midz - dmax };
    const auto p2 = Node{ midx + 20 * dmax, midy - dmax ,midz - dmax};
    const auto p3 = Node{ midx , midy , midz + 20 * dmax };
    d.triangles.emplace_back(Tetrahedron_3<T>{p0, p1, p2, p3});

    for (auto const& pt : points) {
        vector<Triangle_3<T>> edges;
        vector<Tetrahedron_3<T>> tmps;
        for (auto const& tri : d.triangles) {
            /* Check if the point is inside the triangle circumcircle. */
            const auto dist = (tri.sphere.x - pt.x) * (tri.sphere.x - pt.x) +
                              (tri.sphere.y - pt.y) * (tri.sphere.y - pt.y) +
                              (tri.sphere.z - pt.z) * (tri.sphere.z - pt.z);
            if ((dist - tri.sphere.radius) <= eps) {
                edges.push_back(tri.e0);
                edges.push_back(tri.e1);
                edges.push_back(tri.e2);
                edges.push_back(tri.e3);
            }
            else {
                tmps.push_back(tri);
            }
        }

        /* Delete duplicate edges. */
        vector<bool> remove(edges.size(), false);
        for (auto it1 = edges.begin(); it1 != edges.end(); ++it1) {
            for (auto it2 = edges.begin(); it2 != edges.end(); ++it2) {
                if (it1 == it2) {
                    continue;
                }
                if (*it1 == *it2) {
                    remove[distance(edges.begin(), it1)] = true;
                    remove[distance(edges.begin(), it2)] = true;
                }
            }
        }

        edges.erase(
            remove_if(edges.begin(), edges.end(),
                [&](auto const& e) { return remove[&e - &edges[0]]; }),
            edges.end());

        /* Update triangulation. */
        for (auto const& e : edges) {
            tmps.push_back({ e.p0, e.p1, e.p2, {pt.x, pt.y, pt.z} });
        }
        d.triangles = tmps;
    }
    /* Remove original super triangle. */
    d.triangles.erase(
        remove_if(d.triangles.begin(), d.triangles.end(),
            [&](auto const& tri) {
                return ((tri.p0 == p0 || tri.p1 == p0 || tri.p2 == p0 || tri.p3 == p0) ||
                        (tri.p0 == p1 || tri.p1 == p1 || tri.p2 == p1 || tri.p3 == p1) ||
                        (tri.p0 == p2 || tri.p1 == p2 || tri.p2 == p2 || tri.p3 == p2) ||
                        (tri.p0 == p3 || tri.p1 == p3 || tri.p2 == p3 || tri.p3 == p3));
            }),
        d.triangles.end());

    /* Add edges. */
    for (auto const& tri : d.triangles) {
        d.edges.push_back(tri.e0);
        d.edges.push_back(tri.e1);
        d.edges.push_back(tri.e2);
        d.edges.push_back(tri.e3);
    }
    return d;
}


#endif //TRIANGULATE_2_H