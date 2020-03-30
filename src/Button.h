#ifndef BUTTON_H
#define BUTTON_H

#include "../dependencies/SDL2/include/SDL.h"
#include "Coordinates.h"

class Button
{
private:
    Coordinates m_topLeftCoordinates;
    int m_width;
    int m_height;
    uint32_t m_color;
public:
    Button(Coordinates coordinate, int width, int height, uint32_t color): 
            m_topLeftCoordinates(coordinate), m_width(width), m_height(height), m_color(color) {};
    virtual int Activate() = 0;
    virtual int Deactivate() = 0;
};

#endif //BUTTON_H
