#ifndef MOUSE_H
#define MOUSE_H

#include "InputDevice.h"

class Mouse : public InputDevice {
private:
public:
    bool process_events() override;
};

#endif //MOUSE_H