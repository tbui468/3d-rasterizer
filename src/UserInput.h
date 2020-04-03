#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include "Coordinates.h"
//#include "../dependencies/SDL2/include/SDL.h"
#include "SDL.h"

enum Inputs {MouseLeft = 0, MouseMiddle, MouseRight, WindowClose, MainWindowClose, ColorWindowClose};

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
    virtual ~UserInput() {delete m_user_inputs;};
    Coordinates get_mouse_coordinates() const;
};

#endif //USERINPUT_H