#include "Screen.h"

bool Screen::init() {
    m_window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if(m_window == NULL) {
        return false;
    }
    //create renderer
    //create texture
    m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    return true;
}


bool Screen::close() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    delete[] m_buffer;
    delete m_color;

    return true;
}
