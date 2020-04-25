#pragma once

#include "magic_enum.h"

#include "bounds.h"
#include "window.h"

#include <functional>
#include <SDL.h>

// Static stuff here:
//
// - Keyboard
// - Mouse
// - GamePad
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
extern int key_map[magic_enum::enum_count<GameKeys>()];

inline void RemapInput()
{
	key_map[GameKeys::NONE] = SDL_SCANCODE_UNKNOWN;
	key_map[GameKeys::UP] = SDL_SCANCODE_W;
	key_map[GameKeys::DOWN] = SDL_SCANCODE_S;
	key_map[GameKeys::LEFT] = SDL_SCANCODE_A;
	key_map[GameKeys::RIGHT] = SDL_SCANCODE_D;
	key_map[GameKeys::ACTIVATE] = SDL_SCANCODE_E;
	key_map[GameKeys::ACTION] = SDL_SCANCODE_P;
	key_map[GameKeys::SHOOT] = SDL_SCANCODE_O;
	key_map[GameKeys::START] = SDL_SCANCODE_RETURN;
	key_map[GameKeys::DEBUG_ZOOM_IN] = SDL_SCANCODE_KP_PLUS;
	key_map[GameKeys::DEBUG_ZOOM_OUT] = SDL_SCANCODE_KP_MINUS;
	key_map[GameKeys::RESTART] = SDL_SCANCODE_ESCAPE;
	key_map[GameKeys::DEBUG_FRAME_BY_FRAME] = SDL_SCANCODE_F1;
	key_map[GameKeys::DEBUG_FRAME_BY_FRAME_NEXT] = SDL_SCANCODE_E;
	key_map[GameKeys::DEBUG_MODE] = SDL_SCANCODE_F2;
	key_map[GameKeys::DEBUG_KILLALL] = SDL_SCANCODE_F3;
	key_map[GameKeys::DEBUG_DOGGO] = SDL_SCANCODE_EQUALS;
	key_map[GameKeys::DEBUG_SET_PLANTS_AT_MAX_STATS] = SDL_SCANCODE_F8;
	key_map[GameKeys::DEBUG_GET_MONEY] = SDL_SCANCODE_F6;
	key_map[GameKeys::DEBUG_ADD_PLAYER] = SDL_SCANCODE_F7;
	key_map[GameKeys::MUTE] = SDL_SCANCODE_M;
	key_map[GameKeys::NEXT_TRACK] = SDL_SCANCODE_COMMA;
}

enum KeyStates { JUST_RELEASED, RELEASED, JUST_PRESSED, PRESSED };

/*
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
		None = -1,
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

	static bool IsButtonPressed(int player, GamePad::Button b) { return b==Button::None?false:(button_states[player][b] == PRESSED || button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonJustPressed(int player, GamePad::Button b) { return b==Button::None?false:(button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonReleased(int player, GamePad::Button b) { return b==Button::None?false:(button_states[player][b] == RELEASED || button_states[player][b] == JUST_RELEASED); }
	static bool IsButtonJustReleased(int player, GamePad::Button b) { return b==Button::None?false:(button_states[player][b] == JUST_RELEASED); }

	static void _UpdateInputState__XboxNormal(int joy, int player);
	static void _UpdateInputState();
};
*/

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


using GamePadInput = std::function<bool(int player)>;
extern GamePadInput gp_map[magic_enum::enum_count<GameKeys>()];

inline void RemapGamePadInput()
{
/*  auto kEmpty = [](int){ return false; };
	gp_map[GameKeys::NONE] = kEmpty;
  gp_map[GameKeys::UP] = [](int p) { 
		return GamePad::IsButtonPressed(p, GamePad::Button::B) || 
          GamePad::AnalogStick::Left.get(p, 20.f).y < -50.0f; };
	gp_map[GameKeys::DOWN] = [](int p) { return GamePad::AnalogStick::Left.get(p, 20.f).y > 0.0f; };
	gp_map[GameKeys::LEFT] = [](int p) { return GamePad::AnalogStick::Left.get(p, 20.f).x < 0.0f; };
	gp_map[GameKeys::RIGHT] = [](int p) { return GamePad::AnalogStick::Left.get(p, 20.f).x > 0.0f; };
	gp_map[GameKeys::ACTIVATE] = [](int p){ return GamePad::IsButtonPressed(p, GamePad::Button::A); };
	gp_map[GameKeys::ACTION] = kEmpty;
	gp_map[GameKeys::SHOOT] = kEmpty;
	gp_map[GameKeys::START] = [](int p) { return GamePad::IsButtonPressed(p, GamePad::Button::Start); };
	gp_map[GameKeys::DEBUG_ZOOM_IN] = kEmpty;
	gp_map[GameKeys::DEBUG_ZOOM_OUT] = kEmpty;
	gp_map[GameKeys::RESTART] = [](int p) { return GamePad::IsButtonPressed(p, GamePad::Button::Select); };
	gp_map[GameKeys::DEBUG_FRAME_BY_FRAME] = kEmpty;
	gp_map[GameKeys::DEBUG_FRAME_BY_FRAME_NEXT] = kEmpty;
	gp_map[GameKeys::DEBUG_MODE] = kEmpty;
	gp_map[GameKeys::DEBUG_KILLALL] = kEmpty;
	gp_map[GameKeys::DEBUG_DOGGO] = kEmpty;
	gp_map[GameKeys::DEBUG_SET_PLANTS_AT_MAX_STATS] = kEmpty;
	gp_map[GameKeys::DEBUG_GET_MONEY] = kEmpty;
	gp_map[GameKeys::DEBUG_ADD_PLAYER] = kEmpty;
	gp_map[GameKeys::MUTE] = kEmpty;
	gp_map[GameKeys::NEXT_TRACK] = kEmpty;
	*/
}

