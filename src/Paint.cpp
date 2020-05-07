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
                break;
            case Input::Backward:
                break;
            case Input::StrafeLeft:
                break;
            case Input::StrafeRight:
                break;
            case Input::PeekLeft:
                break;
            case Input::PeekRight:
                break;
            case Input::ZoomIn:
                break;
            case Input::ZoomOut:
                break;
            case Input::CameraUp:
                camera.moveBy({0.0f, 2.0f});
                break;
            case Input::CameraDown:
                camera.moveBy({0.0f, -2.0f});
                break;
            case Input::CameraLeft:
                camera.moveBy({-2.0f, 0.0f});
                break;
            case Input::CameraRight:
                camera.moveBy({2.0f, 0.0f});
                break;
            case Input::CameraZoomIn:
                camera.scaleBy(0.01f);
                break;
            case Input::CameraZoomOut:
                camera.scaleBy(-0.01f);
                break;
            case Input::CameraRotateCW:
                camera.rotateBy(.01f);
                break;
            case Input::CameraRotateCCW:
                camera.rotateBy(-.01f);
                break;
            }
        }

        screen.setColor(255, 255, 255);


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