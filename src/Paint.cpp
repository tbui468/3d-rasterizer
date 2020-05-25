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

using namespace paint;


int main()
{


    Screen screen(800, 600);


    CoordinateTransformer ct(screen);
    Camera camera(ct);

    //USING LEFT HAND COORDINATES (BUT I FUCKED UP AND WANTED TO USE RIGHT HAND)
    //create test entity
    Vertex vertex;
    float s = 200.0f;
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
    vertex.indices.emplace_back(0, 5, 4);
    vertex.indices.emplace_back(0, 1, 5);
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

    Vertex floorVertex;
    float f = 500.0f;
    floorVertex.positions.emplace_back(-f, -f , -f - 100.0f, 1.0f);
    floorVertex.positions.emplace_back(f, -f, -f - 100.0f, 1.0f);
    floorVertex.positions.emplace_back(f, f, -f - 100.0f, 1.0f);
    floorVertex.positions.emplace_back(-f, f, -f - 100.0f, 1.0f);
    floorVertex.positions.emplace_back(f, -f, f - 100.0f, 1.0f);
    floorVertex.positions.emplace_back(f, f, f - 100.0f, 1.0f);
    floorVertex.indices.emplace_back(0, 2, 1);
    floorVertex.indices.emplace_back(0, 3, 2);
    floorVertex.indices.emplace_back(1, 5, 4);
    floorVertex.indices.emplace_back(1, 2, 5);


    Entity e(vertex);
    Entity e2(vertex);
    Entity e3(vertex);
    Entity floor(floorVertex);

    e.scaleBy({0.0f, 1.0f, 0.0f});
    e.moveBy({0.0f, s, 9000.0f});
    e.rotateBy(3.14f);
    e2.moveBy({-2000.5f, 0.0f, 8040.5f});
    e2.rotateBy(3.14f/2.0f);
    floor.moveBy({0.0f, 0.0f, 1000.0f});
    e3.moveBy({-2000.5f, 0.0f, 9900.5f});

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
                camera.moveBy({0.0f, 0.0f, 1.01f});
                break;
            case Input::CameraZoomOut:
                camera.moveBy({0.0f, 0.0f, -1.01f});
                break;
            case Input::CameraRotateCW:
                break;
            case Input::CameraRotateCCW:
                break;
            }
        }

        screen.setColor(255, 255, 255);

 //       camera.draw(e.getDrawable());
        camera.draw(e2.getDrawable());
//        camera.draw(floor.getDrawable());
   //     camera.draw(e3.getDrawable());



//        screen.drawLine(0.0f, 300.0f, 800.0f, 300.0f);


        screen.render();
    }

    screen.close();
    return 0;
}