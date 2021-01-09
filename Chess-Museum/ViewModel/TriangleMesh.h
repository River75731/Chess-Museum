#pragma once

#include "../Common/vectors.h"
#include <vector>
#include <fstream>
#include <string>
#include <vector>

class Triangle
{
public:
    void setV(Vec3f a, Vec3f b, Vec3f c);
    void setN(Vec3f a, Vec3f b, Vec3f c);
    void setT(Vec3f a, Vec3f b, Vec3f c);
    void setV(Vec3f a, Vec3f b, Vec3f c, Vec3f d);
    void setN(Vec3f a, Vec3f b, Vec3f c, Vec3f d);
    void setT(Vec3f a, Vec3f b, Vec3f c, Vec3f d);
    const std::vector<Vec3f> &getV() const { return v; }
    const std::vector<Vec3f> &getN() const { return vn; }
    const std::vector<Vec3f> &getT() const { return vt; }
    void draw() const;

private:
    std::vector<Vec3f> v;
    std::vector<Vec3f> vn;
    std::vector<Vec3f> vt;
};

class TriangleMesh
{
public:
    TriangleMesh(std::string name, const std::vector<Triangle> &tris);

    std::string getObjName() const;
    int getListNum() const;
    const std::vector<Triangle> &getTriangles() const;

    void setListNum(int n);
    void add(Triangle &t);

private:
    std::string objName;
    int listNum;
    std::vector<Triangle> triangles;
};