#include "TriangleMesh.h"
#include "../View/Draw.h"
#include "../View/List.h"
#include <fstream>
#include <string>
#include <vector>

TriangleMesh::TriangleMesh(std::string name) : ViewObject3d(name) {}

TriangleMesh::TriangleMesh(std::string name, const std::vector<Triangle> &tris) : ViewObject3d(name)
{
    triangles = tris;
}

const std::vector<Triangle> &TriangleMesh::getTriangles() const
{
    return triangles;
}

int TriangleMesh::getListNum() const
{
    return listNum;
}

void TriangleMesh::setListNum(int n)
{
    listNum = n;
}

void TriangleMesh::add(Triangle t)
{
    triangles.emplace_back(t);
}

void TriangleMesh::init()
{
    regObject(*this);
}

void TriangleMesh::draw() const
{
    callObject(*this);
}
