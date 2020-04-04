#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include "Coordinates.hpp"
#include "SDL.h"

enum Inputs {MouseLeft = 0, MouseRight, CloseMainWindow, CloseColorWindow};


class UserInput {
private:
    std::vector<Inputs> m_user_inputs {};
public:
    const std::vector<Inputs>& processEvents();
    Coordinates getMouseCoordinates() const;
};

#endif //USERINPUT_H