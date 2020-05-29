#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Drawable.hpp"
#include "Math.hpp"
#include "Vertex.hpp"

namespace paint {

class Entity {
private:
    Vertex m_vertexBuffer;
    Vec3 m_scale;
    float m_angle;
    Vec3 m_rotationAxis;
    Vec3 m_translation;
public:
    Entity(Vertex vertex) :
            m_vertexBuffer (vertex),
            m_scale({1.0f, 1.0f, 1.0f}),
            m_angle (0.0f),
            m_rotationAxis ({0.0f, 1.0f, 1.0f}),
            m_translation({0.0f, 0.0f, 0.0f})
            {};

    


    //these are all the model transforms
    Drawable getDrawable() {
        Drawable d(m_vertexBuffer);
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


    Vec3 getPosition() const {
        return m_translation;
    }

    float getAngle() const {
        return m_angle;
    }

    Vec3 getScale() const {
        return m_scale;
    }



};


}


#endif //ENTITY_H