#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SDL.h>
#include "magic_enum.h"

#include "bounds.h"
#include "window.h"

// Static stuff here:
//
// - Keyboard
// - Mouse
// - GamePad
// - Camera
// - Window
//

enum GameKeys
{
	NONE = 0,
	UP, DOWN, LEFT, RIGHT,
	ACTION, START, SHOOT,
	ACTIVATE,
	DEBUG_ZOOM_IN, DEBUG_ZOOM_OUT,
	DEBUG_FRAME_BY_FRAME, DEBUG_FRAME_BY_FRAME_NEXT,
	DEBUG_MODE,
	DEBUG_KILLALL,
	DEBUG_DOGGO,
	DEBUG_SET_PLANTS_AT_MAX_STATS,
	DEBUG_GET_MONEY,
	DEBUG_ADD_PLAYER,
	MUTE,
	NEXT_TRACK,
	RESTART,
};
extern sf::Keyboard::Key key_map[magic_enum::enum_count<GameKeys>()];

inline void RemapInput()
{
	key_map[GameKeys::NONE] = sf::Keyboard::Key::Unknown;
	key_map[GameKeys::UP] = sf::Keyboard::Key::W;
	key_map[GameKeys::DOWN] = sf::Keyboard::Key::S;
	key_map[GameKeys::LEFT] = sf::Keyboard::Key::A;
	key_map[GameKeys::RIGHT] = sf::Keyboard::Key::D;
	key_map[GameKeys::ACTIVATE] = sf::Keyboard::Key::E;
	key_map[GameKeys::ACTION] = sf::Keyboard::Key::P;
	key_map[GameKeys::SHOOT] = sf::Keyboard::Key::O;
	key_map[GameKeys::START] = sf::Keyboard::Key::Enter;
	key_map[GameKeys::DEBUG_ZOOM_IN] = sf::Keyboard::Add;
	key_map[GameKeys::DEBUG_ZOOM_OUT] = sf::Keyboard::Subtract;
	key_map[GameKeys::RESTART] = sf::Keyboard::Escape;
	key_map[GameKeys::DEBUG_FRAME_BY_FRAME] = sf::Keyboard::F1;
	key_map[GameKeys::DEBUG_FRAME_BY_FRAME_NEXT] = sf::Keyboard::E;
	key_map[GameKeys::DEBUG_MODE] = sf::Keyboard::F2;
	key_map[GameKeys::DEBUG_KILLALL] = sf::Keyboard::F3;
	key_map[GameKeys::DEBUG_DOGGO] = sf::Keyboard::Equal;
	key_map[GameKeys::DEBUG_SET_PLANTS_AT_MAX_STATS] = sf::Keyboard::F8;
	key_map[GameKeys::DEBUG_GET_MONEY] = sf::Keyboard::F6;
	key_map[GameKeys::DEBUG_ADD_PLAYER] = sf::Keyboard::F7;
	key_map[GameKeys::MUTE] = sf::Keyboard::M;
	key_map[GameKeys::NEXT_TRACK] = sf::Keyboard::Comma;
}

enum KeyStates { JUST_RELEASED, RELEASED, JUST_PRESSED, PRESSED };


struct GamePad
{

private:
	GamePad() { }

	const static int JoystickCountMax = 4;

	static KeyStates button_states[JoystickCountMax][sf::Joystick::ButtonCount];
	static int player_to_joystick[JoystickCountMax];

	static KeyStates calculateJustPressed(bool pressed, KeyStates state);

public:
	enum Button {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		Select = 6,
		Start = 7
	};

