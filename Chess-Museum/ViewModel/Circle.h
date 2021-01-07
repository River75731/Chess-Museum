#pragma once

#include "../Common/vectors.h"
#include "ViewObject.h"

class Circle : public ViewObject3d
{
public:
    Circle(Vec3f center, Vec3f normal, float radius);

    virtual void draw() const;

public:
    Vec3f center, normal;
    float radius;
};