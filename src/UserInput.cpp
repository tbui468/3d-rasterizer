#include "UserInput.hpp"

//returns an vector of user inputs
//inputs are InputPair struct (defined in header file) 
const std::vector<Inputs>& UserInput::processEvents()
{
    SDL_Event event;
    m_user_inputs.clear();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_user_inputs.push_back(Inputs::CloseMainWindow);
        }
        else if (event.type == SDL_WINDOWEVENT) {
            switch(event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    m_user_inputs.push_back(Inputs::CloseColorWindow);
                break;
                default:
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                m_user_inputs.push_back(Inputs::MouseLeft);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                m_user_inputs.push_back(Inputs::MouseRight);
        }
    }
    return m_user_inputs;
}

Coordinates UserInput::getMouseCoordinates() const
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return Coordinates{x, y};
}