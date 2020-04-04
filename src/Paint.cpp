//Pixel Art application
/*
FEATURES Deadline: April 5 by midnight
**********
8 canvas tabs
    -click to add new tabs (like in a web browser)
    -play/stop button will scroll through the tabs to animate
8 quick colors
    -eight different quick select colors
    -click customize to open subscreen to customize the eight colors
    -choose from a color from color gradient or input hex/rgb (no alpha)
4 quick brushes
    -four quick select brushes
    -click customize to open subscreen to customize four brushes
    -customize shape (square, circle, diamond) and size (horizontal and vertical scale)
4 special brush options from main menu 
    -regular brush
    -erase brush
    -color picker
    -fill all similar colors

SCreen size 800 x 600
submenu size 400 x 300 (1/4 the size)
Canvas size:  ~512 x 512  //scale is 32x32
Menu Bar size: ~300 x 600
default background (blue checkered similar to Cobalt blue)
Default frame color (darker blue similar to Cobalt blue theme)
Highlights: yellow, orange, red, purple, green (Cobalt theme)
    - mouse hover over pixel will highlight with yellow
    - other highlights

TO DO: CLOSING WINDOWS IS NOT WORKING CORRECTLY.  USER INPUT SHOULD RETURN CLOSE WINDOW (OR WINDOW ID//)

*/

#include <iostream>
#include <memory>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Coordinates.hpp"
#include "Screen.hpp"
#include "UserInput.hpp"

using namespace paint;

int main(int argc, char *argv[])
{
    Screen::initialize();

    Window mainWindow("Paint", 800, 600);
    Window colorWindow("Color", 400, 300);

    UserInput userinput;
    bool appOpen = true;
    while (appOpen)
    {
        std::vector<Inputs> inputs = userinput.processEvents();
        for (Inputs input : inputs)
        {
            switch (input)
            {
            case Inputs::MouseLeft:
                break;
            case Inputs::MouseRight:
                break;
            case Inputs::CloseColorWindow:
                colorWindow.close();
                break;
            case Inputs::CloseMainWindow:
            {
                appOpen = false;
                break;
            }
            default:
                break;
            }
        }
    }

    mainWindow.close();
    Screen::close();
    return 0;
}