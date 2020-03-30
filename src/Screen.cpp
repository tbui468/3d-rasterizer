#include "Screen.h"

bool Screen::init() {
    m_window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if(m_window == nullptr) {
        return false;
    }
    m_window2 = SDL_CreateWindow("Paint2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if(m_window2 == nullptr) {
        return false;
    }
    //create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == nullptr) {
        SDL_DestroyWindow(m_window);
        return false;
    }
    //create texture
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_texture == nullptr) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        return false;
    }
    m_buffer = new uint32_t[SCREEN_WIDTH * SCREEN_HEIGHT];

    SDL_SetWindowBordered(m_window, SDL_TRUE);
    set_color(255,255,255);
    draw_background();
    update_screen();
    return true;
}

void Screen::update_screen() {
    SDL_UpdateTexture(m_texture, nullptr, m_buffer, SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Screen::set_color(uint8_t t_red, uint8_t t_green, uint8_t t_blue) {
    m_color = t_red;
    m_color <<= 8;
    m_color += t_green;
    m_color <<= 8;
    m_color += t_blue;
    m_color <<= 8;
}

bool Screen::close() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    delete[] m_buffer;

    return true;
}

bool Screen::close_window(uint32_t id) {
    if(id == SDL_GetWindowID(m_window))
        SDL_DestroyWindow(m_window);
    if(id == SDL_GetWindowID(m_window2))
        SDL_DestroyWindow(m_window2);
    return true;
}

void Screen::draw_background() {
    for(int row = 0; row < SCREEN_HEIGHT; ++row) {
        for(int col = 0; col < SCREEN_WIDTH; ++col) {
            m_buffer[row * SCREEN_WIDTH + col] = m_color;
        }
    }
}

void Screen::draw_pixel(int t_x_coordinate, int t_y_coordinate) {
    m_buffer[t_y_coordinate * SCREEN_WIDTH + t_x_coordinate] = m_color;
}