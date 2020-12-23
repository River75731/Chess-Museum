#pragma once

#include "../ViewModel/TriangleMesh.h"

class ObjParser
{
public:
    static std::vector<TriangleMesh> parseFile(std::string filename);

private:
    /* !! NEVER INSTANTIATE ObjParser !! */
    ObjParser() {}
    ~ObjParser() {}    
};