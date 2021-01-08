#pragma once

#include "../Common/vectors.h"
#include <vector>
#include "ViewObject.h"

/* Centrosymmetric Prism */
class Prism : public ViewObject3d
{
public:
    Prism(int a);
    virtual void draw() const;

private:
    int a; // number of edges
};