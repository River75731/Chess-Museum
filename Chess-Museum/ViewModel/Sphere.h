#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

/*
The order of the vertices is four on the bottom surface and the corresponding four on top surface
*/
class Sphere : public ViewObject3d
{
public:
    Sphere(Vec3f center, float radius);
    virtual void draw() const;

private:
    Vec3f center;
    float radius;
};