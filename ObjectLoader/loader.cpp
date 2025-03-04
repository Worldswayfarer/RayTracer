#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../Data/triangle3.h"
#include <tuple>

void transform_triangles(std::vector<triangle3>* triangles) {
    
}

bool simple_loadOBJ(const std::string& filename, std::vector<triangle3>* triangles) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return false;
    }

    std::vector<vector3> vertices;
    std::string line;

    RGB_Material material = RGB_Material(color3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),
        1, 0.5, 0.5, 1);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { // Read vertex
            vector3 v;
            iss >> v.e[0] >> v.e[1] >> v.e[2];
            v.e[1] -= 0.1; //move bunny down
            v.e[2] -= 2; // move bunny away
            vertices.push_back(v);
        }
        else if (prefix == "f") { // Read face
            int v0, v1, v2;
            iss >> v0 >> v1 >> v2;

            // Convert OBJ 1-based index to 0-based index
            triangle3 neewTri = triangle3({ vertices[v0 - 1], vertices[v1 - 1], vertices[v2 - 1] });
            neewTri.setMaterial(material);
            triangles->push_back(neewTri);
        }
    }
    transform_triangles(triangles);
    return true;
}
