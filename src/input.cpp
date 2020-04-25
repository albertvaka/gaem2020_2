#include "input.h"
#include <SDL.h>

#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_sdl.h"
#endif

SDL_GameController* GamePad::player_to_joystick[PlayerInput::kMaxPlayers] = { nullptr };

const GamePad::AnalogStick GamePad::AnalogStick::Left(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
const GamePad::AnalogStick GamePad::AnalogStick::Right(SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY);

GamePad::Trigger::LeftTrigger GamePad::Trigger::Left;
GamePad::Trigger::RightTrigger GamePad::Trigger::Right;

KeyStates GamePad::button_states[PlayerInput::kMaxPlayers][SDL_CONTROLLER_BUTTON_MAX];

KeyStates Mouse::button_states[magic_enum::enum_count<Button>()];
float Mouse::scrollWheel;
veci Mouse::pos(0,0);
KeyStates Keyboard::key_states[magic_enum::enum_count<GameKeys>()];
float Keyboard::key_times[magic_enum::enum_count<GameKeys>()];
int key_map[magic_enum::enum_count<GameKeys>()];

// Assumes first player is on Keyboard.
int PlayerInput::keyboard_player_id = 0;
int PlayerInput::player_id_to_gamepad_id[PlayerInput::kMaxPlayers] = {-1, 0, 1, 2};
KeyStates PlayerInput::action_states[PlayerInput::kMaxPlayers][magic_enum::enum_count<GameKeys>()];
float PlayerInput::action_times[PlayerInput::kMaxPlayers][magic_enum::enum_count<GameKeys>()];
GamePadInput gp_map[magic_enum::enum_count<GameKeys>()];


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

void GamePad::_UpdateInputState__XboxNormal(SDL_GameController* joystick, int player)
{
    for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
    {
        bool pressed = SDL_GameControllerGetButton(joystick, SDL_GameControllerButton(i));
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


void GamePad::_Added(SDL_GameController* joystick) {
    Debug::out << "Added " << joystick;
    for (int player = 0; player < PlayerInput::kMaxPlayers; player++) {
        if (!player_to_joystick[player]) {
            player_to_joystick[player] = joystick;
            break;
        }
    }
}

void GamePad::_Removed(SDL_GameController* joystick) {
    Debug::out << "Removed " << joystick;
    for (int player = 0; player < PlayerInput::kMaxPlayers; player++) {
        if (joystick == player_to_joystick[player]) {
            player_to_joystick[player] = nullptr;
            break;
        }
    }
}

void GamePad::_UpdateInputState() {
    for (int player = 0; player < PlayerInput::kMaxPlayers; player++) {
        SDL_GameController* joystick = player_to_joystick[player];
        if (joystick) {
            _UpdateInputState__XboxNormal(joystick, player);
        }
        else {
            for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
                button_states[player][i] = calculateJustPressed(false, button_states[player][i]);
            }
        }
    }
}

void Mouse::_UpdateInputState()
{
    int pressed = SDL_GetRelativeMouseState(&pos.x, &pos.y);
    for (size_t i = 1; i < magic_enum::enum_count<Button>(); i++) //skip NONE
    {
        if (pressed & SDL_BUTTON(i))
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

vec Mouse::GetPositionInWorld()
{
    return (vec(GetPositionInWindow()) / Camera::zoom) + Camera::pos;
}

void Keyboard::_UpdateInputState(float dt)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for (size_t i = 1; i < magic_enum::enum_count<GameKeys>(); i++) //Skip GameKeys::NONE
	{
        if (state[key_map[i]] && Window::HasFocus())
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


void PlayerInput::_UpdateAllPlayerInput(float dt)
{
    for (int player = 0; player < PlayerInput::kMaxPlayers; ++player) {
        int gamepad_id = player_id_to_gamepad_id[player];
        for (size_t k = 1; k < magic_enum::enum_count<GameKeys>(); k++) {  //Skip GameKeys::NONE
            bool pressed_now = player == keyboard_player_id ? Keyboard::IsKeyPressed(GameKeys(k)) : (gp_map[k] && gp_map[k](gamepad_id));
            if (pressed_now) {
                if (action_states[player][k] == JUST_PRESSED || action_states[player][k] == PRESSED) {
                    action_states[player][k] = PRESSED;
                    if (action_times[player][k] < 1000.f) action_times[player][k] += dt;
                }
                else {
                    action_states[player][k] = JUST_PRESSED;
                    action_times[player][k] = dt;
                }
            }
            else {
                if (action_states[player][k] == JUST_RELEASED || action_states[player][k] == RELEASED) {
                    action_states[player][k] = RELEASED;
                    if (action_times[player][k] < 1000.f) action_times[player][k] += dt;
                }
                else {
                    action_states[player][k] = JUST_RELEASED;
                    action_times[player][k] = dt;
                }
            }
        }
    }
}


namespace Input
{
    void Update(float dt)
	{
        Mouse::scrollWheel = 0.f;

#ifdef _IMGUI
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard)
#endif
        {
            Keyboard::_UpdateInputState(dt);

        }
#ifdef _IMGUI
        if (!io.WantCaptureMouse)
#endif
        {
            Mouse::_UpdateInputState();
        }
        GamePad::_UpdateInputState();
        PlayerInput::_UpdateAllPlayerInput(dt);
    }
    void Init()
	{
        RemapInput();
        for (size_t i = 0; i < magic_enum::enum_count<GameKeys>(); i++) Keyboard::key_states[i] = RELEASED;
        for (size_t i = 0; i < magic_enum::enum_count<Mouse::Button>(); i++) Mouse::button_states[i] = RELEASED;
        RemapGamePadInput();
        for (int p = 0; p < PlayerInput::kMaxPlayers; ++p) {
          for (size_t i = 0; i < magic_enum::enum_count<GameKeys>(); i++) PlayerInput::action_states[p][i] = RELEASED;
        }
    }
    
}
