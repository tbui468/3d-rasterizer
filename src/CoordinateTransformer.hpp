#ifndef COORDINATETRANSFORM_H
#define COORDINATETRANSFORM_H

#include "Math.hpp"
#include "Drawable.hpp"
#include "Screen.hpp"

namespace paint {
//for normalizing coordinate system
//(0,0) at center of screen
//x axis: left is negative, and right is positive
//y axis: down is negative and up is positive
class CoordinateTransformer {
private:
    inline static Vec3 m_scale {1.0f, -1.0f, 1.0f};
    inline static Vec3 m_offset {1.33333f, 1.0f, 1.0f};
    inline static Vec3 m_aspectRatio {300.f, 300.f, 1.0f};
    Screen* m_screen;
public:
    CoordinateTransformer(Screen& screen) : m_screen(&screen) {};

    //projection transform
    void draw(Drawable& drawable) {
        //appply perspective transforms here?? (before coordinate transforms)
        ////drawable.applyTransformation(Mat4::perspective());
        drawable.applyTransformation(Mat4::scale(m_aspectRatio) * Mat4::translate(m_offset) * Mat4::scale(m_scale));
        drawable.render(*m_screen);
    }

};

}


#endif //COORDINATETRANSFORM_H