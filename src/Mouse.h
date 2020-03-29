#ifndef MOUSE_H
#define MOUSE_H

#include "InputDevice.h"

enum MouseInputs {button_left = 0, button_middle, button_right, button_one, button_two, wheel_up, wheel_down, wheel_left, wheel_right};

struct MouseCoordinates {
    int x;
    int y;
};

class Mouse : public InputDevice {
private:
public:
    std::optional<std::vector<int>*> process_events() override;
    MouseCoordinates get_mouse_coordinates();
};

#endif //MOUSE_H