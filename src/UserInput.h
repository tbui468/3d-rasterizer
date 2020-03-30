#ifndef USERINPUT_H
#define USERINPUT_H

#include <optional>
#include <vector>
#include "Coordinates.h"

enum Inputs {MouseLeft = 0, MouseMiddle, MouseRight, MouseAltOne, MouseAltTwo, WheelUp, WheelDown, WheelLeft, WheelRight,
                KeyUp, KeyDown, KeyRight, KeyLeft, WindowClose};


class UserInput {
private:
    std::vector<int>* m_user_inputs;
public:
    UserInput() : m_user_inputs(new std::vector<int>) {};
    std::optional<std::vector<int>*> process_events();
    ~UserInput() {delete m_user_inputs;};
    Coordinates get_mouse_coordinates();
};

#endif //USERINPUT_H