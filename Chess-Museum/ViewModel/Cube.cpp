#include "Cube.h"

Cube::Cube(std::array<Vec3f, 8> &vertices)
{
    v = vertices;
}

void Cube::draw() const
{    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(v[0].x(), v[0].y(), v[0].z());
    glVertex3f(v[1].x(), v[1].y(), v[1].z());
    glVertex3f(v[2].x(), v[2].y(), v[2].z());
    glVertex3f(v[3].x(), v[3].y(), v[3].z());
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(v[4].x(), v[4].y(), v[4].z());
    glVertex3f(v[5].x(), v[5].y(), v[5].z());
    glVertex3f(v[6].x(), v[6].y(), v[6].z());
    glVertex3f(v[7].x(), v[7].y(), v[7].z());
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(v[0].x(), v[0].y(), v[0].z());
    glVertex3f(v[1].x(), v[1].y(), v[1].z());
    glVertex3f(v[5].x(), v[5].y(), v[5].z());
    glVertex3f(v[4].x(), v[4].y(), v[4].z());
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(v[1].x(), v[1].y(), v[1].z());
    glVertex3f(v[2].x(), v[2].y(), v[2].z());
    glVertex3f(v[6].x(), v[6].y(), v[6].z());
    glVertex3f(v[5].x(), v[5].y(), v[5].z());
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(v[2].x(), v[2].y(), v[2].z());
    glVertex3f(v[3].x(), v[3].y(), v[3].z());
    glVertex3f(v[7].x(), v[7].y(), v[7].z());
    glVertex3f(v[6].x(), v[6].y(), v[6].z());
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(v[3].x(), v[3].y(), v[3].z());
    glVertex3f(v[0].x(), v[0].y(), v[0].z());
    glVertex3f(v[4].x(), v[4].y(), v[4].z());
    glVertex3f(v[7].x(), v[7].y(), v[7].z());
    glEnd();
    glPopMatrix();
}