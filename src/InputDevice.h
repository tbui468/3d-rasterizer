#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

class InputDevice {
private:
public:
    virtual bool process_events() = 0;
};

#endif //INPUTDEVICE_H