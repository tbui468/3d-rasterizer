#ifndef BUTTON_H
#define BUTTON_H

#include "Interactive.hpp"
#include "Window.hpp"
#include "Coordinates.hpp"

namespace paint {

class Button : public Interactive
{
private:
    Coordinates m_topLeftCorner{0, 0};
    int m_width{0};
    int m_height{0};
public:
    Button(Window* window, Coordinates topLeftCorner, int width, int height) : 
            Interactive(window), m_topLeftCorner(topLeftCorner), m_width(width), m_height(height) {};
    bool mouseHover(Window *activeWindow, Coordinates mousePosition);
    void setState(State newState);
    void update();
private:
    bool insideButton(Coordinates coordinates);

};

}//namespace paint

#endif //BUTTON_H