#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

class Cone : public ViewObject3d
{
public:
    Cone();
    virtual void draw() const;
private:
};