	struct Trigger
	{
		struct TriggerBase
		{
			friend struct GamePad;
			bool IsPressed(int player) { return (state[player] == PRESSED || state[player] == JUST_PRESSED); }
			bool IsJustPressed(int player) { return (state[player] == JUST_PRESSED); }
			bool IsReleased(int player) { return (state[player] == RELEASED || state[player] == JUST_RELEASED); }
			bool IsJustReleased(int player) { return (state[player] == JUST_RELEASED); }
		private:
			KeyStates state[JoystickCountMax];
		};
		struct LeftTrigger : public TriggerBase
		{
			float get(int player) const
			{ //Pos between 0 and 100
				int joystick = player_to_joystick[player];
				if (joystick < 0) return 0;
				float a = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Z);
				return a > 0.1 ? a : 0;
			}
		};
		struct RightTrigger : public TriggerBase
		{
			float get(int player) const
			{ //Pos between 0 and 100
				int joystick = player_to_joystick[player];
				if (joystick < 0) return 0;
				float a = -sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Z);
				return a > 0.1 ? a : 0;
			}
		};
		static LeftTrigger Left;
		static RightTrigger Right;
	};

	struct AnalogStick
	{
		const static AnalogStick Left;
		const static AnalogStick Right;
		sf::Vector2f get(int player, float dead_area = 0) const
		{ //Pos between -100 and 100
			if (player > GamePad::JoystickCountMax) {
				return sf::Vector2f();
			}
			int joystick = player_to_joystick[player];
			if (joystick < 0) return sf::Vector2f();
			float a = sf::Joystick::getAxisPosition(joystick, x);
			float b = sf::Joystick::getAxisPosition(joystick, y);
			return sf::Vector2f(abs(a) > dead_area ? a : 0, abs(b) > dead_area ? b : 0);
		}
	private:
		AnalogStick(sf::Joystick::Axis mx, sf::Joystick::Axis my) : x(mx), y(my) { }
		sf::Joystick::Axis x, y;
	};

	static bool IsButtonPressed(int player, GamePad::Button b) { return (button_states[player][b] == PRESSED || button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonJustPressed(int player, GamePad::Button b) { return (button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonReleased(int player, GamePad::Button b) { return (button_states[player][b] == RELEASED || button_states[player][b] == JUST_RELEASED); }
	static bool IsButtonJustReleased(int player, GamePad::Button b) { return (button_states[player][b] == JUST_RELEASED); }

	static void _UpdateInputState__MandoSteam(int joy, int player);
	static void _UpdateInputState__XboxNormal(int joy, int player);
	static void _UpdateInputState();
};


//KEYBOARD ACCESS
//===============

struct Keyboard
{
	static bool IsKeyPressed(GameKeys k) {
		return (key_states[k] == PRESSED || key_states[k] == JUST_PRESSED);
	}

	static bool IsKeyJustPressed(GameKeys k) {
		return (key_states[k] == JUST_PRESSED);
	}

	static bool IsKeyJustPressed(GameKeys k, float interval) {
		return key_states[k] == JUST_PRESSED || (key_states[k] == PRESSED && key_times[k] < interval);
	}

	static bool IsKeyReleased(GameKeys k) {
		return (key_states[k] == RELEASED || key_states[k] == JUST_RELEASED);
	}

	static bool IsKeyJustReleased(GameKeys k) {
		return (key_states[k] == JUST_RELEASED);
	}

	static bool IsKeyJustReleased(GameKeys k, float interval) {
		return key_states[k] == JUST_RELEASED || (key_states[k] == RELEASED && key_times[k] < interval);
	}

	static void ConsumeJustPressed(GameKeys k) {
		key_states[k] = PRESSED;
		key_times[k] += 1000.f;
	}

	static void ConsumeJustReleased(GameKeys k) {
		key_states[k] = RELEASED;
		key_times[k] += 1000.f;
	}


	static void _UpdateInputState(float dt);

	static KeyStates key_states[magic_enum::enum_count<GameKeys>()];
	static float key_times[magic_enum::enum_count<GameKeys>()];
};



//MOUSE ACCESS
//============
struct Mouse
{
	static bool IsPressed(sf::Mouse::Button b = sf::Mouse::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == PRESSED || button_states[b] == JUST_PRESSED);
	}

	static bool IsJustPressed(sf::Mouse::Button b = sf::Mouse::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == JUST_PRESSED);
	}

	static bool IsReleased(sf::Mouse::Button b = sf::Mouse::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == RELEASED || button_states[b] == JUST_RELEASED);
	}

	static bool IsJustReleased(sf::Mouse::Button b = sf::Mouse::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == JUST_RELEASED);
	}

	static float GetScrollWheelMovement() { return scrollWheel; }

	static sf::Vector2i GetPositionInWindow();

	static vec GetPositionInWorld();


	static void _UpdateInputState();

	static float scrollWheel;
	static KeyStates button_states[sf::Mouse::ButtonCount];
	
};

namespace Input
{
	void Init();
	void Update(float dt);
}
