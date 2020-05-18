#include "Screen.hpp"
#include <memory>
#include <assert.h>

namespace paint
{



Screen::Screen(int width, int height) : m_window(nullptr),
                                        m_renderer(nullptr),
                                        m_texture(nullptr),
                                        m_buffer(nullptr),
                                        m_color(0x000000f),
                                        SCREEN_HEIGHT(height),
                                        SCREEN_WIDTH(width)
{
    initialize();
}

bool Screen::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }


    m_window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_window == nullptr)
    {
        return false;
    }
    //create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        return false;
    }
    //create texture
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (m_texture == nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        return false;
    }

    m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(m_buffer, 0, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
    SDL_SetWindowBordered(m_window, SDL_TRUE);
    return true;
}


void Screen::setColor(Uint8 t_red, Uint8 t_green, Uint8 t_blue)
{
    m_color = t_red;
    m_color <<= 8;
    m_color += t_green;
    m_color <<= 8;
    m_color += t_blue;
    m_color <<= 8;
    m_color += 0xff;
}

void Screen::setColor(uint32_t color) {
    m_color = color;
}

void Screen::putPixel(int x, int y)
{
    if(x < 0 || x > 799)
        return;
    if(y < 0 || y > 599)
        return;
    m_buffer[y * SCREEN_WIDTH + x] = m_color;
}

void Screen::drawLine(float x0f, float y0f, float x1f, float y1f)
{
    /*BRESENHAM'S ALGORITHM*/
    int x0 = int(x0f);
    int y0 = int(y0f);
    int x1 = int(x1f);
    int y1 = int(y1f);

    int sx = x0 < x1 ? 1 : -1;  //chooses positive or negative increment for each iteration
    int sy = y0 < y1 ? 1 : -1; //same for y

    int dx = abs(x1 - x0); //find horizontal distance between endpoints
    int dy = -abs(y1 - y0); //find vertical distance between endpoints (but negative????)

    if (dy == 0)
    { //horizontal line
        while(true) {
            putPixel(x0, y0);
            if(x0 == x1)
                break;
            x0 += sx;
        }
    }
    else if (dx == 0)
    { //vertical line
        while(true) {
            putPixel(x0, y0);
            if(y0 == y1)
                break;
            y0 += sy;
        }
    }
    else
    {
        int err = dx + dy; //????Not sure what is happening here.  Initializing err

        while (true)
        {
            putPixel(x0, y0); //draw pixel at x0, y0
            if (x0 == x1 && y0 == y1) //leave loop if both points are on the same pixel
            {
                break;
            }
            int e2 = 2 * err; //what is this two doing??
            if (e2 > dy)
            {
                err += dy; //decrease by initial distance between y1 and y0
                x0 += sx; //increment by 1 closer to x1
            }
            if (e2 <= dx)
            {
                err += dx; //increase by initial distance between x1 and x0
                y0 += sy; //increment by 1 closer to y1
            }
        }
    }
}

//draw model(THis can be processed by GPU for better performance, such as using CUDA)
void Screen::drawPolygon(const Vertex &vertexBuffer, const Mat4 &transformation)
{
    assert(vertexBuffer.indices.size() == vertexBuffer.cullFlags.size());


    //apply transformation to model and load into new vertex
    unsigned int vertexBufferSize = vertexBuffer.positions.size();
    std::vector<Vec3> transformedVB;
    for (const Vec3 &v3 : vertexBuffer.positions)
    {
        Vec4 v4 = {v3.x, v3.y, v3.z, 1.0f};
        v4 = transformation * v4;
        if(abs(v4.w) > 0.01f) //geometric clipping will take care of negative and 0 w'.  So this line won't be necessary
            transformedVB.emplace_back(v4.x/v4.w, v4.y/v4.w, v4.z/v4.w); //perspective division
        else
            transformedVB.emplace_back(0.0f, 0.0f, 0.0f); //perspective division
    }

    //draw each transformed vertex using index buffer
    char color = 10;
    for(unsigned int k = 0; k < vertexBuffer.indices.size(); ++k) 
    {
        const Index& i = vertexBuffer.indices.at(k);
        //if cullFlag is true, continue loop
        if(vertexBuffer.cullFlags.at(k))
            continue;
        assert(i.x < vertexBufferSize);
        assert(i.y < vertexBufferSize);
        assert(i.z < vertexBufferSize);
        /*
        float scale = transformedVB.at(i.x).z; //should be between 0 and 1 if inside screen
        scale *= scale;
        scale = 1.0f - scale;
        scale *= 255.0f;
        setColor(char(scale), char(scale), char(scale));
        drawLine(transformedVB.at(i.x).x, transformedVB.at(i.x).y, transformedVB.at(i.y).x, transformedVB.at(i.y).y);
        drawLine(transformedVB.at(i.y).x, transformedVB.at(i.y).y, transformedVB.at(i.z).x, transformedVB.at(i.z).y);
        drawLine(transformedVB.at(i.z).x, transformedVB.at(i.z).y, transformedVB.at(i.x).x, transformedVB.at(i.x).y);*/


        Vec2 vec[3];
        vec[0] = {transformedVB.at(i.x).x, transformedVB.at(i.x).y};
        vec[1] = {transformedVB.at(i.y).x, transformedVB.at(i.y).y};
        vec[2] = {transformedVB.at(i.z).x, transformedVB.at(i.z).y};
        color += 20;
        setColor(color, color, color);
        fillTriangle(vec[0], vec[1], vec[2]);
    }
}



