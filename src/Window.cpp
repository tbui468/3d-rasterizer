#include "Window.hpp"
#include <iostream>

namespace paint
{

Window::Window(const char *t_title, int t_width, int t_height) : m_title(t_title), M_WIDTH(t_width), M_HEIGHT(t_height){
//    if(initialize())
    if(initialize())
        std::cout << "Window successfully initialized\n";
    else
        std::cout << "Window failed to initialize\n";
};

bool Window::initialize()
{
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, M_WIDTH, M_HEIGHT, 0);
    if (m_window == nullptr)
    {
        return false;
    }
    //create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        return false;
    }
    //create texture
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, M_WIDTH, M_HEIGHT);
    if (m_texture == nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        return false;
    }

    m_buffer = new Uint32[M_WIDTH * M_HEIGHT];
	memset(m_buffer, 0, sizeof(Uint32) * M_WIDTH * M_HEIGHT);
    SDL_SetWindowBordered(m_window, SDL_TRUE);
    return true;
}

void Window::close()
{
    if (isClosed()) {
        return;
    }
        std::cout << "Window closed" << std::endl;

        delete[] m_buffer;
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

        m_buffer = nullptr;
        m_texture = nullptr;
        m_renderer = nullptr;
        m_window = nullptr;

}

void Window::render()
{
    if (isClosed())
    {
        return;
    }
    SDL_UpdateTexture(m_texture, nullptr, m_buffer, M_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Window::setColor(Uint8 t_red, Uint8 t_green, Uint8 t_blue)
{
    m_color = t_red;
    m_color <<= 8;
    m_color += t_green;
    m_color <<= 8;
    m_color += t_blue;
    m_color <<= 8;
    m_color += 0xff;
}

void Window::setColor(Uint32 t_color)
{
    m_color = t_color;
}

void Window::drawPixel(Coordinates t_coordinates)
{
    if(isClosed()){
        return;
    }
    m_buffer[t_coordinates.y * M_WIDTH + t_coordinates.x] = m_color;
}

void Window::drawRectangle(Coordinates t_topLeft, Coordinates t_bottomRight)
{
    if(isClosed()) {
        return;
    }

    int xStart = 0;
    int xEnd = 0;
    if (t_topLeft.x - t_bottomRight.x < 0)
    {
        xStart = t_topLeft.x;
        xEnd = t_bottomRight.x;
    }
    else
    {
        xStart = t_bottomRight.x;
        xEnd = t_topLeft.x;
    }

    int yStart = 0;
    int yEnd = 0;
    if (t_topLeft.y - t_bottomRight.y < 0)
    {
        yStart = t_topLeft.y;
        yEnd = t_bottomRight.y;
    }
    else
    {
        yStart = t_bottomRight.y;
        yEnd = t_topLeft.y;
    }

    for (int col = xStart; col < xEnd; ++col)
    {
        for (int row = yStart; row < yEnd; ++row)
        {
            drawPixel({col, row});
        }
    }
}

void Window::drawLine(Coordinates t_start, Coordinates t_end)
{
    if(isClosed()) {
        return;
    }

    int totalSteps = abs(t_start.x - t_end.x) > abs(t_start.y - t_end.y) ? abs(t_start.x - t_end.x) : abs(t_start.y - t_end.y);

    float xStart = static_cast<float>(t_start.x);
    float yStart = static_cast<float>(t_start.y);

    float deltaXPerStep = static_cast<float>(t_end.x - t_start.x) / totalSteps;
    float deltaYPerStep = static_cast<float>(t_end.y - t_start.y) / totalSteps;

    for (int i = 0; i < totalSteps; ++i)
    {
        int drawX = static_cast<int>(xStart);
        int drawY = static_cast<int>(yStart);
        drawPixel({drawX, drawY});
        xStart += deltaXPerStep;
        yStart += deltaYPerStep;
    }
}

void Window::drawBackground()
{
    if(isClosed()) {
        return;
    }

    for (int col = 0; col < M_WIDTH; ++col)
    {
        for (int row = 0; row < M_HEIGHT; ++row)
        {
            drawPixel({col, row});
        }
    }
}

bool Window::isActive() const
{
    if ((SDL_GetWindowFlags(m_window) & SDL_WINDOW_MOUSE_FOCUS) && (SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS))
    {
        return true;
    }
    return false;
}

bool Window::isClosed() const
{
    return m_window == nullptr;
}

Uint32 Window::getWindowID() const
{
    return SDL_GetWindowID(m_window);
}

} // namespace paint