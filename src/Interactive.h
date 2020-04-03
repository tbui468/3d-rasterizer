#ifndef INTERACTIVE_H
#define INTERACTIVE_H

class Interactive
{
public:
    static enum State = {Idle, Active, Hover};

public:
    bool MouseHover(SDL_Window *activeWindow, Coordinates mousePosition);
    void ChangeState(State newState);
    void Render();
};

#endif //INTERACTIVE_H