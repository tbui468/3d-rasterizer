#include "Screen.hpp"
#include "Rasterize.hpp"
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
    /*BRESEHAM'S ALGORITHM*/
    int x0 = int(x0f);
    int y0 = int(y0f);
    int x1 = int(x1f);
    int y1 = int(y1f);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    if (y0 == y1)
    { //horizontal line
        while(true) {
            putPixel(x0, y0);
            if(x0 == x1)
                break;
            x0 += sx;
        }
    }
    else if (x0 == x1)
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
        int dx = abs(x1 - x0);
        int dy = -abs(y1 - y0);
        int err = dx + dy;

        while (true)
        {
            putPixel(x0, y0);
            if (x0 == x1 && y0 == y1)
            {
                break;
            }
            int e2 = 2 * err;
            if (e2 > dy)
            {
                err += dy;
                x0 += sx;
            }
            if (e2 <= dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }
}

//draw model(THis can be processed by GPU for better performance, such as using CUDA)
void Screen::drawPolygon(const std::vector<Vec3> &vertexBuffer, const Mat4 &transformation, const std::vector<Index> &indexBuffer)
{
    //apply transformation to model and load into new vertex
    unsigned int vertexBufferSize = vertexBuffer.size();
    std::vector<Vec3> transformedVB;
    for (const Vec3 &v3 : vertexBuffer)
    {
        Vec4 v4 = {v3.x, v3.y, v3.z, 1.0f};
        v4 = transformation * v4;
        transformedVB.emplace_back(v4.x, v4.y, v4.z);
    }

    //draw each transformed vertex using index buffer
    for (const Index &i : indexBuffer)
    {
        assert(i.x < vertexBufferSize);
        assert(i.y < vertexBufferSize);
        assert(i.z < vertexBufferSize);
        drawLine(transformedVB.at(i.x).x, transformedVB.at(i.x).y, transformedVB.at(i.y).x, transformedVB.at(i.y).y);
        drawLine(transformedVB.at(i.y).x, transformedVB.at(i.y).y, transformedVB.at(i.z).x, transformedVB.at(i.z).y);
        drawLine(transformedVB.at(i.z).x, transformedVB.at(i.z).y, transformedVB.at(i.x).x, transformedVB.at(i.x).y);

        Vec2 vec[3];
        vec[0] = {transformedVB.at(i.x).x, transformedVB.at(i.x).y};
        vec[1] = {transformedVB.at(i.y).x, transformedVB.at(i.y).y};
        vec[2] = {transformedVB.at(i.z).x, transformedVB.at(i.z).y};

//        drawTriangle(*this, vec);
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
