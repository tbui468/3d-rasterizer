#ifndef VERTEX_H
#define VERTEX_H

#include "Math.hpp"
#include <vector>

namespace paint {

struct Vertex {
    std::vector<Vec3> vertexArray;
    std::vector<Index> indexArray; 
    std::vector<bool> cullFlags;  
};

}

#endif VERTEX_H