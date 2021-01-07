#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

/*
The order of the vertices is four on the bottom surface and the corresponding four on top surface
*/
class Cube : public ViewObject3d
{
public:
    Cube(std::array<Vec3f, 8> &vertices);
    virtual void draw() const;

private:
    std::array<Vec3f, 8> v;
};