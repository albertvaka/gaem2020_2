#include <map>

#define SDL_MAIN_HANDLED

#include <string>

#include "scene_manager.h"
#include "input.h"
#include "mates.h"
#include "assets.h"
#include "debug.h"

#include "scene_jumpman.h"
#include "intro_scene.h"

#ifdef _DEBUG
#include "imgui.h"
#include "imgui_sdl.h"
#include "imgui_impl_sdl.h"
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Scene* SceneManager::currentScene = nullptr;
float mainClock;

#define _FPS_COUNTER

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	Window::Init();

	Input::Init();

#ifdef _DEBUG
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Window::window, nullptr);
	ImGuiSDL::Initialize(Window::renderer, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
#endif

	Assets::LoadAll();

	srand(time(NULL));

#ifdef _FPS_COUNTER
	//sf::Text txt_fps;
	//txt_fps.setFont(Assets::font);
	//txt_fps.setPosition(Window::WINDOW_WIDTH - 100, 10);
	int fps_counter = 0;
#endif
	float fpsClock = 0.f;
	bool slowDown = false;

	int last_ticks = SDL_GetTicks();

	Scene* currentScene = new JumpScene();
	SceneManager::SetScene(currentScene);
	currentScene->EnterScene();
	while (true)
	{
		if (SceneManager::CurrentScene() != currentScene) {
			currentScene->ExitScene();
			delete currentScene;
			currentScene = SceneManager::CurrentScene();
			currentScene->EnterScene();
		}

#ifdef _DEBUG
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
			Camera::MoveCameraWithArrows(100.f, dt);
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

#ifdef _FPS_COUNTER
		fps_counter++;
		fpsClock += dt;
		if (fpsClock > 0.5f)
		{
			Debug::out << std::to_string(int(fps_counter / fpsClock)) + (slowDown ? "!" : "");
			//txt_fps.setString(std::to_string(int(fps_counter / fpsClock.restart().asSeconds())) + (slowDown ? "!" : ""));
			slowDown = false;
			fps_counter = 0;
			fpsClock = 0;
		}
		//window.draw(txt_fps);
#endif

#ifdef _DEBUG
		SDL_RenderSetScale(Window::renderer, 1, 1);
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		SDL_RenderSetScale(Window::renderer, Camera::zoom, Camera::zoom);
#endif

		SDL_RenderPresent(Window::renderer);

	}

#ifdef _DEBUG
	ImGui_ImplSDL2_Shutdown();
#endif

	SDL_DestroyWindow(Window::window);
	SDL_Quit();
}
