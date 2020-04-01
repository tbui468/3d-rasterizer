#ifndef BUTTON_H
#define BUTTON_H

#include "../dependencies/SDL2/include/SDL.h"
#include "Coordinates.h"
#include "Screen.h"

enum ButtonState {Idle, Hover, Active};

class Button
{
private:
    SDL_Window* m_window;
    Coordinates m_topLeftCoordinates;
    int m_width;
    int m_height;
    uint32_t m_idleColor = 0x00000000;
    uint32_t m_activeColor = 0xffffffff;
    uint32_t m_hoverColor = 0x88888888;
    uint32_t m_color = m_idleColor;
    int m_state = ButtonState::Idle;
public:
    Button(SDL_Window* window, Coordinates coordinate, int width, int height) :
            m_window(window), m_topLeftCoordinates(coordinate), m_width(width), m_height(height) {};
    bool MouseHover(SDL_Window* activeWindow, Coordinates mouseLocation) {
        if(activeWindow == nullptr)
            return false;
        uint32_t windowID = SDL_GetWindowID(m_window);
        uint32_t activeWindowID = SDL_GetWindowID(activeWindow);
        if(windowID != activeWindowID)
            return false;
        bool insideDomain = mouseLocation.x > m_topLeftCoordinates.x && mouseLocation.x < m_topLeftCoordinates.x + m_width;
        bool insideRange = mouseLocation.y > m_topLeftCoordinates.y && mouseLocation.y < m_topLeftCoordinates.y + m_height;

        if(insideDomain && insideRange)
            return true;

        return false;
    }
    void ChangeState(ButtonState newState) {
        m_state = newState;
        switch(m_state) {
            case ButtonState::Idle:
                m_color = m_idleColor;
            break;
            case ButtonState::Hover:
                m_color = m_hoverColor;
            break;
            case ButtonState::Active:
                m_color = m_activeColor;
            break;
            default:
            break;
        }
    }
    void renderButton(Screen* screen) {
        screen->set_color(m_color);
        screen->DrawRectangle(m_topLeftCoordinates, Coordinates {m_topLeftCoordinates.x + m_width, m_topLeftCoordinates.y + m_height});
    }

};

#endif //BUTTON_H
