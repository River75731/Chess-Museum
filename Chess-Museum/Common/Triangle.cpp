#include "Triangle.h"

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c)
{
    v[0] = a;
    v[1] = b;
    v[2] = c;
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c)
{
    vn[0] = a;
    vn[1] = b;
    vn[2] = c;
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c)
{
    vt[0] = a;
    vt[1] = b;
    vt[2] = c;
}