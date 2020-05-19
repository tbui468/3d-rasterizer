#ifndef VERTEX_H
#define VERTEX_H

#include "Math.hpp"
#include <vector>

namespace paint {

struct Vertex {
    std::vector<Vec4> positions; 
    std::vector<Index> indices; 
    std::vector<bool> cullFlags;  
};

}

#endif VERTEX_H