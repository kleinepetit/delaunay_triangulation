#ifndef MESH_2_H
#define MESH_2_H

#include "Triangle_2.h"

template <typename T>
struct Mesh_2 {
  vector<Triangle_2<T>> triangles;
  vector<Edge_2<T>> edges;
};

#endif //MESH_2_H