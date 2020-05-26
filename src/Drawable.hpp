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

            //set flat shading level based on normal
            normal = normal * (1.0f / normal.magnitude());
            Vec3 lightSource = {1000.0f, 1000.0f, -1000.0f};
            Vec3 v0 = {vertexPosX.x, vertexPosX.y, vertexPosX.z};
            Vec3 light = lightSource - v0;
            light = light * (1.0f / light.magnitude());
            float c = light * normal;
            if (c >= 0)
                m_vertexBuffer.shadingLevel.push_back(c);
            else
                m_vertexBuffer.shadingLevel.push_back(0.0f);
        }
    }

    //try only clipping to near plane
    void clipTriangles()
    {
        applyVertexShader();
        //copy vertex positions and indices into new data structures
        std::vector<Index> newIndices = m_vertexBuffer.indices;
        std::vector<bool> newCullFlags = m_vertexBuffer.cullFlags;
        std::vector<float> newShadingLevel = m_vertexBuffer.shadingLevel;

        //clear vertex indices and cull flags
        m_vertexBuffer.indices.clear();
        m_vertexBuffer.cullFlags.clear();
        m_vertexBuffer.shadingLevel.clear();

        std::vector<unsigned int> polygon;

        //near plane
        //Plane plane = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
        Plane plane = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};

        //for each index i
        for (unsigned int i = 0; i < newIndices.size(); ++i)
        {
            polygon.clear();

            //skip if polygon is culled
            if (newCullFlags.at(i))
                continue;

            Index index = newIndices.at(i); //three Vec4 vertices

            clipVertices(index.x, index.z, polygon, plane);
            clipVertices(index.y, index.x, polygon, plane);
            clipVertices(index.z, index.y, polygon, plane);

            //convert polygon to triangles and add to m_vertexBuffer.indices
            if (polygon.size() == 3)
            {
                m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(1), polygon.at(2));
                m_vertexBuffer.cullFlags.push_back(newCullFlags.at(i));
                m_vertexBuffer.shadingLevel.push_back(newShadingLevel.at(i));
            }

            if (polygon.size() == 4)
            {
                m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(1), polygon.at(2));
                m_vertexBuffer.indices.emplace_back(polygon.at(0), polygon.at(2), polygon.at(3));
                m_vertexBuffer.cullFlags.push_back(newCullFlags.at(i));
                m_vertexBuffer.cullFlags.push_back(false);
                m_vertexBuffer.shadingLevel.push_back(newShadingLevel.at(i));
                m_vertexBuffer.shadingLevel.push_back(newShadingLevel.at(i));
            }
        }
    }

    //clip vertices against near plane
    void clipVertices(unsigned int currentVertexIndex, unsigned int previousVertexIndex, std::vector<unsigned int> &polygon, Plane plane)
    {

        Vec4 currentVertex = m_vertexBuffer.positions.at(currentVertexIndex);
        Vec4 previousVertex = m_vertexBuffer.positions.at(previousVertexIndex);

        Vec4 dir4 = currentVertex - previousVertex;

        Line line = {{currentVertex.x, currentVertex.y, currentVertex.z}, {dir4.x, dir4.y, dir4.z}};
        Vec3 intersection;
        bool hasIntersection = hasPlaneLineIntersection(plane.normal, line.direction);

        if (hasIntersection)
        {
            intersection = getPlaneLineIntersection(plane, line);
        }

        unsigned int intersectionIndex = m_vertexBuffer.positions.size();

        //polygon clipping algorithm for near plane
        if (currentVertex.z > plane.point.z)
        {
            if (previousVertex.z <= plane.point.z && hasIntersection)
            {
                polygon.push_back(intersectionIndex);
                m_vertexBuffer.positions.emplace_back(intersection.x, intersection.y, intersection.z, 200.0f); //????
            }
            polygon.push_back(currentVertexIndex);
        }
        else if (previousVertex.z > plane.point.z && hasIntersection)
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

    unsigned int getVertexPositionSize() const
    {
        return m_vertexBuffer.positions.size();
    }

    unsigned int getVertexIndexSize() const
    {
        return m_vertexBuffer.indices.size();
    }
};

} // namespace paint

#endif //DRAWABLE_H