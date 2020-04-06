#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include "Coordinates.hpp"
#include "SDL.h"
#include "Window.hpp"

namespace paint
{

enum Inputs
{
    MouseLeft = 0,
    MouseRight,
    CloseMainWindow,
    CloseColorWindow,
    CloseApplication
};

class UserInput
{
private:
    std::vector<Inputs> m_user_inputs{};

public:
    const std::vector<Inputs> &processEvents(const Window& window1, const Window& window2);
    Coordinates getMouseCoordinates() const;
};

} // namespace paint

#endif //USERINPUT_H