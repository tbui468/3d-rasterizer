#include "Grid.hpp"

namespace paint
{

Grid::Grid(int columns, int rows)
{
    for (int col = 0; col < columns; ++col)
    {
        grid.emplace_back(std::vector<Vertex>());
        for (int row = 0; row < rows; ++row)
        {
            grid.at(col).emplace_back(Vertex {{col, row},
                    VertexType::Unvisited, 10000, nullptr});
        }
    }
}


Vertex* Grid::getVertex(int column, int row) {
    return &(grid.at(column).at(row));
}

//returns a nullptr if no valid next vertex is found
Vertex* Grid::getNextVertex() {
    Vertex* lowestVertex {nullptr};
    for(std::vector<Vertex>& vector : grid) {
        for(Vertex& vertex : vector) {
            if(vertex.type == VertexType::Unvisited || vertex.type == VertexType::End || vertex.type == VertexType::Start) {
                if(lowestVertex == nullptr) {
                    lowestVertex = &vertex;
                }else{
                    if(vertex.minimumDistance < lowestVertex->minimumDistance &&
                        vertex.minimumDistance < 10000) {
                        lowestVertex = &vertex;
                    }
                }
            }
        }
    }

    return lowestVertex;
}

Vertex *Grid::getEnd()
{
    for (std::vector<Vertex> &vector : grid)
    {
        for (Vertex &vertex : vector)
        {
            if (vertex.type == VertexType::End)
            {
                return &vertex;
            }
        }
    }
    return nullptr;
}

Vertex *Grid::getStart()
{
    for (std::vector<Vertex> &vector : grid)
    {
        for (Vertex &vertex : vector)
        {
            if (vertex.type == VertexType::Start)
            {
                return &vertex;
            }
        }
    }
    return nullptr;
}

void Grid::setVertexDistance(int column, int row, int newDistance)
{
    grid.at(column).at(row).minimumDistance = newDistance;
}

void Grid::setVertexType(int column, int row, VertexType newType)
{
    grid.at(column).at(row).type = newType;
    if(newType == VertexType::Start) {
        grid.at(column).at(row).minimumDistance = 0;
    }
}

void Grid::setVertexListPointer(int column, int row, Vertex &nextVertex)
{
    grid.at(column).at(row).previousVertex = &nextVertex;
}

} // namespace paint