#include <string>

#ifdef _DEBUG
#define SDL_MAIN_HANDLED
#endif

#include "scene_manager.h"
#include "input.h"
#include "mates.h"
#include "assets.h"
#include "debug.h"

#include "scene_jumpman.h"
#include "intro_scene.h"

#ifdef _IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "imgui_impl_sdl.h"
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Scene* SceneManager::currentScene = nullptr;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

float mainClock;

#define _FPS_COUNTER

Scene* currentScene;
Text* txt_fps;
int fps_counter = 0;
float fpsClock = 0.f;
bool slowDown = false;
int last_ticks;

void init();
void main_loop();

int main(int argc, char* argv[])
{
	init();
	
#ifdef __EMSCRIPTEN__
  	emscripten_set_main_loop(main_loop, 0, 1);
#else
	while (true) {
		main_loop();
	}
#endif

}


void init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER)) {
		Debug::out << IMG_GetError();
	}

	if (IMG_Init(IMG_INIT_PNG)) {
		Debug::out << IMG_GetError();
	}

	if (TTF_Init()) {
		Debug::out << TTF_GetError();
	}

	if (Mix_Init(MIX_INIT_OGG)) {
		Debug::out << Mix_GetError();
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)) {
		Debug::out << Mix_GetError();
	}

	Window::Init();

	Input::Init();

#ifdef _IMGUI
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Window::window, nullptr);
	ImGuiSDL::Initialize(Window::renderer, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
#endif

	Assets::LoadAll();

	srand(time(NULL));

#ifdef _FPS_COUNTER
	txt_fps= new Text(Assets::font_30);
	txt_fps->setString("0");
#endif

	last_ticks = SDL_GetTicks();

	currentScene = new IntroScene();
	SceneManager::SetScene(currentScene);
	currentScene->EnterScene();
}


void main_loop() {

	if (SceneManager::CurrentScene() != currentScene) {
		currentScene->ExitScene();
		delete currentScene;
		currentScene = SceneManager::CurrentScene();
		currentScene->EnterScene();
	}

#ifdef _IMGUI
	ImGui_ImplSDL2_NewFrame(Window::window);
	ImGui::NewFrame();
#endif

	int ticks = SDL_GetTicks();
	float dt = (ticks - last_ticks) / 1000.f;
	last_ticks = ticks;

	Window::ProcessEvents();
	Input::Update(dt);

#ifdef _DEBUG
	if (Keyboard::IsKeyJustPressed(DEBUG_MODE)) {
		Debug::Draw = !Debug::Draw;
	}
#endif

#ifdef _DEBUG
	static bool frameByFrame = false;

	if (Keyboard::IsKeyJustPressed(DEBUG_FRAME_BY_FRAME)) {
		frameByFrame = !frameByFrame;
	}
	if (frameByFrame && Debug::Draw) {
		Camera::MoveCameraWithArrows(50.f, dt);
		Camera::ChangeZoomWithPlusAndMinus(1.f, dt);
	}

	if (!frameByFrame || Keyboard::IsKeyJustPressed(DEBUG_FRAME_BY_FRAME_NEXT) || Keyboard::IsKeyJustPressed(RESTART))
#endif
	{
#ifdef _DEBUG
		ClearDebugVecs();
#endif

		float limited_dt = dt;
		if (limited_dt > 0.06f) // less than 17 FPS
		{
			limited_dt = 0.06f; //Slow game down instead of epic jumps
			slowDown = true;
		}
		mainClock += limited_dt;
		currentScene->Update(limited_dt);
	}

	currentScene->Draw();

#ifdef _DEBUG
	if (Debug::Draw) {
		DrawDebugVecs();
	}
#endif

	//Draw debug GUI

	vec saved_pos = Camera::pos;
	Camera::pos = vec(0,0);
	SDL_RenderSetScale(Window::renderer, 1, 1);
	
#ifdef _FPS_COUNTER
	fps_counter++;
	fpsClock += dt;
	if (fpsClock > 0.5f)
	{
		txt_fps->setString(std::to_string(int(fps_counter / fpsClock)) + (slowDown ? "!" : ""));
		slowDown = false;
		fps_counter = 0;
		fpsClock = 0;
	}
	Window::Draw(*txt_fps, vec(Window::WINDOW_WIDTH - 100, 10));
#endif

#ifdef _IMGUI
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
#endif
	Camera::pos = saved_pos;
	SDL_RenderSetScale(Window::renderer, Camera::zoom, Camera::zoom);

	SDL_RenderPresent(Window::renderer);
}

