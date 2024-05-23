#ifndef TRIANGULATE_2_H
#define TRIANGULATE_2_H

#include "Mesh_2.h"

template <typename T, typename = enable_if_t<is_floating_point<T>::value>>
Mesh_2<T> Triangulate_2(const vector<Point_2<T>>& points)
{
  typedef Point_2<T> Node;
  if (points.size() < 3) {
    return Mesh_2<T>{};
  }
  auto xmin = points[0].x;
  auto xmax = xmin;
  auto ymin = points[0].y;
  auto ymax = ymin;
  for (auto const& pt : points) {
    xmin = min(xmin, pt.x);
    xmax = max(xmax, pt.x);
    ymin = min(ymin, pt.y);
    ymax = max(ymax, pt.y);
  }

  const auto dx = xmax - xmin;
  const auto dy = ymax - ymin;
  const auto dmax = max(dx, dy);
  const auto midx = (xmin + xmax) / static_cast<T>(2.);
  const auto midy = (ymin + ymax) / static_cast<T>(2.);

  /* Init Delaunay triangulation. */
  auto d = Mesh_2<T>{};

  const auto p0 = Node{midx - 20 * dmax, midy - dmax};
  const auto p1 = Node{midx, midy + 20 * dmax};
  const auto p2 = Node{midx + 20 * dmax, midy - dmax};
  d.triangles.emplace_back(Triangle_2<T>{p0, p1, p2});

  for (auto const& pt : points) {
    vector<Edge_2<T>> edges;
    vector<Triangle_2<T>> tmps;
    for (auto const& tri : d.triangles) {
      /* Check if the point is inside the triangle circumcircle. */
      const auto dist = (tri.circle.x - pt.x) * (tri.circle.x - pt.x) +
                        (tri.circle.y - pt.y) * (tri.circle.y - pt.y);
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
      tmps.push_back({e.p0, e.p1, {pt.x, pt.y}});
    }
    d.triangles = tmps;
  }
  /* Remove original super triangle. */
  d.triangles.erase(
      remove_if(d.triangles.begin(), d.triangles.end(),
                     [&](auto const& tri) {
                       return ((tri.p0 == p0 || tri.p1 == p0 || tri.p2 == p0) ||
                               (tri.p0 == p1 || tri.p1 == p1 || tri.p2 == p1) ||
                               (tri.p0 == p2 || tri.p1 == p2 || tri.p2 == p2));
                     }),
      d.triangles.end());

  /* Add edges. */
  for (auto const& tri : d.triangles) {
    d.edges.push_back(tri.e0);
    d.edges.push_back(tri.e1);
    d.edges.push_back(tri.e2);
  }
  return d;
}


#endif //TRIANGULATE_2_H