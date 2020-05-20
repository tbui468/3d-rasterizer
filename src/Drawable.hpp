#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <math.h>
#include <vector>
#include "Math.hpp"
#include "Screen.hpp"
#include "Vertex.hpp"


namespace paint {

//stack all translations and scaling 
class Drawable {
private:
    Vertex m_vertexBuffer;
    Mat4 m_transformation;
public:
    Drawable(Vertex vertexBuffer):  
                m_vertexBuffer(vertexBuffer)
    {};

    void scale(Vec3 scale) {
        m_transformation = Mat4::scale(scale) * m_transformation;
    }

    void rotate(float angle, Vec3 axis) {
        m_transformation = Mat4::rotate(angle, axis) * m_transformation;
    }

    void translate(Vec3 vec) {
        m_transformation = Mat4::translate(vec) * m_transformation;
    }

    void applyTransformation(Mat4 transformation) {
        m_transformation = transformation * m_transformation;
    }

    void draw(Screen &screen)
    {
        applyVertexShader();
        screen.drawPolygon(m_vertexBuffer);
    }

    //set cull flags
    void cullBackfaces() {
        applyVertexShader();
        for(const Index& i : m_vertexBuffer.indices) {
            //get vector from origin to first point on 
            Vec4 vertexPosX = m_vertexBuffer.positions.at(i.x);
            Vec4 vertexPosY = m_vertexBuffer.positions.at(i.y);
            Vec4 vertexPosZ = m_vertexBuffer.positions.at(i.z);
            Vec4 origin = {0.0f, 0.0f, 0.0f, 0.0f};
            Vec4 triDir = vertexPosX - origin;
            
            Vec4 v1 = vertexPosY - vertexPosX;
            Vec4 v2 = vertexPosZ - vertexPosX;

            //clip Vec4 to Vec3
            Vec3 v1c = {v1.x, v1.y, v1.z};
            Vec3 v2c = {v2.x, v2.y, v2.z};
            Vec3 triDirc {triDir.x, triDir.y, triDir.z};

            Vec3 normal = v1c.crossProduct(v2c);
            
            if(triDirc * normal > 0.0f) {
                m_vertexBuffer.cullFlags.push_back(true);
            }else{
                m_vertexBuffer.cullFlags.push_back(false);
            }
        }
    }

    //try only clipping to near plane
    void clipTriangles() {
        applyVertexShader();
        //copy vertex positions and indices into new data structures
        std::vector<Index> newIndices = m_vertexBuffer.indices;

        //TESTING IF CULLFLAG IS PROBLEM
        //clear vertex indices
        m_vertexBuffer.indices.clear();

        
        //for each index i 
        for(unsigned int i = 0; i < newIndices.size(); ++i) {
            std::vector<unsigned int> polygon;
            Index index = newIndices.at(i); //three Vec4 vertices 

            clipVertices(index.x, index.z, polygon);
            clipVertices(index.y, index.x, polygon);
            clipVertices(index.z, index.y, polygon);

            //convert polygon to triangles and add to m_vertexBuffer.indices
            if (polygon.size() == 3)
            {
                //for (unsigned int k = 1; k < polygon.size() - 1; ++k)
                {
                    m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(1), polygon.at(2));
                }
            }

            if (polygon.size() == 4)
            {
                //for (unsigned int k = 1; k < polygon.size() - 1; ++k)
                {
                    m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(1), polygon.at(2));
                    m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(2), polygon.at(3));
                }
            }
        }
        while(m_vertexBuffer.cullFlags.size() < m_vertexBuffer.indices.size()) {
            m_vertexBuffer.cullFlags.emplace_back(false);
        }
    }

    //clip vertices against near plane and adds
    void clipVertices(unsigned int currentVertexIndex, unsigned int previousVertexIndex, std::vector<unsigned int> &polygon)
    {

        Vec4 currentVertex = m_vertexBuffer.positions.at(currentVertexIndex);
        Vec4 previousVertex = m_vertexBuffer.positions.at(previousVertexIndex);
        Vec4 dir4 = currentVertex - previousVertex;

        Plane plane = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
        Line line = {{currentVertex.x, currentVertex.y, currentVertex.z}, {dir4.x, dir4.y, dir4.z}};
        Vec3 intersection;
        bool hasIntersection = hasPlaneLineIntersection(plane.normal, line.direction);
        if (hasIntersection)
        {
            intersection = getPlaneLineIntersection(plane, line);
        }
        unsigned int intersectionIndex = m_vertexBuffer.positions.size();

        //polygon clipping algorithm
        if (currentVertex.z > 0.0f)
        {
            if (previousVertex.z <= 0.0f && hasIntersection)
            {
                polygon.push_back(intersectionIndex);
                m_vertexBuffer.positions.emplace_back(intersection.x, intersection.y, intersection.z, 200.0f); //????
            }
            polygon.push_back(currentVertexIndex);
        }
        else if (previousVertex.z > 0.0f && hasIntersection)
        {
            polygon.push_back(intersectionIndex);
            m_vertexBuffer.positions.emplace_back(intersection.x, intersection.y, intersection.z, 200.0f); //????
        }
    }

    //transforms vertex positions into clip space
    //resets transformation matrix to identity matrix
    void applyVertexShader()
    {

        unsigned int size = m_vertexBuffer.positions.size();

        //transform all vertices
        for (unsigned int i = 0; i < size; ++i)
        {
            m_vertexBuffer.positions.at(i) = m_transformation * m_vertexBuffer.positions.at(i);
        }

        //resets m_transform to identity matrix
        m_transformation = Mat4();
    }

    //clear all cullflags
    void clearCullFlags()
    {
        m_vertexBuffer.cullFlags.clear();
    }

private:
    /*
    //simple clipping if all vertices are outside of clipping plane
    //NEED TO REDO!!!!!
    bool clip(Vec4 v) {
        bool outX = abs(v.x) > v.w;
        bool outY = abs(v.y) > v.w;
        bool outZ = v.z > v.w || v.z < 0.0f;

        return outX || outY || outZ;
    }*/
};

} // namespace paint

#endif //DRAWABLE_H