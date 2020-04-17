#include "Grid.hpp"

namespace paint
{

Grid::Grid(int columns, int rows)
{
    for (int col = 0; col < columns; ++col)
    {
        m_grid.emplace_back(std::vector<Vertex>());
        for (int row = 0; row < rows; ++row)
        {
            m_grid.at(col).emplace_back(Vertex{{col, row},
                                               VertexType::Unvisited,
                                               10000,
                                               nullptr});
        }
    }
}

Vertex *Grid::getVertex(int column, int row)
{
    return &(m_grid.at(column).at(row));
}

VertexType Grid::getVertexType(int column, int row) const {
    return m_grid.at(column).at(row).type;
}

//returns a nullptr if no valid next vertex is found
Vertex *Grid::getNextVertex()
{
    Vertex *lowestVertex{nullptr};
    for (std::vector<Vertex> &vector : m_grid)
    {
        for (Vertex &vertex : vector)
        {
            if (vertex.type == VertexType::Unvisited || vertex.type == VertexType::End || vertex.type == VertexType::Start)
            {
                if (lowestVertex == nullptr)
                {
                    lowestVertex = &vertex;
                }
                else
                {
                    if (vertex.minimumDistance < lowestVertex->minimumDistance &&
                        vertex.minimumDistance < 10000)
                    {
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
    for (std::vector<Vertex> &vector : m_grid)
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
    for (std::vector<Vertex> &vector : m_grid)
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
    m_grid.at(column).at(row).minimumDistance = newDistance;
}

void Grid::setVertexType(int column, int row, VertexType newType)
{
    m_grid.at(column).at(row).type = newType;
    if (newType == VertexType::Start)
    {
        m_grid.at(column).at(row).minimumDistance = 0;
    }
}

void Grid::setVertexListPointer(int column, int row, Vertex &nextVertex)
{
    m_grid.at(column).at(row).previousVertex = &nextVertex;
}

void Grid::updateAdjacentVertex(Vertex *currentVertex, Vertex *adjVertex)
{
    if (adjVertex->type == VertexType::Unvisited || adjVertex->type == VertexType::End)
    {
        int oldAdjacentDis = adjVertex->minimumDistance;
        int newAdjacentDis = currentVertex->minimumDistance + 1;
        //if new distance is less than old dis, update distance, and set pointer
        if (newAdjacentDis < oldAdjacentDis)
        {
            adjVertex->minimumDistance = newAdjacentDis;
            adjVertex->previousVertex = currentVertex;
        }
    }
}

bool Grid::insideGrid(int column, int row) const
{
    bool insideHorizontal = (0 <= column && column < 32);
    bool insideVertical = (0 <= row && row < 24);
    return (insideHorizontal && insideVertical);
}

void Grid::computePath()
{
    while (true)
    {
        //get next vertex
        Vertex *currentVertex = getNextVertex();
        if (currentVertex->type == VertexType::Unvisited || currentVertex->type == VertexType::Start)
        {
            currentVertex->type = VertexType::Visited;
        }
        //exit loop if no Unvisited vertices remains or the next vertex is the end
        if (currentVertex == nullptr || currentVertex->type == VertexType::End)
        {
            break;
        }

        //calculate new values of adjacent vertices (check the four around it
        int col = currentVertex->coordinates.x;
        int row = currentVertex->coordinates.y;
        //check above
        if (insideGrid(col, row - 1))
        {
            Vertex *adjVertex = getVertex(col, row - 1);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check below
        if (insideGrid(col, row + 1))
        {
            Vertex *adjVertex = getVertex(col, row + 1);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check left
        if (insideGrid(col - 1, row))
        {
            Vertex *adjVertex = getVertex(col - 1, row);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check right
        if (insideGrid(col + 1, row))
        {
            Vertex *adjVertex = getVertex(col + 1, row);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
    }

    //update m_path
    m_path.clear();
    Vertex *end = getEnd();
    Vertex *current = end;
    while (current != nullptr)
    {
        m_path.insert(m_path.begin(), current->coordinates);
        current = current->previousVertex;
    }
}

} // namespace paint