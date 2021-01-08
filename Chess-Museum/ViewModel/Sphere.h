#pragma once

#include "../Common/vectors.h"
#include "ViewObject.h"

class Sphere : public ViewObject3d
{
public:
    Sphere();
    virtual void draw() const;

private:
};