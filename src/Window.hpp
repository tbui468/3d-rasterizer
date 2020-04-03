#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "Coordinates.h"

namespace paint
{

//C++ object wrapper for SDL2 Window
class Window
{
private:
    const char *m_title{""};
    const int M_WIDTH{0};
    const int M_HEIGHT{0};
    SDL_Window *m_window{nullptr};
    SDL_Renderer *m_renderer{nullptr};
    SDL_Texture *m_texture{nullptr};
    uint32_t *m_buffer{nullptr};
    uint32_t m_color{0x00000000};

public:
    Window(const char *t_title, int t_width, int t_height);
    bool initialize();
    bool close();
    void render();
    void setColor(uint8_t t_red, uint8_t t_green, uint8_t t_blue);
    void drawPixel(Coordinates t_coordinates);
    void drawRectangle(Coordinates t_topLeft, Coordinates t_bottomRight);
};

} // namespace paint

#endif //WINDOW_H