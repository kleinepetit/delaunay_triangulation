#ifndef TRIANGLE_2_H
#define TRIANGLE_2_H

#include "Edge_2.h"
#include "Circle_2.h"

template <typename T>
struct Triangle_2 {
  typedef Point_2<T> Node;
  Node p0, p1, p2;
  Edge_2<T> e0, e1, e2;
  Circle_2<T> circle;

  Triangle_2(const Node& _p0, const Node& _p1, const Node& _p2)
      : p0{_p0},
        p1{_p1},
        p2{_p2},
        e0{_p0, _p1},
        e1{_p1, _p2},
        e2{_p0, _p2},
        circle{}
  {
    const auto ax = p1.x - p0.x;
    const auto ay = p1.y - p0.y;
    const auto bx = p2.x - p0.x;
    const auto by = p2.y - p0.y;

    const auto m = p1.x * p1.x - p0.x * p0.x + p1.y * p1.y - p0.y * p0.y;
    const auto u = p2.x * p2.x - p0.x * p0.x + p2.y * p2.y - p0.y * p0.y;
    const auto s = 1. / (2. * (ax * by - ay * bx));

    circle.x = ((p2.y - p0.y) * m + (p0.y - p1.y) * u) * s;
    circle.y = ((p0.x - p2.x) * m + (p1.x - p0.x) * u) * s;

    const auto dx = p0.x - circle.x;
    const auto dy = p0.y - circle.y;
    circle.radius = dx * dx + dy * dy;
  }
};


#endif //TRIANGLE_2_H