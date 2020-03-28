//this is temporary class!!!! Refactor this into InputDevice class (see Input.h for more details)
#include "Input.h"
#include "../dependencies/SDL2/include/SDL.h"

Input::Input() {

}

bool Input::process_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            return false;
    }
    return true;
}