void Screen::fillTriangle(const Vec2 &vec1, const Vec2 &vec2, const Vec2 &vec3)
{
    const Vec2 *top = &vec1;
    const Vec2 *mid = &vec2;
    const Vec2 *bot = &vec3;

    //check to swap top and mid
    if(top->y > mid->y) {
        std::swap(top, mid);
    }

    //check to swap mid and bot
    if(mid->y > bot->y) {
        std::swap(mid, bot);

        //check if top and mid need to be swapped after mid/bottom swap
        if(top->y > mid->y) {
            std::swap(top, mid);
        }
    }

    if(int(top->y) == int(mid->y)) { //flap top
        fillFlatTopTriangle(*top, *mid, *bot);
    }else if(int(mid->y) == int(bot->y)) { //flat bottom
        fillFlatBottomTriangle(*top, *mid, *bot);
    }else{ //split triangle into flat/bottom triangles
        float a = top->y - bot->y;
        float b = bot->x - top->x;
        float c = top->x * bot->y - bot->x * top->y;
        Vec2 newMid;
        if(abs(a) > 0.01f) 
            newMid = {(-b * mid->y - c) / a, mid->y};
        else //vertical line (approx.) between top and bottom
            newMid = {top->x, mid->y};
        fillFlatBottomTriangle(*top, *mid, newMid);
        fillFlatTopTriangle(*mid, newMid, *bot);
    }

}

void Screen::fillFlatBottomTriangle(const Vec2& top, const Vec2& bot1, const Vec2& bot2) {
    const Vec2* left = &bot1;
    const Vec2* right = &bot2;
    if(left->x > right->x) {
        std::swap(left, right);
    }

    //left line
    int y0l = int(top.y);
    int x0l = int(top.x);
    int y1l = int(left->y);
    int x1l = int(left->x);
    int sxl = x0l < x1l ? 1 : -1;
    int syl = y0l < y1l ? 1 : -1;
    int dxl = abs(x1l - x0l);
    int dyl = -abs(y1l - y0l);
    int errl = dxl + dyl;

    //right line
    int y0r = int(top.y);
    int x0r = int(top.x);
    int y1r = int(right->y);
    int x1r = int(right->x);
    int sxr = x0r < x1r ? 1 : -1;
    int syr = y0r < y1r ? 1 : -1;
    int dxr = abs(x1r - x0r);
    int dyr = -abs(y1r - y0r);
    int errr = dxr + dyr;

    while (true)
    {
        drawLine(x0l, y0l, x0r, y0r);
        if (y0r == y1l)
        {
            break;
        }
        //loop left until y0l is incremented by 1
        while(true) {
            if(x0l == x1l && y0l == y1l)
                break;
            int e2 = errl * 2; 
            if(e2 >= dyl) {
                errl += dyl;
                x0l += sxl;
            }
            if(e2 <= dxl){
                errl += dxl;
                y0l += syl;
                break;
            }
        }
        //loop right until y0r is incremented by 1 (and equal to y0l)
        while(true) {
            if(x0r == x1r && y0r == y1r)
                break;
            int e2 = errr * 2; 
            if(e2 >= dyr) {
                errr += dyr;
                x0r += sxr;
            }
            if(e2 <= dxr){
                errr += dxr;
                y0r += syr;
                break;
            }
        }
    }
}

