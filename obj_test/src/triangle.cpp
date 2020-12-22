#include "triangle.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>

#define MAX 100
#define MAX_LINE 200

TriangleMesh::TriangleMesh(string &filename)
{
    fstream in(filename, ios::in);
    if (!in.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }

    string sbuf;
    char buf[MAX];
    char c;
    vector<Vec3f> v;
    vector<Vec3f> vt;
    vector<Vec3f> vn;

    int cnt = 0;

    while (!in.eof())
    {
        in >> sbuf;
        if (sbuf == "v")
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
                n[3 * i] = n[3 * i] < 0 ? v.size() + n[3 * i] + 1 : n[3 * i];
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 1];
                n[3 * i + 1] = n[3 * i + 1] < 0 ? vt.size() + n[3 * i + 1] + 1 : n[3 * i + 1];
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 2];
                n[3 * i + 2] = n[3 * i + 2] < 0 ? vn.size() + n[3 * i + 2] + 1 : n[3 * i + 2];
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
            in.getline(buf, MAX_LINE);
        }
        sbuf = "\0";
    }
    in.close();
}

void TriangleMesh::draw()
{
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (vector<Triangle>::iterator iter = triangles.begin(); iter != triangles.end(); iter++)
    {
        Vec3f a, b, c;
        Vec3f n[3];
        iter->getV(a, b, c);
        iter->getN(n[0], n[1], n[2]);
        Vec3f normal;
        Vec3f::Cross3(normal, a - b, b - c);
        // glNormal3f(normal.x(), normal.y(), normal.z());
        glNormal3f(n[0].x(), n[0].y(), n[0].z());
        glVertex3f(a.x(), a.y(), a.z());
        glNormal3f(n[1].x(), n[1].y(), n[1].z());
        glVertex3f(b.x(), b.y(), b.z());
        glNormal3f(n[2].x(), n[2].y(), n[2].z());
        glVertex3f(c.x(), c.y(), c.z());
    }
    glEnd();
    glPopMatrix();
}