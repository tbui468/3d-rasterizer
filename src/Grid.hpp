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
    void setVertexType(int column, int row, VertexType newType);
    VertexType getVertexType(int column, int row) const;
    void resetPath(); //resets all visited/path Vertex types to unvisited.  Resets all mindistance values/pointers
    void computePath(); //computes pathfinding algorithm and sets path Vertices type = VertexType::Path
    const std::vector<Coordinates>& getPath();
private:
    Vertex* getVertex(int column, int row);
    Vertex* getNextVertex();
    Vertex* getEnd();
    Vertex* getStart();
    void setVertexDistance(int column, int row, int newDistance);
    void setVertexListPointer(int column, int row, Vertex &nextVertex);
    void updateAdjacentVertex(Vertex *currentVertex, Vertex *adjVertex);
    bool insideGrid(int column, int row) const;

private:
    std::vector<std::vector<Vertex>> m_grid;
    std::vector<Coordinates> m_path;
};

} // namespace paint

#endif //GRID_H