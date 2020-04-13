#include "Button.hpp"

namespace paint{ 

bool Button::mouseHover(Window *activeWindow, Coordinates mousePosition)
{
    if(activeWindow == nullptr)
        return false;
    //check if active window is equal to m_window
    bool onActiveWindow = false;
    Window *myWindow = getWindow();
    if(!myWindow->isClosed() && !activeWindow->isClosed()) {
        onActiveWindow = (myWindow == activeWindow);
    }

    //check if mouse is inside button area
    bool insideButtonArea = insideButton(mousePosition);

    return onActiveWindow && insideButtonArea;
}

void Button::setState(State newState)
{
    m_state = newState;
}

//updates color information in window buffer
void Button::update()
{
    State currentState = getState();
    switch (currentState)
    {
    case State::Idle:
        m_color = 0x555555ff;
        break;
    case State::Active:
        m_color = 0x000000ff;
    case State::Hover:
        m_color = 0xaaaaaaff;
        break;
    default:
        m_color = 0x000000ff;
        break;
    }
    Window *myWindow = getWindow();
    if (!myWindow->isClosed())
    {
        myWindow->setColor(m_color);
        myWindow->drawRectangle(m_topLeftCorner, {m_topLeftCorner.x + m_width, m_topLeftCorner.y + m_height});
    }
}

bool Button::insideButton(Coordinates coordinates)
{
    bool insideHorizontal = false;
    if (coordinates.x > m_topLeftCorner.x && coordinates.x < (m_topLeftCorner.x + m_width))
    {
        insideHorizontal = true;
    }

    bool insideVertical = false;
    if (coordinates.y > m_topLeftCorner.y && coordinates.y < (m_topLeftCorner.y + m_height))
    {
        insideVertical = true;
    }

    return insideHorizontal && insideVertical;
}

} //namespace paint