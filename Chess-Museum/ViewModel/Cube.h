#pragma once

#include "../Common/vectors.h"
#include "ViewObject.h"

/*
The order of the vertices is four on the bottom surface and the corresponding four on top surface
*/
class Cube : public ViewObject3d
{
public:
    Cube();
    virtual void draw() const;

private:
};