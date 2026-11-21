#pragma once
#include "Vector3d.h"  
#include "vector"
#include <iostream>
#include <fstream>
#include <sstream> 
#include "pixel.h"

struct Triangle
{
    int v0Index, v1Index, v2Index;
    Triangle(int p_v0Index, int p_v1Index, int p_v2Index)
        : v0Index(p_v0Index), v1Index(p_v1Index), v2Index(p_v2Index) {}
};

class Mesh
{
    private:
        std::vector<Vector3d<double>> mesh_vertices;
        std::vector<Triangle> mesh_triangles;
        std::vector<Pixel> mesh_triangles_colors;
    public:
        const std::vector<Vector3d<double>>& getVertices();
        const std::vector<Triangle>& getTriangles() const;
        const std::vector<Pixel>& getColors(); 
        void makeDebugCube();
        bool makeDebugChessGrid(int width, int tileWidth, Pixel CheckerBoardColorDark, Pixel CheckerBoardColorLight);
        bool loadObjFile(std::string ObjFilePath);
};

inline const std::vector<Vector3d<double>>& Mesh::getVertices() 
{
    return this->mesh_vertices;
}

inline const std::vector<Triangle>& Mesh::getTriangles() const
{
    return this->mesh_triangles;    
}

inline const std::vector<Pixel>& Mesh::getColors()  
{
    return this->mesh_triangles_colors;    
}

inline void
Mesh::makeDebugCube(void)
{
    mesh_vertices = {
        Vector3d<double>(-1, -1, -1), Vector3d<double>(+1, -1, -1),
        Vector3d<double>(+1, -1, +1), Vector3d<double>(-1, -1, +1),
        Vector3d<double>(-1, +1, -1), Vector3d<double>(+1, +1, -1),
        Vector3d<double>(+1, +1, +1), Vector3d<double>(-1, +1, +1)
    };

    mesh_triangles = {
        Triangle(0, 1, 2), Triangle(7, 6, 5), Triangle(0, 4, 5), Triangle(3, 2, 6),
        Triangle(0, 3, 7), Triangle(1, 5, 6), Triangle(0, 2, 3), Triangle(7, 5, 4),
        Triangle(0, 5, 1), Triangle(3, 6, 7), Triangle(0, 7, 4), Triangle(1, 6, 2)
    };

}