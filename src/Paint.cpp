#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <cmath>
#include <math.h>
#include <optional>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Screen.hpp" //this takes care of userinput

#include "Math.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "CoordinateTransformer.hpp"
#include "Texture.hpp"

using namespace paint;


int main()
{

//    Texture tex("../../src/texture.bmp");


    Screen screen(800, 600);

    //regular icosahedron (20 sided die)
    Vertex v;
    float se = 200.0f;
    float l = se * ((1.0f + sqrt(5.0f)) / 2.0f);

    //12 vertices
    //light green plane
    v.positions.emplace_back(-se, -l, 0.0f, 1.0f); //l0
    v.positions.emplace_back(se, -l, 0.0f, 1.0f); //l1
    v.positions.emplace_back(se, l, 0.0f, 1.0f); //l2
    v.positions.emplace_back(-se, l, 0.0f, 1.0f); //l3

    //purple plane
    v.positions.emplace_back(0.0f, -se, -l, 1.0f); //p0
    v.positions.emplace_back(0.0f, se, -l, 1.0f); //p1
    v.positions.emplace_back(0.0f, se, l, 1.0f); //p2
    v.positions.emplace_back(0.0f, -se, l, 1.0f); //p3

    //dark green plane
    v.positions.emplace_back(-l, 0.0f, -se, 1.0f); //d0
    v.positions.emplace_back(l, 0.0f, -se, 1.0f); //d1
    v.positions.emplace_back(l, 0.0f, se, 1.0f); //d2
    v.positions.emplace_back(-l, 0.0f, se, 1.0f); //d3

    //20 faces
    v.indices.emplace_back(0,11,7);
    v.indices.emplace_back(11,6,7);
    v.indices.emplace_back(0,7,1);
    v.indices.emplace_back(7,6,10);
    v.indices.emplace_back(7,10,1);
    v.indices.emplace_back(0,1,4);
    v.indices.emplace_back(4,1,9);
    v.indices.emplace_back(1,10,9);
    v.indices.emplace_back(10,2,9);
    v.indices.emplace_back(6,2,10);

    //top right cap (2)
    v.indices.emplace_back(11,3,6);
    v.indices.emplace_back(3,2,6);
    //bottom left cap (3)
    v.indices.emplace_back(0,4,8);
    v.indices.emplace_back(8,4,5);
    v.indices.emplace_back(4,9,5);

    //reverse of center ring (5)
    v.indices.emplace_back(0,8,11);
    v.indices.emplace_back(5,9,2);

    v.indices.emplace_back(11,8,3);
    v.indices.emplace_back(8,5,3);
    v.indices.emplace_back(3,5,2);

    //USING LEFT HAND COORDINATES (BUT I FUCKED UP AND WANTED TO USE RIGHT HAND)
    //create test entity
    Vertex vertex;
    constexpr float s = 200.0f;
    vertex.positions.emplace_back(-s, -s, -s, 1.0f);
    vertex.positions.emplace_back(s, -s, -s, 1.0f);
    vertex.positions.emplace_back(s, s, -s, 1.0f);
    vertex.positions.emplace_back(-s, s, -s, 1.0f);
    vertex.positions.emplace_back(-s, -s, s, 1.0f);
    vertex.positions.emplace_back(s, -s, s, 1.0f);
    vertex.positions.emplace_back(s, s, s, 1.0f);
    vertex.positions.emplace_back(-s, s, s, 1.0f);
    vertex.positions.emplace_back(0.0f, 2* s, 0.0f, 1.0f);



    //change order of vertices so that 
    //first index is initial position of v1 and v2
    //and second and third indices are endpoints of v1 and v2, respectively
    vertex.indices.emplace_back(0, 2, 1);
    vertex.indices.emplace_back(0, 3, 2);
    vertex.indices.emplace_back(0, 7, 3);
    vertex.indices.emplace_back(0, 4, 7);
    //vertex.indices.emplace_back(0, 5, 4);
    //vertex.indices.emplace_back(0, 1, 5);
    vertex.indices.emplace_back(6, 5, 1);
    vertex.indices.emplace_back(6, 1, 2);
    vertex.indices.emplace_back(6, 2, 3);
    vertex.indices.emplace_back(6, 3, 7);
    vertex.indices.emplace_back(6, 4, 5);
    vertex.indices.emplace_back(6, 7, 4);
    vertex.indices.emplace_back(2,3,8);
    vertex.indices.emplace_back(2,8,6);
    vertex.indices.emplace_back(6,8,7);
    vertex.indices.emplace_back(3,7,8);


    //light source
    Vertex lv;
    Entity light(lv);


    CoordinateTransformer ct(screen, &light);
    Camera camera(ct);




    Entity e(vertex);
    Entity e2(v);
    Entity e3(vertex);

    e.scaleBy({0.0f, 1.0f, 0.0f});
    e.moveBy({0.0f, s, 9000.0f});
    e.rotateBy(.8f);
    e2.moveBy({-2000.5f, 0.0f, 8040.5f});
    e2.rotateBy(3.14f/8.0f);
    e3.moveBy({-2000.5f, 0.0f, 9900.5f});
    light.moveBy({1000.0f, 1000.0f, -1000.0f});

    bool play = true;
    while (play)
    {
        screen.setColor(0, 0, 0);
        screen.clear();

        screen.processEvents();
        while (screen.hasEvents())
        {
            Input input = screen.getNextEvent();
            switch (input)
            {
            case Input::Quit:
                play = false;
                break;
            case Input::Forward:
                camera.moveBy({0.0f, 0.0f, 60.0f});
                break;
            case Input::Backward:
                camera.moveBy({0.0f, 0.0f, -60.0f});
                break;
            case Input::StrafeLeft:
                camera.moveBy({-80.0f, 0.0f, 0.0f});
                break;
            case Input::StrafeRight:
                camera.moveBy({80.0f, 0.0f, 0.0f});
                break;
            case Input::PeekLeft:
                camera.pan(-0.05f);
                break;
            case Input::PeekRight:
                camera.pan(0.05f);
                break;
            case Input::ZoomIn:
                camera.tilt(0.05f);
                break;
            case Input::ZoomOut:
                camera.tilt(-0.05f);
                break;
            case Input::CameraUp:
                camera.moveBy({0.0f, 0.01f, 0.0f});
                break;
            case Input::CameraDown:
                camera.moveBy({0.0f, -0.01f, 0.0f});
                break;
            case Input::CameraLeft:
                camera.moveBy({-0.01f, 0.0f, 0.0f});
                break;
            case Input::CameraRight:
                camera.moveBy({0.01f, 0.0f, 0.0f});
                break;
            case Input::CameraZoomIn: 
                light.moveBy({-10.0f, 0.0f, 0.0f});
                break;
            case Input::CameraZoomOut:
                light.moveBy({10.0f, 0.0f, 0.0f});
                break;
            case Input::CameraRotateCW:
//                light.moveBy({0.0f, 0.0f, 10.0f});
                e2.rotateBy(.1f);
                break;
            case Input::CameraRotateCCW:
 //               light.moveBy({0.0f, 0.0f, -10.0f});
                e2.rotateBy(-.1f);
                break;
            }
        }

        screen.setColor(255, 255, 255);

        camera.draw(e.getDrawable());
        camera.draw(e2.getDrawable());
        camera.draw(e3.getDrawable());
        camera.draw(light.getDrawable());



//        screen.drawLine(0.0f, 300.0f, 800.0f, 300.0f);



        screen.render();
    }

    screen.close();
    return 0;
}