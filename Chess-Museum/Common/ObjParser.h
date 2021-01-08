#pragma once

#include "../ViewModel/TriangleMesh.h"

class ObjParser
{
public:
    static std::vector<TriangleMesh> &parseFile();

private:
    /* !! NEVER INSTANTIATE ObjParser !! */
    ObjParser() {}
    ~ObjParser() {}    
};