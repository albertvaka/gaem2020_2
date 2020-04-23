#include "input.h"
#include <SDL.h>

#ifdef _DEBUG
#include "imgui.h"
#include "imgui-SFML.h"
#endif

int GamePad::player_to_joystick[GamePad::JoystickCountMax];

const GamePad::AnalogStick GamePad::AnalogStick::Left(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
const GamePad::AnalogStick GamePad::AnalogStick::Right(sf::Joystick::Axis::U, sf::Joystick::Axis::V);

GamePad::Trigger::LeftTrigger GamePad::Trigger::Left;
GamePad::Trigger::RightTrigger GamePad::Trigger::Right;

KeyStates GamePad::button_states[GamePad::JoystickCountMax][sf::Joystick::ButtonCount];
KeyStates Mouse::button_states[sf::Mouse::ButtonCount];
float Mouse::scrollWheel;
KeyStates Keyboard::key_states[magic_enum::enum_count<GameKeys>()];
float Keyboard::key_times[magic_enum::enum_count<GameKeys>()];
sf::Keyboard::Key key_map[magic_enum::enum_count<GameKeys>()];


KeyStates GamePad::calculateJustPressed(bool pressed, KeyStates state)
{
    if (pressed)
	{
        //FIXME: No hauria d'anar per frames, sino per temps.
        // Si porta apretat < X milis, esta justpressed
        // Per fer tricks com deixar saltar "tard" podriem incrementar aquest temps (parametre extra a justpressed?)
        if (state == JUST_PRESSED || state == PRESSED)
		{
            state = PRESSED;
        }
        else
		{
            state = JUST_PRESSED;
        }
    }
    else
	{
        if (state == JUST_RELEASED || state == RELEASED)
		{
            state = RELEASED;
        }
        else
		{
            state = JUST_RELEASED;
        }
    }
    return state;
}

void GamePad::_UpdateInputState__MandoSteam(int joy, int player)
{
    //TODO: Fix this
    for (int i = 0; i < sf::Joystick::ButtonCount; i++)
    {
        bool pressed = (sf::Joystick::isButtonPressed(joy, i));
        button_states[player][i] = calculateJustPressed(pressed, button_states[player][i]);
    }
    {
        bool pressed = (Trigger::Left.get(player) > 50);
        Trigger::Left.state[player] = calculateJustPressed(pressed, Trigger::Left.state[player]);
    }
    {
        bool pressed = (Trigger::Right.get(player) > 50);
        Trigger::Right.state[player] = calculateJustPressed(pressed, Trigger::Right.state[player]);
    }
}

void GamePad::_UpdateInputState__XboxNormal(int joy, int player)
{
    for (int i = 0; i < sf::Joystick::ButtonCount; i++)
    {
        bool pressed = (sf::Joystick::isButtonPressed(joy, i));
        button_states[player][i] = calculateJustPressed(pressed, button_states[player][i]);
    }
    {
        bool pressed = (Trigger::Left.get(player) > 50);
        Trigger::Left.state[player] = calculateJustPressed(pressed, Trigger::Left.state[player]);
    }
    {
        bool pressed = (Trigger::Right.get(player) > 50);
        Trigger::Right.state[player] = calculateJustPressed(pressed, Trigger::Right.state[player]);
    }
}


void Mouse::_UpdateInputState()
{
    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
        if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
		{
            if (button_states[i] == JUST_PRESSED || button_states[i] == PRESSED)
			{
                button_states[i] = PRESSED;
            }
            else
			{
                button_states[i] = JUST_PRESSED;
            }
        }
        else
		{
            if (button_states[i] == JUST_RELEASED || button_states[i] == RELEASED)
			{
                button_states[i] = RELEASED;
            }
            else
			{
                button_states[i] = JUST_RELEASED;
            }
        }
    }

}

sf::Vector2i Mouse::GetPositionInWindow()
{
    //return sf::Mouse::getPosition(*Window::window); //window arg is needed for relative coords
    return sf::Vector2i();
}

vec Mouse::GetPositionInWorld()
{
    /*
    vec displacement = Camera::gameView.getCenter() - (Camera::gameView.getSize() / 2.f);
    return (vec(GetPositionInWindow())/Camera::zoom) + displacement;
    */
    return vec();
}


void GamePad::_UpdateInputState()
    {
        int player = 0;
        for (int joystick = 0; joystick < JoystickCountMax; ++joystick)
        {
            if (!sf::Joystick::isConnected(joystick))
            {
                continue;
            }
            player_to_joystick[player] = joystick;


            sf::Joystick::Identification id_joy = sf::Joystick::getIdentification(joystick);

            const int ID_MANDO_STEAM = 999999;
            switch (id_joy.productId)
            {
            case ID_MANDO_STEAM:
            {
                _UpdateInputState__MandoSteam(joystick, player);
            } break;

            default:
            {
                _UpdateInputState__XboxNormal(joystick, player);
            } break;
            }

            player++;

        }

        while (player < JoystickCountMax)
        {
            player_to_joystick[player] = -1;
            for (int i = 0; i < sf::Joystick::ButtonCount; i++)
            {
                button_states[player][i] = calculateJustPressed(false, button_states[player][i]);
            }
            player++;
        }

}

void Keyboard::_UpdateInputState(float dt)
{
    for (size_t i = 1; i < magic_enum::enum_count<GameKeys>(); i++) //Skip GameKeys::NONE
	{
        if (sf::Keyboard::isKeyPressed(key_map[i]) && Window::WindowHasFocus())
		{
            if (key_states[i] == JUST_PRESSED || key_states[i] == PRESSED)
			{
                key_states[i] = PRESSED;
                if (key_times[i] < 1000.f) key_times[i] += dt;
            }
            else
			{
                key_states[i] = JUST_PRESSED;
                key_times[i] = dt;
            }
        }
        else
		{
            if (key_states[i] == JUST_RELEASED || key_states[i] == RELEASED)
			{
                key_states[i] = RELEASED;
                if (key_times[i] < 1000.f) key_times[i] += dt;
            }
            else
			{
                key_states[i] = JUST_RELEASED;
                key_times[i] = dt;
            }
        }
    }

}

namespace Input
{
    void Update(sf::Time deltaTime)
	{
        /*
#ifdef _DEBUG
        ImGui::SFML::Update(*Window::window, deltaTime);
#endif
        Mouse::scrollWheel = 0.f;
        _ProcessWindowEvents();

#ifdef _DEBUG
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard)
#endif
        {
            Keyboard::_UpdateInputState(deltaTime.asSeconds());

        }
#ifdef _DEBUG
        if (!io.WantCaptureMouse)
#endif
        {
            Mouse::_UpdateInputState();
        }
        GamePad::_UpdateInputState();
        */
    }
    void Init(SDL_Window* renderwindow)
	{
        /*
        Camera::ResetCamera();
        Camera::ResetGuiCamera();
        RemapInput();
        for (size_t i = 0; i < magic_enum::enum_count<GameKeys>(); i++) Keyboard::key_states[i] = RELEASED;
        for (size_t i = 0; i < sf::Mouse::ButtonCount; i++) Mouse::button_states[i] = RELEASED;
        */
        
    }
    
}
