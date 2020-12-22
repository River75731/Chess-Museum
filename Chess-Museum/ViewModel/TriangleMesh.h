#pragma once

#include "../Common/Triangle.h"
#include <GL/glut.h>
#include <fstream>
#include <string>
#include <vector>
#include "ViewObject.h"
#include "ViewGroup.h"

class TriangleMesh : public ViewObject3d
{
public:
    TriangleMesh(std::string name);
    TriangleMesh(std::string name, const std::vector<Triangle> &tris);

    void add(Triangle t);

    virtual void init();
    virtual void draw();

private:
    std::vector<Triangle> triangles;
};