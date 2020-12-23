#pragma once

#include <gl/glut.h>
#include "../ViewModel/TriangleMesh.h"

void regObject(TriangleMesh &tm)
{
    tm.setListNum(glGenLists(1));
    glNewList(tm.getListNum(), GL_COMPILE);
    for (std::vector<Triangle>::const_iterator iter = tm.getTriangles().begin(); iter != tm.getTriangles().end(); iter++)
    {
        ::draw(*iter);
    }
    glEndList();
}

void callObject(const TriangleMesh &tm)
{
    glCallList(tm.getListNum());
}