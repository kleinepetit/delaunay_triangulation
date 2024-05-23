#include"Triangulate_2.h"
#include"Tetrahedron_3.h"
#include"Triangle_2.h"
#include"Triangulate_3.h"
#include<fstream>
#include"ReadPointsFromFile.h"
#include<chrono>
#include"PrintMeshToFile.h"
#include"Condition.h"
#include"CDT_2.h"
#include"ReadConditionFromFile.h"

template <typename T>
void printMesh(const Mesh_2<T>& mesh) {
    cout << "Number of triangles: " << mesh.triangles.size() << endl;
    for (const auto& triangle : mesh.triangles) {
        cout << "Triangle: " << endl;
        cout << "  Vertex 1: (" << triangle.p0.x << ", " << triangle.p0.y << ")" << endl;
        cout << "  Vertex 2: (" << triangle.p1.x << ", " << triangle.p1.y << ")" << endl;
        cout << "  Vertex 3: (" << triangle.p2.x << ", " << triangle.p2.y << ")" << endl;
    }
}

int main(){
    Condition<double> conditions = {};
    auto start_time = std::chrono::high_resolution_clock::now();
    vector<Point_2<double>> points;
    readConditionsFromFile<double>("conditions.test", conditions);
	readPointsFromFile<double>("origin.points",points);
    //auto mesh = CDT_2(points, conditions);
    auto mesh = Triangulate_2(points);
    auto Conditionmesh = CDT_2(mesh, conditions);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    printMeshToFile(Conditionmesh, "output_2.txt");
    // printMesh(mesh);
     std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

     Point_2<double> p00, p01;
     p00.x = 0.14;
     p00.y = 0.12;
     p01.x = 0.131429;
     p01.y = 0.150909;
     auto testline = Edge_2<double> (p00, p01);

     p00.x = 0.0;
     p00.y = 0.0;
     p01.x = 1.0;
     p01.y = 1.0;
     auto testline2 = Edge_2<double>(p00, p01);

     Point_2<double> tempt;
     lineIntersect<double>(testline,testline2,tempt);
     cout << tempt;
}