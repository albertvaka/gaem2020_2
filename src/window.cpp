#include "window.h"
#include "input.h"
#include "imgui_impl_sdl.h"

namespace Camera {
    float zoom = 1.f;
    vec pos(Window::WINDOW_WIDTH / 2, Window::WINDOW_HEIGHT / 2);
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
        if (Keyboard::IsKeyPressed(GameKeys::RIGHT))
        {
            c.x += velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(GameKeys::LEFT))
        {
            c.x -= velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(GameKeys::DOWN))
        {
            c.y += velocity * dt * 10 / zoom;
        }
        if (Keyboard::IsKeyPressed(GameKeys::UP))
        {
            c.y -= velocity * dt * 10 / zoom;
        }
        SetCenter(c);
    }

    void ChangeZoomWithPlusAndMinus(float zoomVel, float dt)
    {
        float zoom = GetZoom();
        if (Keyboard::IsKeyPressed(GameKeys::DEBUG_ZOOM_IN))
        {
            zoom += zoomVel * dt;
        }
        if (Keyboard::IsKeyPressed(GameKeys::DEBUG_ZOOM_OUT))
        {
            zoom -= zoomVel * dt;
        }
        SetZoom(zoom);
    }

}

namespace Window
{
    void Init() {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (window == NULL) {
            printf("Window Creation Error: %s\n", SDL_GetError());
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            printf("Renderer Creation Error: %s\n", SDL_GetError());
        }
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
            case SDL_MOUSEWHEEL:
                Mouse::scrollWheel += event.wheel.y;
            case SDL_QUIT:
                exit(0);
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
            {
                // GuiView: scale from top-left corner
                vec oldSize = Camera::guiView.getSize() * (Window::GUI_ZOOM);
                vec newSize = sf::Vector2f(Window::window->getSize());
            //    Camera::guiView.setSize(newSize);
            //    Camera::guiView.zoom(1.f / Window::GUI_ZOOM);
            //    Camera::guiView.setCenter(vec(Camera::guiView.getCenter()) + (newSize-oldSize)/(2*Window::GUI_ZOOM));
            }
                break;
            }
        }
        */
    }

}
