#pragma once

#include "vectors.h"
#include <GL/glut.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Triangle
{
public:
    Triangle() {}
    Triangle(Vec3f a, Vec3f b, Vec3f c) : va(a), vb(b), vc(c) {}

    void setV(Vec3f a, Vec3f b, Vec3f c)
    {
        va = a;
        vb = b;
        vc = c;
    }
    void setN(Vec3f a, Vec3f b, Vec3f c)
    {
        na = a;
        nb = b;
        nc = c;
    }
    void setT(Vec3f a, Vec3f b, Vec3f c)
    {
        ta = a;
        tb = b;
        tc = c;
    }
    void getV(Vec3f &a, Vec3f &b, Vec3f &c)
    {
        a = va;
        b = vb;
        c = vc;
    }
    void getN(Vec3f &a, Vec3f &b, Vec3f &c)
    {
        a = na;
        b = nb;
        c = nc;
    }
    void getT(Vec3f &a, Vec3f &b, Vec3f &c)
    {
        a = ta;
        b = tb;
        c = tc;
    }

private:
    Vec3f va, vb, vc;
    Vec3f na, nb, nc;
    Vec3f ta, tb, tc;
};

// -------------------------------------------------
// -------------------------------------------------

class TriangleMesh
{
public:
    TriangleMesh(string &filename);
    void draw()
    {
        glPushMatrix();
        glBegin(GL_TRIANGLES);
        for (vector<Triangle>::iterator iter = triangles.begin(); iter != triangles.end(); iter++)
        {
            Vec3f a, b, c;
            iter->getV(a, b, c);
            Vec3f normal;
            Vec3f::Cross3(normal, a - b, b - c);
            glNormal3f(normal.x(), normal.y(), normal.z());
            glVertex3f(a.x(), a.y(), a.z());
            glVertex3f(b.x(), b.y(), b.z());
            glVertex3f(c.x(), c.y(), c.z());
        }
        glEnd();
        glPopMatrix();
    }

private:
    vector<Triangle> triangles;
};