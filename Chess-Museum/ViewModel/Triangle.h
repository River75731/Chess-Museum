#pragma once

#include "../Common/vectors.h"
#include <array>
#include "ViewObject.h"

class Triangle : public ViewObject3d
{
public:
    void setV(Vec3f a, Vec3f b, Vec3f c);
    void setN(Vec3f a, Vec3f b, Vec3f c);
    void setT(Vec3f a, Vec3f b, Vec3f c);
    const std::array<Vec3f, 3> &getV() const { return v; }
    const std::array<Vec3f, 3> &getN() const { return vn; }
    const std::array<Vec3f, 3> &getT() const { return vt; }
    virtual void draw() const;

private:
    std::array<Vec3f, 3> v;
    std::array<Vec3f, 3> vn;
    std::array<Vec3f, 3> vt;
};