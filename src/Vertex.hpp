#ifndef VERTEX_H
#define VERTEX_H

#include "Math.hpp"
#include "Texture.hpp"
#include <vector>

namespace paint {

struct Vertex {
    std::vector<Vec4> positions; 
    std::vector<Index> indices; 
    std::vector<Vec3> normals;
    std::vector<float> shadingLevel; //float 0 - 1 (multiple by color values to simulate lighting)
    std::vector<bool> cullFlags;  //each cull flag is associated with an index
};

}

#endif VERTEX_H