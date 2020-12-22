#include "TriangleMesh.h"
#include "../View/Draw.h"
#include <fstream>
#include <string>
#include <vector>

TriangleMesh::TriangleMesh(std::string name)
{
    // TODO: init ViewObject
}

TriangleMesh::TriangleMesh(std::string name, const std::vector<Triangle> &tris)
{
    // TODO: init ViewObject
    triangles = tris;
}

void TriangleMesh::add(Triangle t)
{
    triangles.emplace_back(t);
}

void TriangleMesh::draw()
{
    for (std::vector<Triangle>::iterator iter = triangles.begin(); iter != triangles.end(); iter++)
    {
        ::draw(*iter);
    }
}