#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include "Coordinates.h"
#include "../dependencies/SDL2/include/SDL.h"

enum Inputs {MouseLeft = 0, MouseMiddle, MouseRight, MouseAltOne, MouseAltTwo, WheelUp, WheelDown, WheelLeft, WheelRight,
                KeyUp, KeyDown, KeyRight, KeyLeft, WindowClose};

//return a input information.  { enum Inputs, and optional uint32_t data for WindowClose event}
struct InputInfo {
    int inputType;
    uint32_t optionalData;
};


class UserInput {
private:
    std::vector<InputInfo>* m_user_inputs;
public:
    UserInput() : m_user_inputs(new std::vector<InputInfo>) {};
    std::vector<InputInfo>* process_events();
    ~UserInput() {delete m_user_inputs;};
    Coordinates get_mouse_coordinates();
};

#endif //USERINPUT_H