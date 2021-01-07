#pragma once

#include "Triangle.h"
#include "ViewGroup.h"
#include "ViewObject.h"
#include <fstream>
#include <string>
#include <vector>

class TriangleMesh : public ViewObject3d
{
public:
    TriangleMesh(const std::vector<Triangle> &tris);

    const std::vector<Triangle> &getTriangles() const;

    void add(Triangle &t);

    virtual void draw() const;

private:
    std::vector<Triangle> triangles;
};