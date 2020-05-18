#include "Screen.hpp"
#include <memory>
#include <assert.h>

namespace paint
{



Screen::Screen(int width, int height) : m_window(nullptr),
                                        m_renderer(nullptr),
                                        m_texture(nullptr),
                                        m_buffer(nullptr),
                                        m_zBuffer(nullptr),
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

    m_zBuffer = new int[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(m_zBuffer, 0, sizeof(float) * SCREEN_WIDTH * SCREEN_HEIGHT);

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

void Screen::putPixel(int x, int y, int z)
{
    if(x < 0 || x > 799)
        return;
    if(y < 0 || y > 599)
        return;

    int index = y * SCREEN_WIDTH + x;
    //check z-buffer and u
    if(z < m_zBuffer[index]) {
//    if(true){
        m_zBuffer[index] = z;
        m_buffer[index] = m_color;
    }
}

void Screen::drawLine(int x0, int y0, int z0, int x1, int y1, int z1)
{
    /*BRESENHAM'S ALGORITHM*/

    int sx = x0 < x1 ? 1 : -1;  //chooses positive or negative increment for each iteration
    int sy = y0 < y1 ? 1 : -1; //same for y
    int sz = z0 < z1 ? 1 : -1;

    int dx = abs(x1 - x0); //find horizontal distance between endpoints
    int dy = -abs(y1 - y0); //find vertical distance between endpoints (but negative????)
    int dz = -abs(z1 - z0);

    if (dy == 0)
    { //horizontal line (also used for rasterizing triangles)
        int err = dx + dz;
        while(true) {
            putPixel(x0, y0, z0);
            if(x0 == x1 && z0 == z1)
                break;
            int e2 = 2 * err;
            if(e2 >= dz) {
                err += dz;
                x0 += sx;
            }
            if(e2 <= dx) {
                err += dx;
                z0 += sz;
            }
        }
    }/*
    else if (dx == 0)
    { //vertical line (NOT USED NOW)
        while(true) {
            putPixel(x0, y0, 0.0f);
            if(y0 == y1)
                break;
            y0 += sy;
        }
    }
    else
    {
        int err = dx + dy; //????Not sure what is happening here.  Initializing err (NOT USED NOW)

        while (true)
        {
            putPixel(x0, y0, 0.0f); //draw pixel at x0, y0
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
    }*/
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


        Vec3 vec[3];
        vec[0] = {transformedVB.at(i.x).x, transformedVB.at(i.x).y, transformedVB.at(i.x).z};
        vec[1] = {transformedVB.at(i.y).x, transformedVB.at(i.y).y, transformedVB.at(i.y).z};
        vec[2] = {transformedVB.at(i.z).x, transformedVB.at(i.z).y, transformedVB.at(i.z).z};
        color += 20;
        setColor(color, color, color);
        fillTriangle(vec[0], vec[1], vec[2]);
    }
}



void Screen::fillTriangle(const Vec3 &vec1, const Vec3 &vec2, const Vec3 &vec3)
{
    const Vec3 *top = &vec1;
    const Vec3 *mid = &vec2;
    const Vec3 *bot = &vec3;

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
        const Vec3* left = top;
        const Vec3* right = mid;
        if(left->x > right->x)
            std::swap(left, right);
        fillBetweenLines(*left, *bot, *right, *bot);
    }else if(int(mid->y) == int(bot->y)) { //flat bottom
        const Vec3* left = bot;
        const Vec3* right = mid;
        if(left->x > right->x)
            std::swap(left, right);
         fillBetweenLines(*top, *left, *top, *right);
    }else{ //split triangle into flat/bottom triangles
        float a = top->y - bot->y;
        float b = bot->x - top->x;
        float c = top->x * bot->y - bot->x * top->y;
        Vec3 newMid;
        if(abs(a) > 0.01f) 
            newMid = {(-b * mid->y - c) / a, mid->y, 0.0f};
        else //vertical line (approx.) between top and bottom
            newMid = {top->x, mid->y, 0.0f};
        const Vec3* left = mid;
        const Vec3* right = &newMid;
        if(left->x > right->x)
            std::swap(left, right);
        fillBetweenLines(*top, *left, *top, *right);
        fillBetweenLines(*left, *bot, *right, *bot);
    }

}

void Screen::fillBetweenLines(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3) {

    //left line
    int x0l = int(v0.x);
    int y0l = int(v0.y);
    int z0l = int(v0.z * 5000.0f);
    int x1l = int(v1.x);
    int y1l = int(v1.y);
    int z1l = int(v1.z * 5000.0f);
    int sxl = x0l < x1l ? 1 : -1;
    int syl = y0l < y1l ? 1 : -1;
    int szl = z0l < z1l ? 1 : -1;
    int dxl = abs(x1l - x0l);
    int dyl = -abs(y1l - y0l);
    int dzl = -abs(z1l - z0l);
    int errl = dxl + dyl;

    int errlA = dyl + dzl;
    int y0lA = int(v0.y);

    //right line
    int x0r = int(v2.x);
    int y0r = int(v2.y);
    int z0r = int(v2.z * 5000.0f);
    int x1r = int(v3.x);
    int y1r = int(v3.y);
    int z1r = int(v3.z * 5000.0f);
    int sxr = x0r < x1r ? 1 : -1;
    int syr = y0r < y1r ? 1 : -1;
    int szr = z0r < z1r ? 1 : -1;
    int dxr = abs(x1r - x0r);
    int dyr = -abs(y1r - y0r);
    int dzr = abs(z1r - z0r);
    int errr = dxr + dyr;

    int errrA = dyr + dzr;
    int y0rA = int(v2.y);

    while (true)
    {
        drawLine(x0l, y0l, z0l, x0r, y0r, z0r);
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

        //loop y0lA (alternative) to keep track with y0l (and increment z0l at the same time)
        while(y0lA != y0l) {
            int e2 = errlA * 2;
            if(e2 >= dyl){
                errlA += dyl;
                z0l += szl;
            }
            if(e2 <= dzl) {
                errlA += dzl;
                y0lA += syl;
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


        //loop y0lA (alternative) to keep track with y0l (and increment z0l at the same time)
        while(y0rA != y0r) {
            int e2 = errrA * 2;
            if(e2 >= dyr){
                errrA += dyr;
                z0r += szr;
            }
            if(e2 <= dzr) {
                errrA += dzr;
                y0rA += syr;
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
    resetZBuffer();

    for (int col = 0; col < SCREEN_WIDTH; ++col)
    {
        for (int row = 0; row < SCREEN_HEIGHT; ++row)
        {
            putPixel(col, row, 0);
        }
    }

    resetZBuffer();
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

//resets z-buffer values to inifinity
void Screen::resetZBuffer() {
    for(int row = 0; row < SCREEN_HEIGHT; ++row) {
        for(int col = 0; col < SCREEN_WIDTH; ++col) {
            //m_zBuffer[row * SCREEN_WIDTH + col] = std::numeric_limits<int>::infinity();

            m_zBuffer[row * SCREEN_WIDTH + col] = 10000;
        }
    }
}

void Screen::close()
{
    delete[] m_buffer;
    delete[] m_zBuffer;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_buffer = nullptr;
    m_zBuffer = nullptr;
    m_texture = nullptr;
    m_renderer = nullptr;
    m_window = nullptr;
    SDL_Quit();
}

} // namespace paint
