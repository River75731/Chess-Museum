#include "TriangleMesh.h"
#include "../View//View.h"
#include <fstream>
#include <string>
#include <vector>

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c)
{
    v.emplace_back(a);
    v.emplace_back(b);
    v.emplace_back(c);
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c)
{
    vn.emplace_back(a);
    vn.emplace_back(b);
    vn.emplace_back(c);
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c)
{
    vt.emplace_back(a);
    vt.emplace_back(b);
    vt.emplace_back(c);
}

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    v.emplace_back(a);
    v.emplace_back(b);
    v.emplace_back(c);
    v.emplace_back(d);
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    vn.emplace_back(a);
    vn.emplace_back(b);
    vn.emplace_back(c);
    vn.emplace_back(d);
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    vt.emplace_back(a);
    vt.emplace_back(b);
    vt.emplace_back(c);
    vt.emplace_back(d);
}

void Triangle::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    for (int i = 0; i < v.size(); i++)
    {
        glNormal3f(vn[i].x(), vn[i].y(), vn[i].z());
        glTexCoord2f(vt[i].x(), vt[i].y());
        glVertex3f(v[i].x(), v[i].y(), v[i].z());
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
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
