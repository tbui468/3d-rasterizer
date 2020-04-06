#include "UserInput.hpp"
#include <iostream>

namespace paint
{

//returns an vector of user inputs
//inputs are InputPair struct (defined in header file)
const std::vector<Inputs> &UserInput::processEvents(const Window& window1, const Window& window2)
{
    SDL_Event event;
    m_user_inputs.clear();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_user_inputs.push_back(Inputs::CloseApplication);
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
            {
                Uint32 windowID = event.window.windowID;
                Uint32 mainWindowID = window1.getWindowID();
                Uint32 colorWindowID = window2.getWindowID();

                if (windowID == mainWindowID)
                    m_user_inputs.push_back(Inputs::CloseMainWindow);
                if (windowID == colorWindowID)
                    m_user_inputs.push_back(Inputs::CloseColorWindow);
                break;
            }
            default:
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                m_user_inputs.push_back(Inputs::MouseLeft);
                std::cout << "SDL_BUTTON_LEFT" << std::endl;
            }
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
            {
                m_user_inputs.push_back(Inputs::MouseRight);
                std::cout << "SDL_BUTTON_RIGHT" << std::endl;
            }
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

} // namespace paint