void Screen::fillFlatTopTriangle(const Vec2 &top1, const Vec2 &top2, const Vec2 &bot)
{
    const Vec2 *left = &top1;
    const Vec2 *right = &top2;
    if (left->x > right->x)
    {
        std::swap(left, right);
    }


    //left line
    int y0l = int(left->y);
    int x0l = int(left->x);
    int y1l = int(bot.y);
    int x1l = int(bot.x);
    int sxl = x0l < x1l ? 1 : -1;
    int syl = y0l < y1l ? 1 : -1;
    int dxl = abs(x1l - x0l);
    int dyl = -abs(y1l - y0l);
    int errl = dxl + dyl;

    //right line
    int y0r = int(right->y);
    int x0r = int(right->x);
    int y1r = int(bot.y);
    int x1r = int(bot.x);
    int sxr = x0r < x1r ? 1 : -1;
    int syr = y0r < y1r ? 1 : -1;
    int dxr = abs(x1r - x0r);
    int dyr = -abs(y1r - y0r);
    int errr = dxr + dyr;

    while (true)
    {
        drawLine(x0l, y0l, x0r, y0r);
        if (y0r == y1l)
        {
            break;
        }
        //loop left until y0l is incremented by 1
        while(true) {
            if(x0l == x1l && y0l == y1l)
                break;
            int e2 = errl * 2; 
            if(e2 >= dyl) {
                errl += dyl;
                x0l += sxl;
            }
            if(e2 <= dxl){
                errl += dxl;
                y0l += syl;
                break;
            }
        }
        //loop right until y0r is incremented by 1 (and equal to y0l)
        while(true) {
            if(x0r == x1r && y0r == y1r)
                break;
            int e2 = errr * 2; 
            if(e2 >= dyr) {
                errr += dyr;
                x0r += sxr;
            }
            if(e2 <= dxr){
                errr += dxr;
                y0r += syr;
                break;
            }
        }
    }

}

void Screen::render()
{
    SDL_UpdateTexture(m_texture, nullptr, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Screen::clear()
{
    for (int col = 0; col < SCREEN_WIDTH; ++col)
    {
        for (int row = 0; row < SCREEN_HEIGHT; ++row)
        {
            putPixel(col, row);
        }
    }
}

//fill m_inputs with events that occurred that frame
void Screen::processEvents()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    SDL_Event event;
    m_inputs.clear();

    if (state[SDL_SCANCODE_W])
        m_inputs.push_back(Input::Forward);
    if (state[SDL_SCANCODE_S])
        m_inputs.push_back(Input::Backward);
    if (state[SDL_SCANCODE_E])
        m_inputs.push_back(Input::PeekRight);
    if (state[SDL_SCANCODE_Q])
        m_inputs.push_back(Input::PeekLeft);
    if (state[SDL_SCANCODE_A])
        m_inputs.push_back(Input::StrafeLeft);
    if (state[SDL_SCANCODE_D])
        m_inputs.push_back(Input::StrafeRight);
    if (state[SDL_SCANCODE_Z])
        m_inputs.push_back(Input::ZoomIn);
    if (state[SDL_SCANCODE_X])
        m_inputs.push_back(Input::ZoomOut);
    if (state[SDL_SCANCODE_UP])
        m_inputs.push_back(Input::CameraUp);
    if (state[SDL_SCANCODE_DOWN])
        m_inputs.push_back(Input::CameraDown);
    if (state[SDL_SCANCODE_LEFT])
        m_inputs.push_back(Input::CameraLeft);
    if (state[SDL_SCANCODE_RIGHT])
        m_inputs.push_back(Input::CameraRight);
    if (state[SDL_SCANCODE_COMMA])
        m_inputs.push_back(Input::CameraRotateCW);
    if (state[SDL_SCANCODE_PERIOD])
        m_inputs.push_back(Input::CameraRotateCCW);
    if (state[SDL_SCANCODE_SEMICOLON])
        m_inputs.push_back(Input::CameraZoomIn);
    if (state[SDL_SCANCODE_APOSTROPHE])
        m_inputs.push_back(Input::CameraZoomOut);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_inputs.push_back(Input::Quit);
        }
        else if (event.type == SDL_KEYDOWN)
        { /*
            int key = event.key.keysym.sym;
            if (key == SDLK_a)
                m_inputs.push_back(Input::Left);
            if (key == SDLK_d)
                m_inputs.push_back(Input::Right);
            if (key == SDLK_s)
                m_inputs.push_back(Input::Down);
            if (key == SDLK_w)
                m_inputs.push_back(Input::Up);
            if (key == SDLK_q)
                m_inputs.push_back(Input::Backward);
            if (key == SDLK_e)
                m_inputs.push_back(Input::Forward);*/
        }
    }
}

//removes and returns next user input
Input Screen::getNextEvent()
{
    assert(hasEvents());
    Input ret = m_inputs.back();
    m_inputs.pop_back();
    return ret;
}

void Screen::close()
{
    delete[] m_buffer;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_buffer = nullptr;
    m_texture = nullptr;
    m_renderer = nullptr;
    m_window = nullptr;
    SDL_Quit();
}

} // namespace paint
