#pragma once

#include "../Common/Triangle.h"
#include "ViewGroup.h"
#include "ViewObject.h"
#include <GL/glut.h>
#include <fstream>
#include <string>
#include <vector>

class TriangleMesh : public ViewObject3d
{
public:
    TriangleMesh(std::string name);
    TriangleMesh(std::string name, const std::vector<Triangle> &tris);

    const std::vector<Triangle> &getTriangles() const;
    int getListNum() const;

    void setListNum(int n);
    void add(Triangle t);

    virtual void init();
    virtual void draw() const;

private:
    std::vector<Triangle> triangles;
    int listNum;
};