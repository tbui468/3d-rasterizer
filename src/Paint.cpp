#include <iostream>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Screen.h"
#include "Keyboard.h"
#include "Mouse.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    /***************************/

    Screen* screen = new Screen(800, 600);
    screen->init();
    Mouse* mouse = new Mouse();
    screen->set_color(200, 255 , 200);
    screen->draw_background();
    screen->update_screen();
    while(mouse->process_events()) {
        int mouse_x;
        int mouse_y;
        MouseCoordinates coordinates = mouse->get_mouse_coordinates();
        mouse_x = coordinates.x;
        mouse_y = coordinates.y;
        if (mouse_x < 400)
            screen->set_color(0, 0, 0);
        else
            screen->set_color(255, 255, 255);
        screen->draw_background();
        screen->update_screen();
    }

    screen->close();
    /******************************/
    SDL_Quit();
    return 0;
}