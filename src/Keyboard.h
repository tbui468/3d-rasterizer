#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputDevice.h"

class Keyboard: public InputDevice {
private:
public:
    bool process_events() override;

};

#endif //KEYBOARD_H