#ifndef PRINTMESHTOFILE_H
#define PRINTMESHTOFILE_H

#include"Mesh_2.h"
#include"Mesh_3.h"

template <typename T>
void printMeshToFile(const Mesh_2<T>& mesh, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    outfile << mesh.triangles.size() << "\t" << 0 << std::endl;
    for (const auto& triangle : mesh.triangles) {
        outfile << triangle.p0.x << "\t" << triangle.p0.y << std::endl;
        outfile << triangle.p1.x << "\t" << triangle.p1.y << std::endl;
        outfile << triangle.p2.x << "\t" << triangle.p2.y << std::endl;
    }

    outfile.close();
}

template <typename T>
void printMeshToFile(const Mesh_3<T>& mesh, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    outfile << mesh.triangles.size() << "\t" << 0 << "\t" << 0 <<std::endl;
    for (const auto& triangle : mesh.triangles) {
        outfile << triangle.p0.x << "\t" << triangle.p0.y << "\t" << triangle.p0.z << std::endl;
        outfile << triangle.p1.x << "\t" << triangle.p1.y << "\t" << triangle.p1.z << std::endl;
        outfile << triangle.p2.x << "\t" << triangle.p2.y << "\t" << triangle.p2.z << std::endl;
        outfile << triangle.p3.x << "\t" << triangle.p3.y << "\t" << triangle.p3.z << std::endl;
    }

    outfile.close();
}

#endif //PRINTMESHTOFILE_H