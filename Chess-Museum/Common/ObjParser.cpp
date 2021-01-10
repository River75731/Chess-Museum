#include "ObjParser.h"
#include "../ViewModel/TriangleMesh.h"
#include <sstream>

#define OBJ_MAX_BUF 100
#define OBJ_MAX_LINE 200
#define OBJ_FILE_NUM 1

static std::string objFilePath = "obj/";
static std::string objFileName[OBJ_FILE_NUM] =
    {"bishop.obj"};

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
        TriangleMesh mesh;

        int cnt = 0;

        while (!in.eof())
        {
            in >> sbuf;
            if (sbuf == "g")
            {
                /* if not first group, save the last one */
                if (mesh.getF().size() != 0)
                {
                    mesh.setObjName(groupName);
                    TriangleMeshs.emplace_back(mesh);
                }
                in >> groupName;
            }
            else if (sbuf == "v")
            {
                Vec3f new_v;
                in >> new_v;
                mesh.addV(new_v);
            }
            else if (sbuf == "vt")
            {
                Vec3f new_vt;
                in >> new_vt;
                mesh.addT(new_vt);
                cnt++;
            }
            else if (sbuf == "vn")
            {
                Vec3f new_vn;
                in >> new_vn;
                mesh.addN(new_vn);
            }
            else if (sbuf == "f")
            {
                std::array<unsigned int, 9> n = {0};
                
                for (int i = 0; i < 3; i++)
                {
                    in >> n[3 * i];
                    n[3 * i] = n[3 * i] < 0 ? mesh.getV().size() + n[3 * i] + 1 : n[3 * i]; // number of v/vt/vn may be negative
                    in.get(c);
                    if (c != '/')
                        continue;
                    in >> n[3 * i + 1];
                    n[3 * i + 1] = n[3 * i + 1] < 0 ? mesh.getT().size() + n[3 * i + 1] + 1 : n[3 * i + 1]; // number of v/vt/vn may be negative
                    in.get(c);
                    if (c != '/')
                        continue;
                    in >> n[3 * i + 2];
                    n[3 * i + 2] = n[3 * i + 2] < 0 ? mesh.getN().size() + n[3 * i + 2] + 1 : n[3 * i + 2]; // number of v/vt/vn may be negative
                }
                mesh.addF(n);
            }
            else
            {
                in.getline(buf, OBJ_MAX_LINE);
            }
            sbuf = "\0";
        }
        mesh.setObjName(groupName);
        TriangleMeshs.emplace_back(mesh);

        in.close();
    }

    return TriangleMeshs;
}