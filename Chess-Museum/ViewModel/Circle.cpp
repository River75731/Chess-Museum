#include "Circle.h"
#define _USE_MATH_DEFINE
#include <cmath>

Circle::Circle(Vec3f center, Vec3f normal, float radius)
    : center(center), normal(normal), radius(radius)
{
}

void Circle::draw() const
{
    glPushMatrix();
    Vec3f up(0, 1, 0), axis;
    float angle = acos(up.Dot3(normal) / up.Length() / normal.Length()) / PI * 180;
    Vec3f::Cross3(axis, up, normal);
    
    glTranslatef(center.x(), center.y(), center.z());
    glRotatef(angle, axis.x(), axis.y(), axis.z());

    glBegin(GL_POLYGON);
	int i = 0;
	for (i = 0; i <= 360; i++)
	{
		float p = i * PI / 180;
		glVertex3f(sin(p), 0.0f, cos(p));
	}
	glEnd();
    glPopMatrix();
}