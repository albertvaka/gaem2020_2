#include "window.h"
#include "input.h"
#include "imgui-sfml.h"

namespace Window
{
    sf::RenderWindow* window;
    bool focus = true;
}

void _ProcessWindowEvents()
{

    sf::Event sfmlevent;
    while (Window::window->pollEvent(sfmlevent))
    {
#ifdef _DEBUG
        ImGui::SFML::ProcessEvent(sfmlevent);
#endif
        switch (sfmlevent.type) {
        case sf::Event::LostFocus:
            Window::focus = false;
            break;
        case sf::Event::GainedFocus:
            Window::focus = true;
            break;
        case sf::Event::Closed:
            Window::window->close();
            break;
        case sf::Event::MouseWheelScrolled:
            Mouse::scrollWheel += sfmlevent.mouseWheelScroll.delta;
            break;
        case sf::Event::Resized: //To disable sfml's automatic scaling
        /*{
            // GameView: scale from center
            vec currentCenter = Camera::gameView.getCenter();
            Camera::gameView.setSize(sf::Vector2f(Window::window->getSize()));
            Camera::gameView.setCenter(currentCenter);
            Camera::gameView.zoom(1.f / Camera::zoom);
        }
        {
            // GuiView: scale from top-left corner
            vec oldSize = Camera::guiView.getSize() * (Window::GUI_ZOOM);
            vec newSize = sf::Vector2f(Window::window->getSize());
            Camera::guiView.setSize(newSize);
            Camera::guiView.zoom(1.f / Window::GUI_ZOOM);
            Camera::guiView.setCenter(vec(Camera::guiView.getCenter()) + (newSize-oldSize)/(2*Window::GUI_ZOOM));
        }*/
            break;
        default:
            break;
        }
    }
}

namespace Window
{

    void SetWindowCaption(const std::string& s)
	{
        window->setTitle(s);
    }

    bool WindowHasFocus()
	{
        return focus;
    }

    void CloseWindow()
	{
        window->close();
    }

    void SetWindowSize(sf::Vector2u size, bool centerCamera)
	{
        window->setSize(size);
        _ProcessWindowEvents();
        if (centerCamera) Camera::SetCameraCenter(size / 2);
    }

    sf::Vector2u GetWindowSize()
	{
        return window->getSize();
    }

    Bounds GetWindowBounds()
	{
        return Bounds(0.f, 0.f, (float)window->getSize().x, (float)window->getSize().y);
    }

    bool IsMouseInsideWindow()
	{
        sf::Vector2i vec = sf::Mouse::getPosition(*window);
        if (vec.x < 0 || vec.x >(int)window->getSize().x) return false;
        if (vec.y < 0 || vec.y >(int)window->getSize().y) return false;
        return true;
    }

}
