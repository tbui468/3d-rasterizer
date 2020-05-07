#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <vector>
#include "Math.hpp"

namespace paint {

struct Vec2;
struct Index;

enum class Input {
    Forward = 0,
    Backward,
    StrafeLeft,
    StrafeRight,
    PeekLeft,
    PeekRight,
    ZoomIn,
    ZoomOut,
    CameraUp,
    CameraDown,
    CameraLeft,
    CameraRight,
    CameraRotateCW,
    CameraRotateCCW,
    CameraZoomIn,
    CameraZoomOut,
    Quit
};

class Screen
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    Uint32* m_buffer; 
    Uint32 m_color;
    std::vector<Input> m_inputs; 
    const int SCREEN_HEIGHT;
    const int SCREEN_WIDTH;
public:
    Screen(int width, int height);
    bool initialize();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(uint32_t color);
    void putPixel(int x, int y);
    void drawLine(float x0, float y0, float x1, float y1);
    void drawPolygon(const std::vector<Vec2>& transformedBuffer, const std::vector<Index>& indexBuffer);
    void render();
    void clear();
    void processEvents(); //retrieves user input and fills m_inputs
    Input getNextEvent(); //get next event from m_inputs, removing it from vector
    inline bool hasEvents() const { return m_inputs.size() > 0;};
    void close();
};

}


#endif //SCREEN_H