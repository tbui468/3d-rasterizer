#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Coordinates.hpp"
#include "Vertex.hpp"

namespace paint
{

class Grid
{
public:
    Grid(int columns, int rows);
public:
    Vertex* getVertex(int column, int row);
    Vertex* getNextVertex();
    Vertex* getEnd();
    Vertex* getStart();
    void setVertexDistance(int column, int row, int newDistance);
    void setVertexType(int column, int row, VertexType newType);
    void setVertexListPointer(int column, int row, Vertex& nextVertex);
private:
    std::vector<std::vector<Vertex>> grid;
     
};




} // namespace paint

#endif //GRID_H