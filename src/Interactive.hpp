#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include "Window.hpp"

namespace paint {


enum State {Idle, Active, Hover};

class Interactive
{
public:
    Interactive(Window *window) : m_window(window) {};
    Window *getWindow() { return m_window; };
    State getState() { return m_state; };

public:
    virtual bool mouseHover(Window *activeWindow, Coordinates mousePosition) = 0;;
    virtual void setState(State newState) = 0;
    virtual void update() = 0;

protected:
    Window *m_window{nullptr};
    State m_state{State::Idle};
    Uint32 m_color{0x00000000};
};

} //namespace paint

#endif //INTERACTIVE_H