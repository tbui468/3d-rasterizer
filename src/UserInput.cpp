#include "UserInput.h"

//returns an vector of user inputs
//inputs are InputPair struct (defined in header file) 
std::vector<InputInfo>* UserInput::process_events()
{
    SDL_Event event;
    m_user_inputs->clear();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return m_user_inputs; //return empty input vector
        }
        else if (event.type == SDL_WINDOWEVENT) {
            switch(event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    m_user_inputs->push_back(InputInfo {WindowClose, event.window.windowID});
                break;
                default:
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                m_user_inputs->push_back(InputInfo {MouseLeft, 0});
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                m_user_inputs->push_back(InputInfo {MouseMiddle, 0});
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                m_user_inputs->push_back(InputInfo {MouseRight, 0});
        }
    }
    return m_user_inputs;
}

Coordinates UserInput::get_mouse_coordinates() const
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return Coordinates{x, y};
}