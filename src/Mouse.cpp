#include "Mouse.h"
#include "../dependencies/SDL2/include/SDL.h"



bool Mouse::process_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            return false;
    }
    return true;
}

MouseCoordinates Mouse::get_mouse_coordinates() {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return MouseCoordinates {x, y};
}