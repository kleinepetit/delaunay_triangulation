#pragma once

#include"Condition.h"

template<typename T>
void readConditionsFromFile(const string& filename,Condition<T>& cons) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        // return vector<Point_2<T>>();
    }

    int numConditions;
    file >> numConditions;

    for (int i = 0; i < numConditions; ++i) {
        T x1, y1, x2, y2;
        file >> x1 >> y1 >> x2 >> y2;
        Point_2<T> p00, p01;
        p00.x = x1;
        p00.y = y1;
        p01.x = x2;
        p01.y = y2;
        cons.edges.emplace_back(p00,p01);
    }

    file.close();
}