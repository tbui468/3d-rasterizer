#ifndef VERTEX_H
#define VERTEX_H

#include "Coordinates.hpp"

namespace paint {

enum class VertexType {
    Undefined = 0,
    Unvisited,
    Visited,
    Wall,
    Start,
    End
};


//each grid location will contain a vertex object
struct Vertex {
    Coordinates coordinates {-1,-1};
    VertexType type {VertexType::Undefined};
    int minimumDistance {10000}; //initial value used for Dijkstra's algorithm
    Vertex* previousVertex {nullptr}; //linked list to previous vertex
};

}

#endif //VERTEX_H