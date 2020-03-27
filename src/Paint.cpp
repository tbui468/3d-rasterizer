#include <iostream>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Screen.h"
#include "Input.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Screen* screen = new Screen(800, 600);
    screen->init();
    Input* input;

    std::cout << "Added input and screen" << std::endl;

    screen->close();
    SDL_Quit();
    return 0;
}