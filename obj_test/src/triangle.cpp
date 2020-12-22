#include "triangle.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>

#define OBJ_MAX_BUF 100
#define OBJ_MAX_LINE 200

TriangleMesh::TriangleMesh(std::string name)
{
    // TODO: init ViewObject
}

TriangleMesh::TriangleMesh(std::string name, const std::vector<Triangle> &tris)
{
    // TODO: init ViewObject
    triangles = tris;
}

std::vector<TriangleMesh> TriangleMesh::parseFile(std::string filename)
{
    fstream in(filename, ios::in);
    if (!in.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }

    std::string sbuf;
    std::string groupName;
    char buf[OBJ_MAX_BUF];
    char c;
    std::vector<Vec3f> v;
    std::vector<Vec3f> vt;
    std::vector<Vec3f> vn;
    std::vector<Triangle> triangles;
    std::vector<TriangleMesh> triangleMeshs;

    int cnt = 0;

    while (!in.eof())
    {
        in >> sbuf;
        if (sbuf == "g")
        {
            /* if not first group, save the last one */
            if (triangles.size() != 0)
            {
                TriangleMesh mesh(groupName, triangles);
                triangleMeshs.emplace_back(mesh);
                /* clear temp vectors */
                v.clear();
                vt.clear();
                vn.clear();
                triangles.clear();
            }
            in >> groupName;
        }
        else if (sbuf == "v")
        {
            Vec3f new_v;
            in >> new_v;
            v.emplace_back(new_v);
        }
        else if (sbuf == "vt")
        {
            Vec3f new_vt;
            in >> new_vt;
            vt.emplace_back(new_vt);
            cnt++;
        }
        else if (sbuf == "vn")
        {
            Vec3f new_vn;
            in >> new_vn;
            vn.emplace_back(new_vn);
        }
        else if (sbuf == "f")
        {
            Triangle new_triangle;
            int n[9] = {0};
            for (int i = 0; i < 3; i++)
            {
                in >> n[3 * i];
                n[3 * i] = n[3 * i] < 0 ? v.size() + n[3 * i] + 1 : n[3 * i]; // number of v/vt/vn may be negative
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 1];
                n[3 * i + 1] = n[3 * i + 1] < 0 ? vt.size() + n[3 * i + 1] + 1 : n[3 * i + 1]; // number of v/vt/vn may be negative
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 2];
                n[3 * i + 2] = n[3 * i + 2] < 0 ? vn.size() + n[3 * i + 2] + 1 : n[3 * i + 2]; // number of v/vt/vn may be negative
            }
            if (n[0] && n[3] && n[6])
                new_triangle.setV(v[n[0] - 1], v[n[3] - 1], v[n[6] - 1]);
            if (n[1] && n[4] && n[7])
                new_triangle.setT(vt[n[1] - 1], vt[n[4] - 1], vt[n[7] - 1]);
            if (n[2] && n[5] && n[8])
                new_triangle.setN(vn[n[2] - 1], vn[n[5] - 1], vn[n[8] - 1]);
            triangles.emplace_back(new_triangle);
        }
        else
        {
            in.getline(buf, OBJ_MAX_LINE);
        }
        sbuf = "\0";
    }
    TriangleMesh mesh(groupName, triangles);
    triangleMeshs.emplace_back(mesh);

    in.close();

    return triangleMeshs;
}

void TriangleMesh::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (std::vector<Triangle>::iterator iter = triangles.begin(); iter != triangles.end(); iter++)
    {
        if (iter->getN()[0].Length() || iter->getN()[1].Length() || iter->getN()[2].Length())
        {
            for (int i = 0; i < 3; i++)
            {
                glNormal3f(iter->getN()[i].x(), iter->getN()[i].y(), iter->getN()[i].z());
                glVertex3f(iter->getV()[i].x(), iter->getV()[i].y(), iter->getV()[i].z());
            }
        }
        else
        {
            Vec3f normal;
            Vec3f::Cross3(normal, iter->getV()[0] - iter->getV()[1], iter->getV()[1] - iter->getV()[2]);
            glNormal3f(normal.x(), normal.y(), normal.z());
            for (int i = 0; i < 3; i++)
            {
                glVertex3f(iter->getV()[i].x(), iter->getV()[i].y(), iter->getV()[i].z());
            }
        }
    }
    glEnd();
    glPopMatrix();
}