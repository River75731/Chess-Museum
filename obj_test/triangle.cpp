#include "triangle.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>

#define MAX 100
#define MAX_LINE 200

using namespace std;

TriangleMesh::TriangleMesh(string &filename)
{
    fstream in(filename, ios::in);
    if (!in.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }
    // read it once, get counts
    string sbuf;
    char buf[MAX];
    char c;
    vector<Vec3f> v;
    vector<Vec3f> vt;
    vector<Vec3f> vn;

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
            v.emplace_back(new_vt);
        }
        else if (sbuf == "vn")
        {
            Vec3f new_vn;
            in >> new_vn;
            v.emplace_back(new_vn);
        }
        else if (sbuf == "f")
        {
            Triangle new_triangle;
            int n[9] = {0};
            for (int i = 0; i < 3; i++)
            {
                in >> n[3 * i];
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 1];
                in.get(c);
                if (c != '/')
                    continue;
                in >> n[3 * i + 2];
            }
            if (n[0] && n[3] && n[6])
                new_triangle.setV(v[n[0] - 1], v[n[3] - 1], v[n[6] - 1]);
            if (n[1] && n[4] && n[7])
                new_triangle.setN(v[n[1] - 1], v[n[4] - 1], v[n[7] - 1]);
            if (n[2] && n[5] && n[8])
                new_triangle.setT(v[n[2] - 1], v[n[5] - 1], v[n[8] - 1]);
            triangles.emplace_back(new_triangle);
        }
        else
        {
            in.getline(buf, MAX_LINE);
        }
    }
    in.close();
}