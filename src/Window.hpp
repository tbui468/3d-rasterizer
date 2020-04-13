#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Coordinates.hpp"

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
    Uint32 *m_buffer{nullptr};
    Uint32 m_color{0x00000000};

public:
    Window(const char *t_title, int t_width, int t_height);
    bool initialize();
    void close();
    void render();
    void setColor(Uint8 t_red, Uint8 t_green, Uint8 t_blue);
    void setColor(Uint32 t_color);
    void drawPixel(Coordinates t_coordinates);
    void drawRectangle(Coordinates t_topLeft, Coordinates t_bottomRight);
    void drawLine(Coordinates t_start, Coordinates t_end);
    void drawBackground();
    bool isActive() const;
    bool isClosed() const;
    Uint32 getWindowID() const;
};

} // namespace paint

#endif //WINDOW_H