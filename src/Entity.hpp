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
    Vec2 m_scale;
    float m_angle;
    Vec2 m_translation;
    uint32_t m_color;
public:
    Entity(Vertex vertex) :
            m_vertexBuffer(vertex.vertexArray),
            m_indexBuffer(vertex.indexArray),
            m_scale({1.0f, 1.0f}),
            m_angle (0.0f),
            m_translation({0.0f, 0.0f}),
            m_color(0x000000ff)
            {};

    


    //these are all the model transforms
    Drawable getDrawable() {
        Drawable d(m_vertexBuffer, m_indexBuffer, m_color);
        d.applyTransformation(Mat3::translate(m_translation) * Mat3::rotate(m_angle) * Mat3::scale(m_scale));
        return d;
    }

    void setScale(Vec3 scale) {
        m_scale.x = scale.x;
        m_scale.y = scale.y;
    }

    void scaleBy(Vec3 scale) {
        m_scale.x += scale.x;
        m_scale.y += scale.y;
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
    }

    void moveBy(Vec3 translation) {
        m_translation.x += translation.x;
        m_translation.y += translation.y;
    }

    void setColor(uint32_t color) {
        m_color = color;
    }

    Vec2 getPosition() const {
        return m_translation;
    }

    float getAngle() const {
        return m_angle;
    }

    Vec2 getScale() const {
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