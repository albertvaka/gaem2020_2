#include "window.h"
#include "input.h"
#include "imgui_impl_sdl.h"
#include "debug.h"

#include "SDL_gpu.h"

namespace Camera {
    GPU_Camera camera;
}
namespace Window
{
    SDL_Window* window;
    GPU_Target* target;
    bool focus = true;
    SDL_GLContext glcontext;
}

namespace Camera {

    //Useful for debug pourposes
    void MoveCameraWithArrows(float velocity, float dt) {
        vec c = GetTopLeft();
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
        SetTopLeft(c);
    }

    void ChangeZoomWithPlusAndMinus(float zoomVel, float dt)
    {
        float zoom = GetZoom();
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_KP_PLUS))
        {
            zoom += zoomVel * dt;
            SetZoom(zoom);
        }
        if (Keyboard::IsKeyPressed(SDL_SCANCODE_KP_MINUS)) {
            zoom -= zoomVel * dt;
            if (zoom < 0.01) zoom = 0.01;
            SetZoom(zoom);
        }
    }
}

#if __WIN32__
#pragma comment(lib, "Shcore.lib")
#include <ShellScalingApi.h>
#endif

namespace Window
{
    void Init() {

#if __WIN32__
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
#endif
    #ifdef __EMSCRIPTEN__
        int scale = 1;
    #else
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);
        int scale = Mates::MinOf(dm.w / GAME_WIDTH, dm.h / GAME_HEIGHT);
        Debug::out << "Scaling to x" << scale;
    #endif
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH * scale, GAME_HEIGHT * scale, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
        if (window == NULL) {
            Debug::out << "Window Creation Error: " << SDL_GetError();
        }
        GPU_SetInitWindow(SDL_GetWindowID(window));
        GPU_SetLogCallback([](GPU_LogLevelEnum log_level, const char* format, va_list args) -> int {
            char buffer[1024];
            vsprintf(buffer, format, args);
            Debug::out << std::string(buffer);
            return 0;
        });

        target = GPU_Init(GAME_WIDTH, GAME_HEIGHT, GPU_DEFAULT_INIT_FLAGS);

        // SDL-gpu anchors images at the center by default, change it to the top-left corner
        GPU_SetDefaultAnchor(0, 0);

        //FIXME: Too late for this game, but we have the option to set the Y coordinates the right way
        //GPU_SetCoordinateMode(false);

        GPU_EnableCamera(target, true);
        Camera::camera = GPU_GetDefaultCamera();
        Camera::camera.use_centered_origin = false;
        Camera::SetTopLeft(0, 0);

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
                    GPU_SetWindowResolution(event.window.data1, event.window.data2);
                    GPU_SetVirtualResolution(Window::target, Window::GAME_WIDTH, Window::GAME_HEIGHT);
                }
                break;
            }
            //ImGui_ImplSDL2_ProcessEvent(&event);
        }
    }

    
    namespace DrawPrimitive {

        void Pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            GPU_Pixel(Window::target, x, y, { r,g,b,a });
        }

        void Rectangle(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            if (thickness < 0)
            {
                GPU_SetLineThickness(0);
                GPU_RectangleFilled(Window::target, x1, y1, x2, y2, {r,g,b,a});
            }
            else
            {
                GPU_SetLineThickness(thickness);
                GPU_Rectangle(Window::target, x1, y1, x2, y2, { r,g,b,a });
            }
        }

        void Line(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            GPU_SetLineThickness(thickness);
            GPU_Line(Window::target, x1, y1, x2, y2, { r,g,b,a });
        }

        void Circle(float x, float y, int radius, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            GPU_SetLineThickness(thickness);
            if (thickness < 0) {
                GPU_SetLineThickness(0);
                GPU_CircleFilled(Window::target, x, y, radius, {r,g,b,a});
            }
            else {
                GPU_SetLineThickness(thickness);
                GPU_Circle(Window::target, x, y, radius, {r,g,b,a});
            }
        }
    }
}
