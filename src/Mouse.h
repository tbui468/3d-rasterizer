#ifndef MOUSE_H
#define MOUSE_H

#include "InputDevice.h"

struct MouseCoordinates {
    int x;
    int y;
};

class Mouse : public InputDevice {
private:
public:
    bool process_events() override;
    MouseCoordinates get_mouse_coordinates();
};

#endif //MOUSE_H