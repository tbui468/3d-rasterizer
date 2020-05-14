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
    Vertex* m_vertexBuffer;
    Mat4 m_transformation;
public:
    Drawable(Vertex& vertexBuffer):  
                m_vertexBuffer(&vertexBuffer)
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
        screen.drawPolygon(*m_vertexBuffer, m_transformation);
    }

    //set cull flags
    void cullBackfaces() {
        clearCullFlags();
        std::vector<Vec4> tVertices;

        //transform all vertices
        for(const Vec3& v : m_vertexBuffer->positions) {
            Vec4 tv = {v.x, v.y, v.z, 1.0f};
            tv = m_transformation * tv; 
            tVertices.push_back(tv);
        }
    
        for(const Index& i : m_vertexBuffer->indices) {
            //get vector from origin to first point on 
            Vec4 vertexPosX = tVertices.at(i.x);
            Vec4 vertexPosY = tVertices.at(i.y);
            Vec4 vertexPosZ = tVertices.at(i.z);
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
                m_vertexBuffer->cullFlags.push_back(true);
            }else{
                m_vertexBuffer->cullFlags.push_back(false);
            }
        }
    }

    void clipTriangles() {
        std::vector<Vec4> tVertices;

        //transform all vertices (include perspective transforms)
        for(const Vec3& v : m_vertexBuffer->positions) {
            Vec4 tv = {v.x, v.y, v.z, 1.0f};
            tv = m_transformation * tv; 
            tVertices.push_back(tv);
        }
        for(unsigned int k = 0; k < m_vertexBuffer->indices.size(); ++k)
//        for(const Index& i : m_vertexBuffer->indices) {
            {
            const Index& i = m_vertexBuffer->indices.at(k);
            //get vector from origin to first point on 
            Vec4 vertexPosX = tVertices.at(i.x);
            Vec4 vertexPosY = tVertices.at(i.y);
            Vec4 vertexPosZ = tVertices.at(i.z);


            bool clipTri = clip(vertexPosX) && clip(vertexPosY) && clip(vertexPosZ);
            if(clipTri) {
                m_vertexBuffer->cullFlags.at(k) = true;
            }
        }
    }

private:
    void clearCullFlags() {
        m_vertexBuffer->cullFlags.clear();
    }

    //simple clipping if all vertices are outside of clipping plane
    //NEED TO REDO!!!!!
    bool clip(Vec4 v) {
        bool outX = abs(v.x) > v.w;
        bool outY = abs(v.y) > v.w;
        bool outZ = v.z > v.w || v.z < 0.0f;

        return outX && outY && outZ;
    }

};

} // namespace paint

#endif //DRAWABLE_H