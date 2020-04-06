#include "Screen.hpp"
#include <memory>

namespace paint {

bool Screen::initialize() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return false;
    }else{
        return true;
    }
}

void Screen::close() {
    SDL_Quit();
}

}
