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
    inline static Vec3 m_scale {300.0f, -300.0f, 300.0f};
    inline static Vec3 m_offset {400.0f, 300.0f, 0.0f};
    Screen* m_screen;
public:
    CoordinateTransformer(Screen& screen) : m_screen(&screen) {};

    void draw(Drawable& drawable) {
        //perform backface culling here!!!

        //perspective transformation
        drawable.applyTransformation(Mat4::perspective());

        //how about backface culling here??????

        //peform triangle clipping here

        //viewport mapping
        drawable.applyTransformation(Mat4::translate(m_offset) * Mat4::scale(m_scale));
        drawable.render(*m_screen);
    }

};

}


#endif //COORDINATETRANSFORM_H