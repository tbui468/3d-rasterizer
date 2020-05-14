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


    //create test entity
    Vertex vertex;
    float s = 50.0f;
    vertex.vertexArray.emplace_back(-s, -s, -s);
    vertex.vertexArray.emplace_back(s, -s, -s);
    vertex.vertexArray.emplace_back(s, s, -s);
    vertex.vertexArray.emplace_back(-s, s, -s);
    vertex.vertexArray.emplace_back(-s, -s, s);
    vertex.vertexArray.emplace_back(s, -s, s);
    vertex.vertexArray.emplace_back(s, s, s);
    vertex.vertexArray.emplace_back(-s, s, s);
    vertex.vertexArray.emplace_back(0.0f, 2* s, 0.0f);
    vertex.indexArray.emplace_back(0, 1, 2);
    vertex.indexArray.emplace_back(0, 2, 3);
    vertex.indexArray.emplace_back(0, 4, 7);
    vertex.indexArray.emplace_back(0, 3, 7);
    vertex.indexArray.emplace_back(0, 4, 5);
    vertex.indexArray.emplace_back(0, 1, 5);
    vertex.indexArray.emplace_back(6, 5, 1);
    vertex.indexArray.emplace_back(6, 2, 1);
    vertex.indexArray.emplace_back(6, 3, 2);
    vertex.indexArray.emplace_back(6, 3, 7);
    vertex.indexArray.emplace_back(6, 4, 5);
    vertex.indexArray.emplace_back(6, 4, 7);

    vertex.indexArray.emplace_back(2,3,8);
    vertex.indexArray.emplace_back(2,6,8);
    vertex.indexArray.emplace_back(6,7,8);
    vertex.indexArray.emplace_back(3,7,8);


    Entity e(vertex);
    Entity e2(vertex);
    Entity e3(vertex);

    e.scaleBy({0.0f, 1.0f, 0.0f});
    e.moveBy({0.0f, 50.0f, 150.0f});
    e2.moveBy({-150.0f, 0.0f, 150.0f});
    e3.moveBy({150.0f, 0.0f, 250.0f});

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
                camera.moveBy({0.0f, 0.0f, 2.0f});
                break;
            case Input::Backward:
                camera.moveBy({0.0f, 0.0f, -2.0f});
                break;
            case Input::StrafeLeft:
                camera.moveBy({-2.66f, 0.0f, 0.0f});
                break;
            case Input::StrafeRight:
                camera.moveBy({2.66f, 0.0f, 0.0f});
                break;
            case Input::PeekLeft:
                camera.pan(-0.01f);
                break;
            case Input::PeekRight:
                camera.pan(0.01f);
                break;
            case Input::ZoomIn:
                camera.tilt(0.01f);
                break;
            case Input::ZoomOut:
                camera.tilt(-0.01f);
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

        camera.draw(e.getDrawable());
        camera.draw(e2.getDrawable());
        camera.draw(e3.getDrawable());



//        screen.drawLine(0.0f, 300.0f, 800.0f, 300.0f);

        screen.render();
    }

    screen.close();
    return 0;
}