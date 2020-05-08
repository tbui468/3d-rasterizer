#ifndef CAMERA_H
#define CAMERA_H

#include "CoordinateTransformer.hpp"
#include "Drawable.hpp"
#include "Math.hpp"

namespace paint {

class Camera {
private:
    CoordinateTransformer m_CT;
    Vec3 m_translation;
    Vec3 m_scale;
    float m_angle;
    Vec3 m_rotationAxis;
public:
    Camera(CoordinateTransformer ct) : m_CT(ct), m_translation({0.0f, 0.0f, 0.0f}), m_scale({1.0f, 1.0f, 1.0f}),
                                       m_angle(0.0f), m_rotationAxis({1.0f, 0.0f, 0.0f}) {};

    //view transforms
    void draw(Drawable&& drawable) {
        drawable.applyTransformation(Mat4::rotate(-m_angle, m_rotationAxis) * Mat4::scale(m_scale) * Mat4::translate(m_translation * (-1)));
        m_CT.draw(drawable); //passes to coordinate transform
    }

    void scaleTo(float zoom) {
        m_scale.x = zoom;
        m_scale.y = zoom;
    }

    void scaleBy(float zoom) {
        m_scale.x += zoom;
        m_scale.y += zoom;
    }

    void moveTo(Vec3 location) {
        m_translation.x = location.x;
        m_translation.y = location.y;
    }

    //translate camera taking camera rotation into account
    void moveBy(Vec3 distance) {
        float cosTheta = cos(m_angle);
        float sinTheta = sin(m_angle);
        m_translation.x += distance.x * cosTheta -sinTheta * distance.y;
        m_translation.y += distance.y * cosTheta + sinTheta * distance.x;
    }

    void rotateBy(float angle, Vec3 axis) {
        m_angle += angle;
    }
};


}

#endif //CAMERA_H