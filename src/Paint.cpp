//Pixel Art application
/*
Rewrite Grid class function getLowestValueCoordinate()
Create grid with a std::pair<GridObject, int>
*/

#include <iostream>
#include <memory>
#include <array>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Coordinates.hpp"
#include "Screen.hpp"
#include "UserInput.hpp"
#include "Button.hpp"
#include "Grid.hpp"
#include "Vertex.hpp"

using namespace paint;

static void updateAdjacentVertex(Vertex* currentVertex, Vertex* adjVertex) {
    if (adjVertex->type == VertexType::Unvisited || adjVertex->type == VertexType::End)
    {
        int oldAdjacentDis = adjVertex->minimumDistance;
        int newAdjacentDis = currentVertex->minimumDistance + 1;
        //if new distance is less than old dis, update distance, and set pointer
        if (newAdjacentDis < oldAdjacentDis)
        {
            adjVertex->minimumDistance = newAdjacentDis;
            adjVertex->previousVertex = currentVertex;
        }
    }
}


static bool insideGrid(int col, int row) {
    bool insideHorizontal = (0 <= col && col < 32);
    bool insideVertical = (0 <= row && row < 24);
    return (insideHorizontal && insideVertical);
}

int main()
//int main()
{
    if (Screen::initialize())
    {
        std::cout << "SDL initialized" << std::endl;
    }


    Grid grid(32, 24);
    for(int col = 0; col < 32; ++col) {
        for(int row = 0; row < 24; ++row) {
            grid.setVertexType(col, row, VertexType::Unvisited);
            grid.setVertexDistance(col, row, 10000);
        }
    }
    grid.setVertexType(0, 0, VertexType::Wall);
    grid.setVertexType(31, 0, VertexType::Wall);
    grid.setVertexType(0, 23, VertexType::Wall);
    grid.setVertexType(31, 23, VertexType::Wall);
    grid.setVertexType(0, 0, VertexType::Start);
    grid.setVertexType(31, 0, VertexType::End);

    grid.setVertexType(12, 5, VertexType::Wall);
    grid.setVertexType(12, 6, VertexType::Wall);
    grid.setVertexType(12, 7, VertexType::Wall);
    grid.setVertexType(12, 8, VertexType::Wall);
    grid.setVertexType(12, 9, VertexType::Wall);
    grid.setVertexType(12, 10, VertexType::Wall);

    grid.setVertexType(0, 12, VertexType::Wall);
    grid.setVertexType(1, 12, VertexType::Wall);
    grid.setVertexType(2, 12, VertexType::Wall);
    grid.setVertexType(3, 12, VertexType::Wall);
    grid.setVertexType(4, 12, VertexType::Wall);

    //obstacles
    for(int i = 0; i < 23; ++i) {
        grid.setVertexType(8, i, VertexType::Wall);
    }
    for(int i = 8; i < 24; ++i) {
        grid.setVertexType(16, i, VertexType::Wall);
    }
    for(int i = 0; i < 15; ++i) {
        grid.setVertexType(24, i, VertexType::Wall);
    }



    while(true) {
        //get next vertex
        Vertex* currentVertex = grid.getNextVertex();
        if(currentVertex->type == VertexType::Unvisited || currentVertex->type == VertexType::Start) {
            currentVertex->type = VertexType::Visited;
        }
        //exit loop if no Unvisited vertices remains or the next vertex is the end
        if(currentVertex == nullptr || currentVertex->type == VertexType::End) {
            break;
        }

        //calculate new values of adjacent vertices (check the four around it
        int col = currentVertex->coordinates.x;
        int row = currentVertex->coordinates.y;
        //check above
        if (insideGrid(col, row - 1))
        {
            Vertex *adjVertex = grid.getVertex(col, row - 1);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check below
        if (insideGrid(col, row + 1))
        {
            Vertex *adjVertex = grid.getVertex(col, row + 1);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check left
        if (insideGrid(col - 1, row))
        {
            Vertex *adjVertex = grid.getVertex(col - 1, row);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
        //check right
        if (insideGrid(col + 1, row))
        {
            Vertex *adjVertex = grid.getVertex(col + 1, row);
            updateAdjacentVertex(currentVertex, adjVertex);
        }
    }


    //windows
    Window mainWindow("Paint", 800, 600);
    mainWindow.drawBackground();
    mainWindow.setColor(200, 200, 255);
    mainWindow.drawBackground();
    Window colorWindow("Color", 300, 200);
    colorWindow.setColor(200, 255, 200);
    colorWindow.drawBackground();

    //buttons
    Button button(&mainWindow, {0, 0}, 200, 200);
    Button button3(&mainWindow, {500, 500}, 100, 100);
    Button button2(&colorWindow, {0, 0}, 100, 100);
    UserInput userinput;
    bool appOpen = true;
    while (appOpen)
    {
        std::vector<Inputs> inputs = userinput.processEvents(mainWindow, colorWindow);
        for (Inputs input : inputs)
        {
            switch (input)
            {
            case Inputs::MouseLeft:
            {
                break;
            }
            case Inputs::MouseRight:
            {
                break;
            }
            case Inputs::CloseColorWindow:
            {
                colorWindow.close();
                break;
            }
            case Inputs::CloseMainWindow:
            {
                mainWindow.close();
                appOpen = false;
                break;
            }
            case Inputs::CloseApplication:
            {
                appOpen = false;
                break;
            }
            default:
                break;
            }
        }

        //get currently active window
        Window *activeWindow = nullptr;
        if (mainWindow.isActive())
        {
            activeWindow = &mainWindow;
        }
        else if (colorWindow.isActive())
        {
            activeWindow = &colorWindow;
        }

        //update button states
        if (button.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button.setState(State::Hover);
        }
        else
        {
            button.setState(State::Idle);
        }
        if (button3.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button3.setState(State::Hover);
        }
        else
        {
            button3.setState(State::Idle);
        }

        //update button states
        if (button2.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button2.setState(State::Hover);
        }
        else
        {
            button2.setState(State::Idle);
        }

        button.update();
        button2.update();
        button3.update();

        //draw grid
        for (int col = 0; col < 32; ++col)
        {
            for (int row = 0; row < 24; ++row)
            {
                Vertex *v = grid.getVertex(col, row);
                switch (v->type)
                {
                case VertexType::Wall:
                    mainWindow.setColor(0, 0, 0);
                    break;
                case VertexType::Unvisited:
                    mainWindow.setColor(255, 255, 255);
                    break;
                case VertexType::Visited:
                    mainWindow.setColor(255, 255, 255);
                    break;
                case VertexType::Start:
                    mainWindow.setColor(150, 150, 255);
                    break;
                case VertexType::End:
                    mainWindow.setColor(100, 255, 100);
                    break;
                default:
                    mainWindow.setColor(255, 255, 255);
                    break;
                }

                mainWindow.drawRectangle({col * 25, row * 25}, {col * 25 + 25, row * 25 + 25});
                Vertex* v2 = grid.getVertex(col, row);
                mainWindow.setColor(255,0,0);
                if(v2->previousVertex == nullptr) {
                    mainWindow.drawPixel({col*25+12, row*25+12});
                } 
            }
        }

        //draw path from end to start
        Vertex* end = grid.getEnd();
        Vertex* current = end;
        mainWindow.setColor(255, 0, 0);
        while(current != nullptr) {
            //cuolor current Vertex
            if(current->type == VertexType::Visited){
                int xC = current->coordinates.x;
                int yC = current->coordinates.y;
                if(current->previousVertex == nullptr) {
                    mainWindow.setColor(100,100,255);
                }
                mainWindow.drawRectangle({xC*25, yC*25}, {xC*25+25, yC*25+25});
            }
            current = current->previousVertex;
        }
        
        

        mainWindow.setColor(150, 150, 150);
        //draw grid lines
        for (int col = 25; col < 800; col += 25)
        {
            mainWindow.drawLine({col, 0}, {col, 600});
        }
        for (int row = 25; row < 600; row += 25)
        {
            mainWindow.drawLine({0, row}, {800, row});
        }
        mainWindow.render();
        colorWindow.render();
    }

    colorWindow.close();
    mainWindow.close();
    Screen::close();

    std::cout << "SDL shutdown" << std::endl;
    return 0;
}