#include"Point_2.h"
#include"Point_3.h"

template<typename T>
void readPointsFromFile(const string& filename, vector<Point_2<T>> &points) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
       // return vector<Point_2<T>>();
    }

    int numPoints;
    file >> numPoints;

    for (int i = 0; i < numPoints; ++i) {
        T x, y;
        file >> x >> y;
        points.emplace_back(x, y);
    }

    file.close();
}

template<typename T>
void readPointsFromFile(const string& filename, vector<Point_3<T>>& points) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        // return vector<Point_2<T>>();
    }

    int numPoints;
    file >> numPoints;

    for (int i = 0; i < numPoints; ++i) {
        T x, y, z;
        file >> x >> y >> z;
        points.emplace_back(x, y, z);
    }

    file.close();
}