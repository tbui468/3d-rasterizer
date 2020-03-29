#include "Mouse.h"
#include "../dependencies/SDL2/include/SDL.h"

std::optional<std::vector<int> *> Mouse::process_events()
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
                m_user_inputs->push_back(MouseInputs::button_left);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                m_user_inputs->push_back(MouseInputs::button_middle);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                m_user_inputs->push_back(MouseInputs::button_right);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X1))
                m_user_inputs->push_back(MouseInputs::button_one);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X2))
                m_user_inputs->push_back(MouseInputs::button_two);
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if(event.wheel.y > 0)
                m_user_inputs->push_back(MouseInputs::wheel_up);
            if(event.wheel.y < 0)
                m_user_inputs->push_back(MouseInputs::wheel_down);
            if(event.wheel.x > 0)
                m_user_inputs->push_back(MouseInputs::wheel_right);
            if(event.wheel.x < 0)
                m_user_inputs->push_back(MouseInputs::wheel_left);
        }
    }
    return m_user_inputs;
}

MouseCoordinates Mouse::get_mouse_coordinates()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return MouseCoordinates{x, y};
}