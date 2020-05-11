#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Drawable.hpp"
#include "Math.hpp"
#include "Vertex.hpp"

namespace paint {

class Entity {
private:
    const std::vector<Vec3> m_vertexBuffer;
    const std::vector<Index> m_indexBuffer;
    Vec3 m_scale;
    float m_angle;
    Vec3 m_rotationAxis;
    Vec3 m_translation;
    uint32_t m_color;
public:
    Entity(Vertex vertex) :
            m_vertexBuffer(vertex.vertexArray),
            m_indexBuffer(vertex.indexArray),
            m_scale({1.0f, 1.0f, 1.0f}),
            m_angle (0.0f),
            m_rotationAxis ({.0f, 1.0f, 1.0f}),
            m_translation({0.0f, 0.0f, 0.0f}),
            m_color(0x000000ff)
            {};

    


    //these are all the model transforms
    Drawable getDrawable() {
        Drawable d(m_vertexBuffer, m_indexBuffer, m_color);
        d.applyTransformation(Mat4::translate(m_translation) * Mat4::rotate(m_angle, m_rotationAxis) * Mat4::scale(m_scale));
        return d;
    }

    void setScale(Vec3 scale) {
        m_scale.x = scale.x;
        m_scale.y = scale.y;
        m_scale.z = scale.z;
    }

    void scaleBy(Vec3 scale) {
        m_scale.x += scale.x;
        m_scale.y += scale.y;
        m_scale.z += scale.z;
    }

    void rotateTo(float angle) {
        m_angle = angle;
    }

    void rotateBy(float angle) {
        m_angle += angle;
    }

    void moveTo(Vec3 position) {
        m_translation.x = position.x;
        m_translation.y = position.y;
        m_translation.z = position.z;
    }

    void moveBy(Vec3 translation) {
        m_translation.x += translation.x;
        m_translation.y += translation.y;
        m_translation.z += translation.z;
    }

    void setColor(uint32_t color) {
        m_color = color;
    }

    Vec3 getPosition() const {
        return m_translation;
    }

    float getAngle() const {
        return m_angle;
    }

    Vec3 getScale() const {
        return m_scale;
    }

    const std::vector<Vec3>& getVertexArray() const {
        return m_vertexBuffer;
    }


    const std::vector<Index>& getIndexArray() const {
        return m_indexBuffer;
    }

};


}


#endif //ENTITY_H