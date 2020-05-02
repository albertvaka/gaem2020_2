#include "window.h"
#include "input.h"
#include "SDL2_gfxPrimitives.h"
#include "imgui_impl_sdl.h"
#include "debug.h"

namespace Camera {
    float zoom = 1.f;
    vec pos(0, 0);
}

namespace Window
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool focus = true;
}

namespace Camera {

    //Useful for debug pourposes
    void MoveCameraWithArrows(float velocity, float dt) {
        vec c = GetCenter();
        float zoom = GetZoom();
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_RIGHT))
        {
            c.x += velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_LEFT))
        {
            c.x -= velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_DOWN))
        {
            c.y += velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_UP))
        {
            c.y -= velocity * dt * 10 / zoom;
        }
        SetCenter(c);
    }

    void ChangeZoomWithPlusAndMinus(float zoomVel, float dt)
    {
        float zoom = GetZoom();
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_KP_PLUS))
        {
            zoom += zoomVel * dt;
        }
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_KP_MINUS))
        {
            zoom -= zoomVel * dt;
        }
        SetZoom(zoom);
    }

}
#if __WIN32__
#pragma comment(lib, "Shcore.lib")
#include <ShellScalingAPI.h>
#endif

namespace Window
{
    void Init() {

#if __WIN32__
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
#endif

        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);
        int scale = Mates::MinOf(dm.w / GAME_WIDTH, dm.h / GAME_HEIGHT);
        Debug::out << "Scaling to x" << scale;

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH*scale, GAME_HEIGHT*scale, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL) {
            Debug::out << "Window Creation Error: " << SDL_GetError();
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            Debug::out << "Renderer Creation Error: " << SDL_GetError();
        }
        ResetViewport();
    }

    bool IsMouseInsideWindow()
	{

        //sf::Vector2i vec = sf::Mouse::getPosition(*window);
        //if (vec.x < 0 || vec.x >(int)window->getSize().x) return false;
        //if (vec.y < 0 || vec.y >(int)window->getSize().y) return false;
        return true;
    }

    void ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT_FOCUS_LOST:
                focus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                focus = true;
                break;
            case SDL_CONTROLLERDEVICEADDED:
                GamePad::_Added(SDL_GameControllerOpen(event.jdevice.which));
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                GamePad::_Removed(SDL_GameControllerFromInstanceID(event.jdevice.which));
                break;
            case SDL_MOUSEWHEEL:
                Mouse::scrollWheel += event.wheel.y;
                break;
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    ResetViewport();
                }
                break;
            }
            //ImGui_ImplSDL2_ProcessEvent(&event);
        }

        /*
        sf::Event sfmlevent;
        while (Window::window->pollEvent(sfmlevent))
        {
            switch (sfmlevent.type) {
            case sf::Event::Resized: //To disable sfml's automatic scaling
            {
                // GameView: scale from center
                vec currentCenter = Camera::gameView.getCenter();
            //    Camera::gameView.setSize(sf::Vector2f(Window::window->getSize()));
            //    Camera::gameView.setCenter(currentCenter);
            //    Camera::gameView.zoom(1.f / Camera::zoom);
            }
                break;
            }
        }
        */
    }

    
    namespace DrawPrimitive {

        inline int fastfloor(const float x) { return x > 0 ? (int)x : (int)x - 1; }

        void Pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            pixelRGBA(Window::renderer, x - Camera::pos.x, y - Camera::pos.y, r, g, b, a);
        }

        void Rectangle(float _x1, float _y1, float _x2, float _y2, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            int x1 = _x1 - Camera::pos.x;
            int y1 = _y1 - Camera::pos.y;
            int x2 = _x2 - Camera::pos.x;
            int y2 = _y2 - Camera::pos.y;
            if (thickness < 0)
            {
                boxRGBA(Window::renderer, x1, y1, x2, y2, r, g, b, a);
            }
            else if (thickness == 1)
            {
                rectangleRGBA(Window::renderer, x1, y1, x2, y2, r, g, b, a);
            } 
            else
            {
                int e = thickness/2;
                thickLineRGBA(Window::renderer, x1 - e, y1, x2 - e, y1, thickness, r, g, b, a); // top
                thickLineRGBA(Window::renderer, x2 + 1, y1 - e, x2 + 1, y2 - e, thickness, r, g, b, a); // right
                thickLineRGBA(Window::renderer, x1 + e, y2 + 1, x2 + e, y2 + 1, thickness, r, g, b, a); // bottom
                thickLineRGBA(Window::renderer, x1, y1 + e, x1, y2 + e, thickness, r, g, b, a); // left
            }
        }

        void Line(float x1, float y1, float x2, float y2, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            thickLineRGBA(Window::renderer, x1 - Camera::pos.x, y1 - Camera::pos.y, x2 - Camera::pos.x, y2 - Camera::pos.y, thickness, r, g, b, a);
        }

        vec CirclePoint(int index, int m_pointCount, int m_radius) {
            static const float pi = 3.141592654f;

            float angle = index * 2 * pi / m_pointCount - pi / 2;
            float x = std::cos(angle) * m_radius;
            float y = std::sin(angle) * m_radius;

            return vec(x, y);
        }

        void Circle(float _x, float _y, int radius, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            int x = _x - Camera::pos.x;
            int y = _y - Camera::pos.y;
            if (thickness < 0) {
                filledCircleRGBA(Window::renderer, x, y, radius, r, g, b, a);
            }
            else {
                //Hack: Use the renderer scale to increase the thickness
                float scalex, scaley;
                SDL_RenderGetScale(Window::renderer, &scalex, &scaley);
                SDL_RenderSetScale(Window::renderer, thickness*scalex, thickness*scalex);
                circleRGBA(Window::renderer, x/thickness, y/thickness, radius/thickness, r, g, b, a);
                SDL_RenderSetScale(Window::renderer, scalex, scaley);
            }
        }
    }
}
