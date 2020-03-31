#ifndef BUTTON_H
#define BUTTON_H

#include "../dependencies/SDL2/include/SDL.h"
#include "Coordinates.h"
#include "Screen.h"

class Button
{
private:
    Screen* m_screen;
    SDL_Window* m_window;
    Coordinates m_topLeftCoordinates;
    int m_width;
    int m_height;
    enum State {Idle = 0, Active, Hover};
    uint32_t m_idleColor;
    uint32_t m_activeColor;
    uint32_t m_hoverColor;
    uint32_t m_color;
public:
    Button(Screen* screen, SDL_Window* window, Coordinates coordinate, int width, int height, uint32_t idleColor, uint32_t activeColor,
            uint32_t m_hoverColor, uint32_t m_color): 
            m_screen(screen), m_window(window), m_topLeftCoordinates(coordinate), m_width(width), m_height(height),
            m_idleColor(0x00000000), m_activeColor(0x00000000), m_hoverColor(0xffffffff), m_color(m_idleColor) {};
    bool MouseHover(SDL_Window* window, Coordinates mouseLocation) {
        uint32_t windowID = SDL_GetWindowID(m_window);
        uint32_t activeWindowID = SDL_GetWindowID(window);
        if(windowID != activeWindowID)
            return false;
        bool insideDomain = mouseLocation.x > m_topLeftCoordinates.x && mouseLocation.x < m_topLeftCoordinates.x + m_width;
        bool insideRange = mouseLocation.y > m_topLeftCoordinates.y && mouseLocation.y < m_topLeftCoordinates.y + m_height;

        if(insideDomain && insideRange)
            return true;

        return false;
    }
    void renderButton() {
        m_screen->set_color(m_color);
        m_screen->DrawRectangle(m_topLeftCoordinates, Coordinates {m_topLeftCoordinates.x + m_width, m_topLeftCoordinates.y + m_height});
    }

};

#endif //BUTTON_H
