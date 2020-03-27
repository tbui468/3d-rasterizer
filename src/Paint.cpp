#include <iostream>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"

int main(int argc, char* argv[]) {

    SDL_Window* window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if(window == NULL) {
        std::cout << "Could not create window" << std::endl;
        return 1;
    }

    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();


    std::cout << "Hello world" << std::endl;

    return 0;
}