#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Coordinates.h"

class Screen
{
private:
    SDL_Window* m_window {nullptr};
    SDL_Window* m_window2 {nullptr}; //rename later to colorPaletteWindow once button objects are complete
    SDL_Renderer* m_renderer {nullptr};
    SDL_Texture* m_texture {nullptr};
    uint32_t* m_buffer {nullptr};
    uint32_t m_color {0x00000000};
    const int SCREEN_WIDTH {0};
    const int SCREEN_HEIGHT {0};
public:
    Screen(int t_width, int t_height): SCREEN_WIDTH(t_width), SCREEN_HEIGHT(t_height) {};
    bool init();
    void updateScreen();
    bool close();
    bool closeWindow(uint32_t t_id);
    void setColor(uint8_t t_red, uint8_t t_green, uint8_t t_blue);
    void setColor(uint32_t);
    void drawBackground();
    void drawPixel(int t_xCoordinate, int t_yCoordinate);
    void drawRectangle(Coordinates t_topLeft, Coordinates t_bottomRight);
    SDL_Window* getActiveWindow();
    SDL_Window* getMainWindow() const {return m_window;}; //do i need this?
    SDL_Window* getColorWindow() const {return m_window2;};// do i need this?
    void closeWindow(SDL_Window* t_window); //similar function above.  Need to 
};

#endif //SCREEN_H