#ifndef MESH_3_H
#define MESH_3_H

#include "Tetrahedron_3.h"

template <typename T>
struct Mesh_3 {
	vector<Tetrahedron_3<T>> triangles;
	vector<Triangle_3<T>> edges;
};

#endif //MESH_3_H