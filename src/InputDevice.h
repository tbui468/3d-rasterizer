#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <optional>
#include <vector>

class InputDevice {
protected:
    std::vector<int>* m_user_inputs;
public:
    InputDevice() : m_user_inputs(new std::vector<int>) {};
    virtual ~InputDevice() {delete m_user_inputs;};
    virtual std::optional<std::vector<int>*> process_events() = 0;
};

#endif //INPUTDEVICE_H