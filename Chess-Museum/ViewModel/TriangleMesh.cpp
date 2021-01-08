#include "TriangleMesh.h"
#include "../View//View.h"
#include <fstream>
#include <string>
#include <vector>

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c)
{
    v[0] = a;
    v[1] = b;
    v[2] = c;
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c)
{
    vn[0] = a;
    vn[1] = b;
    vn[2] = c;
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c)
{
    vt[0] = a;
    vt[1] = b;
    vt[2] = c;
}

void Triangle::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    if (vn[0].Length() || vn[1].Length() || vn[2].Length())
    {
        for (int i = 0; i < 3; i++)
        {
            glNormal3f(vn[i].x(), vn[i].y(), vn[i].z());
            glVertex3f(v[i].x(), v[i].y(), v[i].z());
        }
    }
    else
    {
        Vec3f normal;
        Vec3f::Cross3(normal, v[0] - v[1], v[1] - v[2]);
        glNormal3f(normal.x(), normal.y(), normal.z());
        for (int i = 0; i < 3; i++)
        {
            glVertex3f(v[i].x(), v[i].y(), v[i].z());
        }
    }
    glEnd();
    glPopMatrix();
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

TriangleMesh::TriangleMesh(std::string name, const std::vector<Triangle> &tris)
{
    objName = name;
    triangles = tris;
}

std::string TriangleMesh::getObjName() const
{
    return objName;
}

int TriangleMesh::getListNum() const
{
    return listNum;
}

const std::vector<Triangle> &TriangleMesh::getTriangles() const
{
    return triangles;
}

void TriangleMesh::setListNum(int n)
{
    listNum = n;
}

void TriangleMesh::add(Triangle &t)
{
    triangles.emplace_back(t);
}

