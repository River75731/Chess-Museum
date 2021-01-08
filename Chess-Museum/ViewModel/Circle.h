#pragma once

#include "../Common/vectors.h"
#include "ViewObject.h"

class Circle : public ViewObject3d
{
public:
    Circle();
    virtual void draw() const;

public:
};