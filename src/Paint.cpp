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
    float s = 0.5f;
    vertex.vertexArray.emplace_back(-s, -s, -s);
    vertex.vertexArray.emplace_back(s, -s, -s);
    vertex.vertexArray.emplace_back(s, s, -s);
    vertex.vertexArray.emplace_back(-s, s, -s);
    vertex.vertexArray.emplace_back(-s, -s, s);
    vertex.vertexArray.emplace_back(s, -s, s);
    vertex.vertexArray.emplace_back(s, s, s);
    vertex.vertexArray.emplace_back(-s, s, s);
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

    Entity e(vertex);


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
                e.moveBy({0.0f, .01f, 0.0f});
                break;
            case Input::Backward:
                e.moveBy({0.0f, -.01f, 0.0f});
                break;
            case Input::StrafeLeft:
                e.moveBy({-.01f, 0.0f, 0.0f});
                break;
            case Input::StrafeRight:
                e.moveBy({.01f, 0.0f, 0.0f});
                break;
            case Input::PeekLeft:
                e.rotateBy(0.05f);
                break;
            case Input::PeekRight:
                e.rotateBy(-0.05f);
                break;
            case Input::ZoomIn:
                e.scaleBy({0.1f, 0.1f, 0.1f});
                break;
            case Input::ZoomOut:
                e.scaleBy({-0.1f, -0.1f, -0.1f});
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
                break;
            case Input::CameraZoomOut:
                break;
            case Input::CameraRotateCW:
                break;
            case Input::CameraRotateCCW:
                break;
            }
        }

        screen.setColor(255, 255, 255);

        camera.draw(e.getDrawable());


        /*
        camera.draw(paddle.getDrawable());
        camera.draw(paddle2.getDrawable());
        camera.draw(paddle3.getDrawable());
        camera.draw(paddle4.getDrawable());*/

        screen.render();
    }

    screen.close();
    return 0;
}