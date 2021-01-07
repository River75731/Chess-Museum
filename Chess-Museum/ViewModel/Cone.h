#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

class Cone : public ViewObject3d
{
public:
    Cone(Vec3f center, Vec3f apex, float radius);
    virtual void draw() const;

private:
    Vec3f center, apex;
    float radius;
};