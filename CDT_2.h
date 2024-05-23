#pragma once

#include"Mesh_2.h"
#include"Condition.h"

template <typename T>
bool onSegment(const Point_2<T>& p, const Point_2<T>& q, const Point_2<T>& r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) {
        return true;
    }
    return false;
}

template <typename T>
bool lineIntersect(Edge_2<T>& e1, Edge_2<T>& e2, Point_2<T>& intersection) {
    T a1 = e1.p1.y - e1.p0.y;
    T b1 = e1.p1.x - e1.p0.x;
    T c1 = e1.p0.y - a1/b1 * e1.p0.x;

    T a2 = e2.p1.y - e2.p0.y;
    T b2 = e2.p1.x - e2.p0.x;
    T c2 = e2.p0.y - a2/b2 * e2.p0.x;

    T determinant = a1/b1 - a2/b2;

    if (std::abs(determinant) < eps) {
        // Lines are parallel
        return false;
    }
    else {
        intersection.x = (c2 - c1) / (a1 / b1 - a2 / b2);
        intersection.y = a1 / b1 * intersection.x + c1;

        if (onSegment(e1.p0, intersection, e1.p1) && onSegment(e2.p0, intersection, e2.p1)) {
            return true;
        }
        return false;
    }
}

template<typename T>
void PointInsert(bool crossed,const Point_2<T> & tempPoint,Mesh_2<T>& mesh ) {
    if (crossed)
    {
        auto d = mesh;
        vector<Edge_2<T>> edges;
        vector<Triangle_2<T>> tmps;
        for (auto const& tri : d.triangles) {
            /* Check if the point is inside the triangle circumcircle. */
            const auto dist = (tri.circle.x - tempPoint.x) * (tri.circle.x - tempPoint.x) +
                (tri.circle.y - tempPoint.y) * (tri.circle.y - tempPoint.y);
            if ((dist - tri.circle.radius) <= eps) {
                edges.push_back(tri.e0);
                edges.push_back(tri.e1);
                edges.push_back(tri.e2);
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
       
        edges.erase(remove_if(edges.begin(), edges.end(), [&](auto const& e) { return remove[&e - &edges[0]]; }), edges.end());
       
        /* Update triangulation. */
        for (auto const& e : edges) {
            tmps.push_back({ e.p0, e.p1, {tempPoint.x, tempPoint.y} });
        }
        d.triangles = tmps;
        d.edges = vector<Edge_2<T>> {};
    for (auto const& tri : d.triangles) {
        d.edges.push_back(tri.e0);
        d.edges.push_back(tri.e1);
        d.edges.push_back(tri.e2);
    }
    mesh = d;
    }
}

template <typename T, typename = enable_if_t<is_floating_point<T>::value>>
Mesh_2<T> CDT_2(Mesh_2<T>& mesh,Condition<T>& conditions)
{
    for (auto& con2 : conditions.edges) {
        for (auto& ed2 : mesh.edges) {
            Point_2<T> tempPoint;
            PointInsert(lineIntersect(con2, ed2, tempPoint), tempPoint, mesh);
        }
        PointInsert(1, con2.p0, mesh);
        PointInsert(1, con2.p1, mesh);
    }
    return mesh;
}
