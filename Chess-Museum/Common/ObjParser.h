#pragma once

#include "../ViewModel/TriangleMesh.h"

class ObjParser
{
public:
    std::vector<TriangleMesh> parseFile(std::string filename);

private:
    /* !! NEVER INSTANTIATE ObjParser !! */
    ObjParser() {}
    ~ObjParser() {}    
};