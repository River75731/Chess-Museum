#pragma once

#include "../Common/vectors.h"
#include <array>
#include <fstream>
#include <string>
#include <vector>

#define BUFFER_OFFSET(offset) ((GLvoid *)(NULL + offset)) // offset of data in buffer

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
    TriangleMesh();

    std::string getObjName() const;
    int getListNum() const;
    const std::vector<Vec3f> &getV() const;
    const std::vector<Vec3f> &getN() const;
    const std::vector<Vec3f> &getT() const;
    const std::vector<std::array<unsigned int, 9>> &getF() const;

    void setObjName(std::string name);
    void setListNum(int n);
    void addV(Vec3f v);
    void addN(Vec3f n);
    void addT(Vec3f t);
    void addF(std::array<unsigned int, 9>);

    void setVAO();

private:
    std::string objName;
    int listNum;
    std::vector<Vec3f> v;
    std::vector<Vec3f> vn;
    std::vector<Vec3f> vt;
    std::vector<std::array<unsigned int, 9>> f;
};