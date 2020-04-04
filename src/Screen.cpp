#include "Screen.hpp"
#include <memory>

namespace paint {

void Screen::initialize() {
    SDL_Init(SDL_INIT_VIDEO);
}

void Screen::close() {
    SDL_Quit();
}

}
