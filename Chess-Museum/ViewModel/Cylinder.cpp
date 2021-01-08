#include "Cylinder.h"
#include "Circle.h"

Cylinder::Cylinder(Vec3f downCenter, Vec3f upCenter, float radius)
    : downCenter(downCenter), upCenter(upCenter), radius(radius)
{
}

void Cylinder::draw() const
{
    glPushMatrix();
    Vec3f up(0, 1, 0), normal(upCenter - downCenter), axis;
    float angle = acos(up.Dot3(normal) / up.Length() / normal.Length()) / PI * 180;
    Vec3f::Cross3(axis, up, normal);
    glTranslatef(downCenter.x(), downCenter.y(), downCenter.z());
    glRotatef(angle, axis.x(), axis.y(), axis.z());

	for (int i = 0; i <= 360; i++)
	{
		float p = i * PI / 180;
        float q = (i + 1) * PI / 180;

        glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(sin(p), 0.0f, cos(p));
        glVertex3f(sin(q), 0.0f, cos(q));
        glVertex3f(0, normal.Length(), 0);
        glVertex3f(sin(p), normal.Length(), cos(p));
        glVertex3f(sin(q), normal.Length(), cos(q));
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f(sin(p), 0.0f, cos(p));
        glVertex3f(sin(q), 0.0f, cos(q));
        glVertex3f(sin(q), normal.Length(), cos(q));
        glVertex3f(sin(p), normal.Length(), cos(p));
        glEnd();
	}
    glPopMatrix();
}