// Multi Player Input.
//====================
struct PlayerInput {
	static const int kMaxPlayers = 4;

	static bool IsActionPressed(int player, GameKeys k) {
		return (action_states[player][k] == PRESSED || action_states[player][k] == JUST_PRESSED);
	}

	static bool IsActionJustPressed(int player, GameKeys k) {
		return (action_states[player][k] == JUST_PRESSED);
	}

	static bool IsActionJustPressed(int player, GameKeys k, float interval) {
		return action_states[player][k] == JUST_PRESSED || (action_states[player][k] == PRESSED && action_times[player][k] < interval);
	}

	static bool IsActionReleased(int player, GameKeys k) {
		return (action_states[player][k] == RELEASED || action_states[player][k] == JUST_RELEASED);
	}

	static bool IsActionJustReleased(int player, GameKeys k) {
		return (action_states[player][k] == JUST_RELEASED);
	}

	static bool IsActionJustReleased(int player, GameKeys k, float interval) {
		return action_states[player][k] == JUST_RELEASED || (action_states[player][k] == RELEASED && action_times[player][k] < interval);
	}

	static void ConsumeJustPressed(int player, GameKeys k) {
		action_states[player][k] = PRESSED;
		action_times[player][k] += 1000.f;
	}

	static void ConsumeJustReleased(int player, GameKeys k) {
		action_states[player][k] = RELEASED;
		action_times[player][k] += 1000.f;
	}

	static void _UpdateAllPlayerInput(float dt) {
		/*
		for (int player = 0; player < kMaxPlayers; ++player) {
			int gamepad_id = player_id_to_gamepad_id[player];
      for (size_t k = 1; k < magic_enum::enum_count<GameKeys>(); k++) {  //Skip GameKeys::NONE
        bool pressed_now = player == keyboard_player_id ? Keyboard::IsKeyPressed(GameKeys(k)) : gp_map[k](gamepad_id);
        if (pressed_now) {
          if (action_states[player][k] == JUST_PRESSED || action_states[player][k] == PRESSED) {
            action_states[player][k] = PRESSED;
            if (action_times[player][k] < 1000.f) action_times[player][k] += dt;
          } else {
            action_states[player][k] = JUST_PRESSED;
            action_times[player][k] = dt;
          }
        } else {
          if (action_states[player][k] == JUST_RELEASED || action_states[player][k] == RELEASED) {
            action_states[player][k] = RELEASED;
            if (action_times[player][k] < 1000.f) action_times[player][k] += dt;
          } else {
            action_states[player][k] = JUST_RELEASED;
            action_times[player][k] = dt;
          }
        }
      }
		}*/
	}

	// Assumes one player max on keyboard.
	static int keyboard_player_id;
	static int player_id_to_gamepad_id[kMaxPlayers];
	// A bit redundant with the other classes, but GamePad doesn't support Consume,
	// and makes it a bit easier.
	static KeyStates action_states[kMaxPlayers][magic_enum::enum_count<GameKeys>()];
	static float action_times[kMaxPlayers][magic_enum::enum_count<GameKeys>()];
};



//MOUSE ACCESS
//============
struct Mouse
{
	static float scrollWheel;
	enum Button {
		None = 0,
		Left = SDL_BUTTON_LEFT, //1
		Middle = SDL_BUTTON_MIDDLE, //2
		Right = SDL_BUTTON_RIGHT, //3
	};

	static bool IsPressed(Button b = Button::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == PRESSED || button_states[b] == JUST_PRESSED);
	}

	static bool IsJustPressed(Button b = Button::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == JUST_PRESSED);
	}

	static bool IsReleased(Button b = Button::Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == RELEASED || button_states[b] == JUST_RELEASED);
	}

	static bool IsJustReleased(Button b = Left)
	{
		if (!Window::HasFocus()) return false;
		if (!Window::IsMouseInsideWindow()) return false;
		return (button_states[b] == JUST_RELEASED);
	}

	static float GetScrollWheelMovement() { return scrollWheel; }

	static veci GetPositionInWindow() { return pos; }

	static vec GetPositionInWorld();


	static void _UpdateInputState();


	static KeyStates button_states[magic_enum::enum_count<Button>()];
private:
	static veci pos;

};

namespace Input
{
	void Init();
	void Update(float dt);
}
