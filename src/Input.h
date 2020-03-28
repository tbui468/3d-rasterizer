//Make interface called InputDevice, that is inherited by mouse and keyboard objects
//Make this an interface that mouse and keyboard inherit from
//Public functions:
//get_inputs() returns a list of use inputs
//


#ifndef INPUT_H
#define INPUT_H

class Input
{
private:
public:
    Input();
    bool process_events();
};

#endif //INPUT_H