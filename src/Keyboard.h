#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputDevice.h"

class Keyboard: public InputDevice {
private:
public:
    std::optional<std::vector<int>*> process_events() override;
};

#endif //KEYBOARD_H