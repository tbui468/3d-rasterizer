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
    inline static Vec3 m_scale {400.0f, -300.0f, 1.0f};
    inline static Vec3 m_offset {400.0f, 300.0f, 0.0f};
    Screen* m_screen;
public:
    CoordinateTransformer(Screen& screen) : m_screen(&screen) {};

    void draw(Drawable& drawable) {
        drawable.clearCullFlags();

        //backface culling before perspective transform
        drawable.cullBackfaces();

        //perspective transformation
        drawable.applyTransformation(Mat4::perspective());
//        drawable.applyTransformation(Mat4::orthogonal());



        drawable.clipTriangles(); //currently only clips if all triangle vertices are out of screeen!!!!! NEED TO FIX!!!

        //viewport mapping
        drawable.applyTransformation(Mat4::translate(m_offset) * Mat4::scale(m_scale));

        drawable.draw(*m_screen);
    }

};

}


#endif //COORDINATETRANSFORM_H