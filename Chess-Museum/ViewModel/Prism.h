#pragma once

#include "../Common/vectors.h"
#include <vector>
#include "ViewObject.h"

/*
The order of the vertices is four on the bottom surface and the corresponding four on top surface
*/
class Prism : public ViewObject3d
{
public:
    Prism(std::vector<Vec3f> &vertices);
    virtual void draw() const;

private:
    std::array<Vec3f, 8> v;
};