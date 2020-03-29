#include "UserInput.h"
#include "../dependencies/SDL2/include/SDL.h"

std::optional<std::vector<int>*> UserInput::process_events()
{
    SDL_Event event;
    m_user_inputs->clear();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return std::nullopt;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                m_user_inputs->push_back(Inputs::MouseLeft);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                m_user_inputs->push_back(Inputs::MouseMiddle);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                m_user_inputs->push_back(Inputs::MouseRight);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X1))
                m_user_inputs->push_back(Inputs::MouseAltOne);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X2))
                m_user_inputs->push_back(Inputs::MouseAltTwo);
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if (event.wheel.y > 0)
                m_user_inputs->push_back(Inputs::WheelUp);
            if (event.wheel.y < 0)
                m_user_inputs->push_back(Inputs::WheelDown);
            if (event.wheel.x > 0)
                m_user_inputs->push_back(Inputs::WheelRight);
            if (event.wheel.x < 0)
                m_user_inputs->push_back(Inputs::WheelLeft);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            int key = event.key.keysym.sym;
            if (key == SDLK_DOWN)
                m_user_inputs->push_back(Inputs::KeyDown);
            if (key == SDLK_UP)
                m_user_inputs->push_back(Inputs::KeyUp);
            if (key == SDLK_LEFT)
                m_user_inputs->push_back(Inputs::KeyLeft);
            if (key == SDLK_RIGHT)
                m_user_inputs->push_back(Inputs::KeyRight);
        }
    }
    return m_user_inputs;
}

MouseCoordinates UserInput::get_mouse_coordinates()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return MouseCoordinates{x, y};
}