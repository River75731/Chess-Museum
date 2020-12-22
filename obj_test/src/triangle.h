#pragma once

#include "vectors.h"
#include <GL/glut.h>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

class Triangle
{
public:
    Triangle() {}

    void setV(Vec3f a, Vec3f b, Vec3f c)
    {
        v[0] = a;
        v[1] = b;
        v[2] = c;
    }
    void setN(Vec3f a, Vec3f b, Vec3f c)
    {
        vn[0] = a;
        vn[1] = b;
        vn[2] = c;
    }
    void setT(Vec3f a, Vec3f b, Vec3f c)
    {
        vt[0] = a;
        vt[1] = b;
        vt[2] = c;
    }
    const std::array<Vec3f, 3> &getV() const { return v; }
    const std::array<Vec3f, 3> &getN() const { return vn; }
    const std::array<Vec3f, 3> &getT() const { return vt; }

private:
    std::array<Vec3f, 3> v;
    std::array<Vec3f, 3> vn;
    std::array<Vec3f, 3> vt;
};

// -------------------------------------------------
// -------------------------------------------------

class TriangleMesh
{
public:
    TriangleMesh(std::string name);
    TriangleMesh(std::string name, const std::vector<Triangle> &tris);

    void add(Triangle t);
    void draw();

    static std::vector<TriangleMesh> parseFile(std::string filename);

private:
    std::vector<Triangle> triangles;
};