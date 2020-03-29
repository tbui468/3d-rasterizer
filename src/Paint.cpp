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

    }

    screen->close();
    /******************************/
    SDL_Quit();
    return 0;
}