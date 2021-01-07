#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

class Cylinder : public ViewObject3d
{
public:
    Cylinder(Vec3f downCenter, Vec3f upCenter, float radius);
    virtual void draw() const;

private:
    Vec3f downCenter;
    Vec3f upCenter;
    float radius;
};