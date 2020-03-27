#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"

class Screen
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    Uint32* m_buffer;
    Uint32* m_color;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
public:
    Screen(int t_width, int t_height): m_window(nullptr), m_renderer(nullptr), m_texture(nullptr), 
            m_buffer(nullptr), m_color(0x00000000), SCREEN_WIDTH(t_width), SCREEN_HEIGHT(t_height) {};
    bool init();
    bool close();
    void set_color(Uint8 t_red, Uint8 t_green, Uint8 t_blue);
    void set_alpha(Uint8 t_alpha);
private:
};

#endif //SCREEN_H