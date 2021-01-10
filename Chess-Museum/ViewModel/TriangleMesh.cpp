#include "TriangleMesh.h"
#include "../View//View.h"
#include <fstream>
#include <string>
#include <vector>

#define MAX_FRAGMENT_NUM 100000

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c)
{
    v.emplace_back(a);
    v.emplace_back(b);
    v.emplace_back(c);
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c)
{
    vn.emplace_back(a);
    vn.emplace_back(b);
    vn.emplace_back(c);
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c)
{
    vt.emplace_back(a);
    vt.emplace_back(b);
    vt.emplace_back(c);
}

void Triangle::setV(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    v.emplace_back(a);
    v.emplace_back(b);
    v.emplace_back(c);
    v.emplace_back(d);
}
void Triangle::setN(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    vn.emplace_back(a);
    vn.emplace_back(b);
    vn.emplace_back(c);
    vn.emplace_back(d);
}
void Triangle::setT(Vec3f a, Vec3f b, Vec3f c, Vec3f d)
{
    vt.emplace_back(a);
    vt.emplace_back(b);
    vt.emplace_back(c);
    vt.emplace_back(d);
}

void Triangle::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    for (int i = 0; i < v.size(); i++)
    {
        glNormal3f(vn[i].x(), vn[i].y(), vn[i].z());
        glTexCoord2f(vt[i].x(), vt[i].y());
        glVertex3f(v[i].x(), v[i].y(), v[i].z());
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

TriangleMesh::TriangleMesh()
{
}

std::string TriangleMesh::getObjName() const
{
    return objName;
}

int TriangleMesh::getListNum() const
{
    return listNum;
}

const std::vector<Vec3f> &TriangleMesh::getV() const
{
    return v;
}

const std::vector<Vec3f> &TriangleMesh::getN() const
{
    return vn;
}

const std::vector<Vec3f> &TriangleMesh::getT() const
{
    return vt;
}

const std::vector<std::array<unsigned int, 9>> &TriangleMesh::getF() const
{
    return f;
}

void TriangleMesh::setObjName(std::string name)
{
    objName = name;
}

void TriangleMesh::setListNum(int n)
{
    listNum = n;
}

void TriangleMesh::addV(Vec3f a)
{
    v.emplace_back(a);
}

void TriangleMesh::addN(Vec3f a)
{
    vn.emplace_back(a);
}

void TriangleMesh::addT(Vec3f a)
{
    vt.emplace_back(a);
}

void TriangleMesh::addF(std::array<unsigned int, 9> a)
{
    f.emplace_back(a);
}

void TriangleMesh::setVAO()
{
    GLfloat *vertexes = new GLfloat[12 * MAX_FRAGMENT_NUM];
    GLfloat *normals = new GLfloat[12 * MAX_FRAGMENT_NUM];
    GLfloat *texCoordes = new GLfloat[6 * MAX_FRAGMENT_NUM];
    GLuint *indexes = new GLuint[3 * MAX_FRAGMENT_NUM];

    int vnn = 0, n = 0, t = 0, in = 0;

    size_t i;
    for (i = 0; i < f.size(); i++)
    {
        for (int b = 0; b < 3; b++)
        {
            for (int a = 0; a < 3; a++)
            {
                vertexes[12 * i + 4 * b + a] = v[f[i][3 * b + 0] - 1][a];
                normals[12 * i + 4 * b + a] = vn[f[i][3 * b + 2] - 1][a];
                vnn++;
                n++;
            }
            vertexes[12 * i + 4 * b + 3] = 1.0f;
            normals[12 * i + 4 * b + 3] = 1.0f;
            vnn++;
            n++;
            indexes[3 * i + b] = 3 * i + b;
            in++;
            for (int a = 0; a < 2; a++)
            {
                texCoordes[6 * i + 2 * b + a] = vt[f[i][3 * b + 1] - 1][a];
                t++;
            }
        }
    }

    size_t vSize = sizeof(GLfloat) * 3 * f.size() * 4;
    size_t nSize = sizeof(GLfloat) * 3 * f.size() * 4;
    size_t tSize = sizeof(GLfloat) * 3 * f.size() * 2;
    size_t iSize = sizeof(GLuint) * 3 * f.size();

    /* VBO */
    GLuint vertexVBO, normalVBO, texVBO;
    GLuint VBOs[3] = {0};

    glBindVertexArray(0);
    glGenBuffers(3, VBOs);
    if (VBOs[0] > 0)
    {
        vertexVBO = VBOs[0];
        normalVBO = VBOs[1];
        texVBO = VBOs[2];
        /* Bind */
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, vSize, vertexes, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, nSize, normals, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, texVBO);
        glBufferData(GL_ARRAY_BUFFER, tSize, texCoordes, GL_STATIC_DRAW);
        /* 
        GL_STATIC_DRAW 是一个性能提示参数，这个参数指示了当前VBO的用途，该参数必须是GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW之一。openGL会根据该指示，尽可能将数据放置在性能最优的内存中，可能是显存，AGP内存，或者cpu内存中。
        GL_STATIC_DRAW：数据指定一次，并多次被用于绘制。
        GL_STREAM_DRAW：数据指定一次，最多几次用于绘制。
        GL_DYNAMIC_DRAW：数组多次指定，多次用于绘制。 
        */
    }

    delete[]vertexes;
    delete[]normals;
    delete[]texCoordes;

    /* IBO */
    GLuint IBO;
    glGenBuffers(1, &IBO);
    if (IBO > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indexes, GL_STATIC_DRAW);
    }

    delete[]indexes;

    /* VAO */
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    if (VAO > 0)
    {
        /* Bind current VAO */
        glBindVertexArray(VAO);
        /* Bind IBO to VAO */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        /* Bind VBOs to VAO */
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, texVBO);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    }

    setListNum(VAO);
}
