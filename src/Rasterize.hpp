#ifndef RASTERIZE_H
#define RASTERIZE_H


#include "Math.hpp"

namespace paint {

template <typename T>
LinearCoefficients<typename T> getIntCoefficients(Vec2 start, Vec2 end) {
    LinearCoefficients<T> lc;
    lc.a = T(end.y) - T(start.y);
    lc.b = T(start.x) - T(end.x);
    lc.c = T(end.x) * T(start.y) - T(start.x) * T(end.y);

    return lc;
}


void drawFlatTop(Screen &screen, Vec2 vertices[3])
{
    //get each line coefficients (integers)
    LinearCoefficients<int>* lines[3]; //index: 0 - top line, 1 -left line, 2 - right line
    lines[0] = &getIntCoefficients<int>(vertices[0], vertices[1]);
    lines[1] = &getIntCoefficients<int>(vertices[1], vertices[2]);
    lines[2] = &getIntCoefficients<int>(vertices[2], vertices[0]);

    //assign top line to lines[0]
    for(unsigned int i = 0; i < 3; ++i) {
        if(lines[i]->a == 0) {
            LinearCoefficients<int>* horizontalLine = lines[i];
            lines[i] = lines[0];
            lines[0] = horizontalLine;
            break;
        }
    } 

    //get y0 (y value of one of the two points that form flat top of triangle)
    int y0 = int(lines[0]->c / lines[0]->b);
    //get y1 (y value of the lowest point of the flattop triangle)
    int y1 = y0;
    for(unsigned int i = 0; i < 3; ++i) {
        if(int(vertices[i].y) > y0) {
            y1 = int(vertices[i].y);
            break;
        }
    }

    //iterate from y0 to y1;
    for(int i = y0; i <= y1; ++i) {
        int x0 = int((lines[1]->b * float(i) - lines[1]->c)/lines[1]->a);
        int x1 = int((lines[2]->b * float(i) - lines[2]->c)/lines[2]->a);
        screen.drawLine(x0, i, x1, i);
    }
/*

    //get left and right vertices
    Vec2* left = &vertices[0];
    Vec2* right = &vertices[1];
    Vec2* bottom = &vertices[2];
    if(left->x > right->x) {
        left = &vertices[1];
        right = &vertices[0];
    }

    //get equations for left and right lines
    float yStart = left->y; //equivalent to right->y
    float yEnd = bottom->y;
    float xStart;
    float xEnd;

    bool leftVertical = false;
    bool rightVertical = false;
    float leftSlope;
    float leftIntercept;
    float rightSlope;
    float rightIntercept;

    if(bottom->x == left->x) {
        leftVertical = true;
        xStart = bottom->x;
    }else{ //get slope and intercept
        leftSlope = (bottom->y - left->y)/(bottom->x - left->x);
        leftIntercept = bottom->y - (leftSlope * bottom->x);
    }

    if(bottom->x == right->x) {
        rightVertical = true;
        xEnd = bottom->x;
    }else{ //get slope and intercept
        rightSlope = (bottom->y - right->y)/(bottom->x - right->x);
        rightIntercept = bottom->y - (rightSlope * bottom->x);
    }

    //render pixel loop
    float yCurrent = yStart;
    while(yCurrent < yEnd) {
        //set xStart and xEnd based on left and right lines
        //set xStart
        if(!leftVertical) {
            xStart = (yCurrent - leftIntercept)/leftSlope;
        }        
        //set xEnd
        if(!rightVertical) {
            xEnd = (yCurrent - rightIntercept)/rightSlope;
        }

        //loop from xStart to xEnd, filling in pixels
        float xCurrent = xStart;
        while(xCurrent < xEnd) {
            screen.putPixel(xCurrent, yCurrent);
            xCurrent +=1;
        }
        yCurrent += 1;
    }
    */
}

void drawFlatBottom(Screen &screen, Vec2 vertices[3])
{
    //get left and right vertices
    Vec2* top = &vertices[0];
    Vec2* left = &vertices[1];
    Vec2* right = &vertices[2];
    if(left->x > right->x) {
        left = &vertices[2];
        right = &vertices[1];
    }

    //get equations for left and right lines
    float yStart = top->y;
    float yEnd = left->y; //equivalent to right->y;
    float xStart;
    float xEnd;

    bool leftVertical = false;
    bool rightVertical = false;
    float leftSlope;
    float leftIntercept;
    float rightSlope;
    float rightIntercept;

    if(top->x == left->x) {
        leftVertical = true;
        xStart = top->x;
    }else{ //get slope and intercept
        leftSlope = (top->y - left->y)/(top->x - left->x);
        leftIntercept = top->y - (leftSlope * top->x);
    }

    if(top->x == right->x) {
        rightVertical = true;
        xEnd = top->x;
    }else{ //get slope and intercept
        rightSlope = (top->y - right->y)/(top->x - right->x);
        rightIntercept = top->y - (rightSlope * top->x);
    }

    //render pixel loop
    float yCurrent = yStart;
    while(yCurrent < yEnd) {
        //set xStart and xEnd based on left and right lines
        //set xStart
        if(!leftVertical) {
            xStart = (yCurrent - leftIntercept)/leftSlope;
        }        
        //set xEnd
        if(!rightVertical) {
            xEnd = (yCurrent - rightIntercept)/rightSlope;
        }

        //loop from xStart to xEnd, filling in pixels
        float xCurrent = xStart;
        while(xCurrent < xEnd) {
            screen.putPixel(xCurrent, yCurrent);
            xCurrent +=1;
        }
        yCurrent += 1;
    }
}

//
void drawTriangle(Screen& screen, Vec2 vertices[3]) {
    //first sort vertices into order based on y positions(smaller y is top, lower y is bottom)
    Vec2* top = &vertices[0];
    Vec2* mid = &vertices[1];
    Vec2* bot = &vertices[2];
    Vec2* swap;

    if(top->y > mid->y) {
        swap = top;
        top = mid;
        mid = swap;
    }
    if(mid->y > bot->y) {
        swap = mid;
        mid = bot;
        bot = swap;
    }
    if(top->y > mid->y) {
        swap = top;
        top = mid;
        mid = swap;
    }

    Vec2 sorted[3];
    sorted[0] = *top;
    sorted[1] = *mid;
    sorted[2] = *bot;

    if(int(top->y) == int(mid->y)) { //flaptop triangle
        drawFlatTop(screen, sorted);
    }else if(int(mid->y) == int(bot->y)) { //flatbottom triangle
        drawFlatBottom(screen, sorted);
    }else{ //split triangle into two
        Vec2 topTri[3];
        Vec2 botTri[3];
        if (top->x == bot->x)
        { //vertical line
            topTri[0] = *top;
            topTri[1] = *mid;
            topTri[2] = {top->x, mid->y};
            botTri[0] = *mid;
            botTri[1] = {top->x, mid->y};
            botTri[2] = *bot;
        }
        else
        { //not vertical line
            float slope = (top->y - bot->y)/(top->x - bot->x);
            float intercept = top->y - slope * top->x;
            Vec2 newMid = {(mid->y-intercept)/slope, mid->y};

            topTri[0] = *top;
            topTri[1] = *mid;
            topTri[2] = newMid;
            botTri[0] = *mid;
            botTri[1] = newMid;
            botTri[2] = *bot;
        }
        drawFlatTop(screen, botTri);
        drawFlatBottom(screen, topTri);
    }
}


}

#endif //RASTERIZE_H