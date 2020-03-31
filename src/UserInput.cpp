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
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X1))
                m_user_inputs->push_back(InputInfo {MouseAltOne, 0});
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X2))
                m_user_inputs->push_back(InputInfo {MouseAltTwo, 0});
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if (event.wheel.y > 0)
                m_user_inputs->push_back(InputInfo {WheelUp, 0});
            if (event.wheel.y < 0)
                m_user_inputs->push_back(InputInfo {WheelDown, 0});
            if (event.wheel.x > 0)
                m_user_inputs->push_back(InputInfo {WheelRight,0 });
            if (event.wheel.x < 0)
                m_user_inputs->push_back(InputInfo {WheelLeft, 0});
        }
        else if (event.type == SDL_KEYDOWN)
        {
            int key = event.key.keysym.sym;
            if (key == SDLK_DOWN)
                m_user_inputs->push_back(InputInfo {KeyDown, 0});
            if (key == SDLK_UP)
                m_user_inputs->push_back(InputInfo {KeyUp, 0});
            if (key == SDLK_LEFT)
                m_user_inputs->push_back(InputInfo {KeyLeft, 0});
            if (key == SDLK_RIGHT)
                m_user_inputs->push_back(InputInfo {KeyRight, 0});
        }
    }
    return m_user_inputs;
}

Coordinates UserInput::get_mouse_coordinates()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return Coordinates{x, y};
}