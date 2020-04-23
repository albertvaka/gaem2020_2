#include "bounds.h"

#include "window.h"

#include <SDL.h>

void Bounds::Draw(int r, int g, int b) const 
{
    SDL_SetRenderDrawColor(Window::renderer, r, g, b, 255);

    SDL_Rect rect = { int(left - Camera::cam.x), int(top - Camera::cam.y), int(width), int(height) };

    SDL_RenderDrawRect(Window::renderer, &rect);
}


void CircleBounds::Draw(int r, int g, int b) const
{
    SDL_SetRenderDrawColor(Window::renderer, r, g, b, 255);
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(Window::renderer, pos.x + x - Camera::cam.x, pos.y - y - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x + x - Camera::cam.x, pos.y + y - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x - x - Camera::cam.x, pos.y - y - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x - x - Camera::cam.x, pos.y + y - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x + y - Camera::cam.x, pos.y - x - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x + y - Camera::cam.x, pos.y + x - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x - y - Camera::cam.x, pos.y - x - Camera::cam.y);
        SDL_RenderDrawPoint(Window::renderer, pos.x - y - Camera::cam.x, pos.y + x - Camera::cam.y);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
