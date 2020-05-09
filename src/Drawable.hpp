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
    Mat4 m_transformation;
    Uint32 m_color;
public:
    Drawable(const std::vector<Vec3>& vertexBuffer, const std::vector<Index>& indexBuffer, uint32_t color):  
                m_vertexBuffer(&vertexBuffer),
                m_indexBuffer(&indexBuffer),
                m_color (color)
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

    void render(Screen &screen)
    {
        screen.drawPolygon(*m_vertexBuffer, m_transformation, *m_indexBuffer);
    }

};

} // namespace paint

#endif //DRAWABLE_H