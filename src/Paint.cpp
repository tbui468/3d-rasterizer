//Pixel Art application

#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Screen.h"
#include "Keyboard.h"
#include "Mouse.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    /***************************/

    Screen *screen = new Screen(800, 600);
    screen->init();
    Mouse *mouse = new Mouse();
    screen->set_color(200, 255, 200);
    screen->draw_background();
    screen->update_screen();

    std::optional<std::vector<int> *> v;
    while (v = mouse->process_events())
    {
        int mouse_x;
        int mouse_y;
        MouseCoordinates coordinates = mouse->get_mouse_coordinates();
        mouse_x = coordinates.x;
        mouse_y = coordinates.y;
        /*
        if (mouse_x < 400)
            screen->set_color(0, 200, 0);
        else
            screen->set_color(255, 5, 255);
        */

        if (v.has_value())
        {
            std::vector<int> *input = v.value();
            if (input->size() > 0)
            {
                int input_number = input->at(0);
                switch (input_number)
                {
                case MouseInputs::button_left:
                    screen->set_color(0, 0, 0);
                    break;
                case MouseInputs::button_middle:
                    screen->set_color(100, 100, 100);
                    break;
                case MouseInputs::button_right:
                    screen->set_color(255, 255, 255);
                    break;
                case MouseInputs::wheel_up:
                    screen->set_color(255, 255, 0);
                    break;
                case MouseInputs::wheel_down:
                    screen->set_color(0, 255, 255);
                    break;
                case MouseInputs::wheel_left:
                    screen->set_color(255, 0, 255);
                    break;
                case MouseInputs::wheel_right:
                    screen->set_color(100, 100, 255);
                    break;
                case MouseInputs::button_one:
                    screen->set_color(0, 0, 0);
                    break;
                case MouseInputs::button_two:
                    screen->set_color(255, 255, 255);
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