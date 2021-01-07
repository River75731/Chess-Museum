#include "Sphere.h"

Sphere::Sphere(Vec3f center, float radius) : center(center), radius(radius)
{
}

void Sphere::draw() const
{    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(center.x(), center.y(), center.z());
    glutSolidSphere(radius, 32, 32);
    glPopMatrix();
}