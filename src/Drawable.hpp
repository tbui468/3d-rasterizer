#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <math.h>
#include <vector>
#include "Math.hpp"
#include "Screen.hpp"


namespace paint {

//stack all translations and scaling 
class Drawable {
private:
    const std::vector<Vec3>* m_vertexBuffer;
    const std::vector<Index>* m_indexBuffer;
    Mat3 m_transformation;
    Uint32 m_color;
public:
    Drawable(const std::vector<Vec3>& vertexBuffer, const std::vector<Index>& indexBuffer, uint32_t color):  
                m_vertexBuffer(&vertexBuffer),
                m_indexBuffer(&indexBuffer),
                m_color (color)
    {};

    void scale(Vec2 scale) {
        m_transformation = Mat3::scale(scale) * m_transformation;
    }

    void rotate(float angle) {
        m_transformation = Mat3::rotate(angle) * m_transformation;
    }

    void translate(Vec2 vec) {
        m_transformation = Mat3::translate(vec) * m_transformation;
    }

    void applyTransformation(Mat3 transformation) {
        m_transformation = transformation * m_transformation;
    }

    void render(Screen &screen)
    {
        //make this call from the GPU for better performance
        std::vector<Vec3> transformedModel;
        for (const Vec3& v : *m_vertexBuffer)
        {
            Vec4 v4 = {v.x, v.y, 1.0f}; //change Vec2 to Vec4
            v4 = m_transformation * v4;
            transformedModel.emplace_back(v4.x, v4.y, v4.z);
        }
        screen.drawPolygon(transformedModel, *m_indexBuffer);
    }
};

} // namespace paint

#endif //DRAWABLE_H