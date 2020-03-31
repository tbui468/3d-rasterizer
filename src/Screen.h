#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Coordinates.h"

class Screen
{
private:
    SDL_Window* m_window;
    SDL_Window* m_window2; //rename later to colorPaletteWindow once button objects are complete
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    uint32_t* m_buffer;
    uint32_t m_color;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
public:
    Screen(int t_width, int t_height): m_window(nullptr), m_window2(nullptr), m_renderer(nullptr), m_texture(nullptr), 
            m_buffer(nullptr), m_color(0x00000000), SCREEN_WIDTH(t_width), SCREEN_HEIGHT(t_height) {};
    bool init();
    void update_screen();
    bool close();
    bool close_window(uint32_t id);
    void set_color(uint8_t t_red, uint8_t t_green, uint8_t t_blue);
    void set_color(uint32_t);
    void set_alpha(int8_t t_alpha);
    void draw_background();
    void draw_pixel(int t_x_coordinate, int t_y_coordinate);
    void DrawRectangle(Coordinates topLeft, Coordinates bottomRight);
};

#endif //SCREEN_H