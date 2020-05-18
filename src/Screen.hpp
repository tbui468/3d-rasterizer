#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <vector>
#include "Math.hpp"
#include "Vertex.hpp"

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
    int* m_zBuffer;
    Uint32 m_color;
    std::vector<Input> m_inputs; 
    const int SCREEN_HEIGHT;
    const int SCREEN_WIDTH;
public:
    Screen(int width, int height);
    bool initialize();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(uint32_t color);
    void putPixel(int x, int y, int z);
    void drawLine(int x0, int y0, int z0, int x1, int y1, int z1);
    void drawPolygon(const Vertex& vertexBuffer, const Mat4& transformation);
    void fillTriangle(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3);
    void render();
    void clear();
    void processEvents(); //retrieves user input and fills m_inputs
    Input getNextEvent(); //get next event from m_inputs, removing it from vector
    inline bool hasEvents() const { return m_inputs.size() > 0;};
    void close();
private:
    void fillBetweenLines(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3);
    void resetZBuffer(); //sets z buffer distances to infinity (large number)
};

}


#endif //SCREEN_H