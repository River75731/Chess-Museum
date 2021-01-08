#pragma once

#include "../Common/vectors.h"
#include "ViewObject.h"

class Cylinder : public ViewObject3d
{
public:
    Cylinder();
    virtual void draw() const;

private:
};