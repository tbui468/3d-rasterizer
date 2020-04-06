#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Window.hpp"

namespace paint {

class Screen
{
public:
    static bool initialize();
    static void close();
};

}


#endif //SCREEN_H