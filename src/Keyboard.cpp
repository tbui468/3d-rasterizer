#include "Keyboard.h"
#include "../dependencies/SDL2/include/SDL.h"


std::optional<std::vector<int>*> Keyboard::process_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
    }
    return m_user_inputs;
}