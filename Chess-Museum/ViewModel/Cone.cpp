#include "Cone.h"

Cone::Cone(Vec3f center, Vec3f apex, float radius)
    : center(center), apex(apex), radius(radius)
{
}

void Cone::draw() const
{
    glPushMatrix();
    Vec3f up(0, 1, 0), normal(apex - center), axis;
    float angle = acos(up.Dot3(normal) / up.Length() / normal.Length()) / PI * 180;
    Vec3f::Cross3(axis, up, normal);

    glTranslatef(center.x(), center.y(), center.z());
    glRotatef(angle, axis.x(), axis.y(), axis.z());
    
    glutSolidCone(radius, (apex - center).Length(), 32, 32);
    glPopMatrix();
}