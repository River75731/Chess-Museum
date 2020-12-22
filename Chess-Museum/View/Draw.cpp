#include "../Common/Triangle.h"
#include <gl/glut.h>

void draw(Triangle tri)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    if (tri.getN()[0].Length() || tri.getN()[1].Length() || tri.getN()[2].Length())
    {
        for (int i = 0; i < 3; i++)
        {
            glNormal3f(tri.getN()[i].x(), tri.getN()[i].y(), tri.getN()[i].z());
            glVertex3f(tri.getV()[i].x(), tri.getV()[i].y(), tri.getV()[i].z());
        }
    }
    else
    {
        Vec3f normal;
        Vec3f::Cross3(normal, tri.getV()[0] - tri.getV()[1], tri.getV()[1] - tri.getV()[2]);
        glNormal3f(normal.x(), normal.y(), normal.z());
        for (int i = 0; i < 3; i++)
        {
            glVertex3f(tri.getV()[i].x(), tri.getV()[i].y(), tri.getV()[i].z());
        }
    }
    glEnd();
    glPopMatrix();
}