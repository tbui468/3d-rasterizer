//Pixel Art application
/*
FEATURES Deadline: April 5 by midnight
**********
8 canvas tabs
    -click to add new tabs (like in a web browser)
    -play/stop button will scroll through the tabs to animate
8 quick colors
    -eight different quick select colors
    -click customize to open subscreen to customize the eight colors
    -choose from a color from color gradient or input hex/rgb (no alpha)
4 quick brushes
    -four quick select brushes
    -click customize to open subscreen to customize four brushes
    -customize shape (square, circle, diamond) and size (horizontal and vertical scale)
4 special brush options from main menu 
    -regular brush
    -erase brush
    -color picker
    -fill all similar colors

SCreen size 800 x 600
submenu size 400 x 300 (1/4 the size)
Canvas size:  ~512 x 512  //scale is 32x32
Menu Bar size: ~300 x 600
default background (blue checkered similar to Cobalt blue)
Default frame color (darker blue similar to Cobalt blue theme)
Highlights: yellow, orange, red, purple, green (Cobalt theme)
    - mouse hover over pixel will highlight with yellow
    - other highlights

Extra features
***************
Save image as a .png strip
Load images


THURSDAY & FRIDAY
*************************
Out of focus window button is still reacting to mouse.  Is this okay???

SATURDAY
******************
Brush buttons and customization

SUNDAY
*******************
regular, erase, picker, fill
*/

#include <iostream>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "../dependencies/SDL2/include/SDL.h"
#include "Coordinates.h"
#include "Screen.h"
#include "UserInput.h"
#include "Button.h"

//initialize Paint program
void Initialize()
{
}

//main will loop this function
//process user interaction with GUI and display on screen
void ProcessUserInputs()
{
}

//close Paint program
void Close()
{
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    /***************************/

    Screen *screen = new Screen(800, 600);
    screen->init();
    screen->set_color(200, 255, 200);
    screen->draw_background();
    screen->update_screen();
    Button button(screen->GetMainWindow(), Coordinates {0,0}, 100,50);
    UserInput *userInput = new UserInput();
    bool runLoop = true;
    while (runLoop)
    {
        std::vector<InputInfo>* inputs = userInput->process_events();
        for (unsigned int i = 0; i < inputs->size(); ++i)
        {
            InputInfo input = inputs->at(i);
            switch (input.inputType)
            {
            case Inputs::WindowClose:
            {
                std::cout << "close window event" << std::endl;
                int windowID = input.optionalData;
                runLoop = !(screen->close_window(windowID));
                break;
            }
            case Inputs::MouseLeft:
                screen->set_color(0, 55, 25);
                break;
            case Inputs::MouseRight:
                screen->set_color(0, 0, 0);
                break;
            default:
                break;
            }
        }
        if(button.MouseHover(screen->GetActiveWindow(), userInput->get_mouse_coordinates())) {
            button.ChangeState(ButtonState::Hover);
        }else{
            button.ChangeState(ButtonState::Idle);
        }
        

        screen->set_color(200,255,200);
        screen->draw_background();
        button.renderButton(screen); 
        screen->update_screen();
    }
    screen->close();
    /******************************/
    SDL_Quit();
    std::cout << "Program ended normally" << std::endl;
    return 0;
}