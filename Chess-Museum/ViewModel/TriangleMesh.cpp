#include "TriangleMesh.h"
#include <fstream>
#include <string>
#include <vector>

TriangleMesh::TriangleMesh(const std::vector<Triangle> &tris)
{
    triangles = tris;
}

const std::vector<Triangle> &TriangleMesh::getTriangles() const
{
    return triangles;
}

void TriangleMesh::add(Triangle &t)
{
    triangles.emplace_back(t);
}

void TriangleMesh::draw() const
{
    for (std::vector<Triangle>::const_iterator iter = triangles.begin(); iter != triangles.end(); iter++)
    {
        iter->draw();
    }
}
