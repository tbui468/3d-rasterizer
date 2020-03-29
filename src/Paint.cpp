//Pixel Art application
#include <iostream>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Screen.h"
#include "UserInput.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    /***************************/

    Screen *screen = new Screen(800, 600);
    screen->init();
    screen->set_color(200, 255, 200);
    screen->draw_background();
    screen->update_screen();
    UserInput* mouse = new UserInput();;
    std::optional<std::vector<int>*> v;
    while (v = mouse->process_events())
    {

        if (v.has_value())
        {
            auto inputs = v.value();
            for (int input : *inputs)
            {
                switch (input)
                {
                case Inputs::KeyUp:
                    screen->set_color(0,0,0);
                    break;
                case Inputs::KeyDown:
                    screen->set_color(255,255,0);
                    break;
                case Inputs::KeyLeft:
                    screen->set_color(255,0,255);
                    break;
                case Inputs::KeyRight:
                    screen->set_color(0,255,255);
                    break;
                case Inputs::MouseLeft:
                    screen->set_color(0,55,25);
                    break;
                case Inputs::MouseRight:
                    screen->set_color(200,25,155);
                    break;
                default:
                    break;
                }
            }
        }

        screen->draw_background();
        screen->update_screen();
    }

    screen->close();
    /******************************/
    SDL_Quit();
    return 0;
}