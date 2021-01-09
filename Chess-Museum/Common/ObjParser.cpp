#include "ObjParser.h"
#include "../ViewModel/TriangleMesh.h"
#include <sstream>

#define OBJ_MAX_BUF 100
#define OBJ_MAX_LINE 200
#define OBJ_FILE_NUM 1

static std::string objFilePath = "obj/";
static std::string objFileName[OBJ_FILE_NUM] =
    {"pawn.obj"};

std::vector<TriangleMesh> ObjParser::parseFile()
{
    std::vector<TriangleMesh> TriangleMeshs;
    for (int i = 0; i < OBJ_FILE_NUM; i++)
    {
        fstream in(objFilePath + objFileName[i], ios::in);
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
                    TriangleMeshs.emplace_back(mesh);
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
                int n[12] = {0};
                in.getline(buf, OBJ_MAX_LINE);
                istringstream iss(buf);
                int i = 0;
                while (!iss.eof() && i <= 3)
                {
                    iss >> n[3 * i];
                    n[3 * i] = n[3 * i] < 0 ? v.size() + n[3 * i] + 1 : n[3 * i]; // number of v/vt/vn may be negative
                    iss.get(c);
                    if (c != '/')
                        continue;
                    iss >> n[3 * i + 1];
                    n[3 * i + 1] = n[3 * i + 1] < 0 ? vt.size() + n[3 * i + 1] + 1 : n[3 * i + 1]; // number of v/vt/vn may be negative
                    iss.get(c);
                    if (c != '/')
                        continue;
                    iss >> n[3 * i + 2];
                    n[3 * i + 2] = n[3 * i + 2] < 0 ? vn.size() + n[3 * i + 2] + 1 : n[3 * i + 2]; // number of v/vt/vn may be negative
                    i++;
                }
                if (n[0] && n[3] && n[6])
                    if (n[9])
                        new_triangle.setV(v[n[0] - 1], v[n[3] - 1], v[n[6] - 1], v[n[9] - 1]);
                    else
                        new_triangle.setV(v[n[0] - 1], v[n[3] - 1], v[n[6] - 1]);
                if (n[1] && n[4] && n[7])
                    if (n[10])
                        new_triangle.setT(vt[n[1] - 1], vt[n[4] - 1], vt[n[7] - 1], vt[n[10] - 1]);
                    else
                        new_triangle.setT(vt[n[1] - 1], vt[n[4] - 1], vt[n[7] - 1]);
                if (n[2] && n[5] && n[8])
                    if (n[11])
                        new_triangle.setN(vn[n[2] - 1], vn[n[5] - 1], vn[n[8] - 1], vn[n[11] - 1]);
                    else
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
        TriangleMeshs.emplace_back(mesh);

        in.close();
    }

    return TriangleMeshs;
}