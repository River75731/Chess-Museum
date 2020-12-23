#pragma once

#include "../ViewModel/TriangleMesh.h"
#include "../Common/ObjParser.h"

void testObjParser()
{
    std::string name = "../obj_test/obj/deer.obj";
    std::vector<TriangleMesh> tm = ObjParser::parseFile(name);
    for (std::vector<TriangleMesh>::iterator iter = tm.begin(); iter != tm.end(); iter++)
    {
        iter->draw();
    }
}