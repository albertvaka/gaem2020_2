#include <map>

#ifdef _DEBUG
#include "imgui.h"
#endif

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "scene_manager.h"
#include "input.h"
#include "mates.h"
#include "assets.h"
#include "debug.h"

#include "scene_jumpman.h"
#include "intro_scene.h"

Scene* SceneManager::currentScene = nullptr;
float mainClock;

#define _FPS_COUNTER

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG); // | IMG_INIT_JPG

	SDL_Window* window = SDL_CreateWindow("LD46_SDL", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	Window::window = window;
	Window::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //
	if (Window::renderer == NULL) {
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}
	//SDL_Rect viewport = { 0,0, Window::WINDOW_WIDTH,Window::WINDOW_HEIGHT };
	//SDL_RenderSetViewport(Window::renderer, &viewport);

#ifdef _DEBUG
	//ImGui::SFML::Init(window);
#endif
	Input::Init(window);

	Assets::LoadAll();

	srand(time(NULL));

#ifdef _FPS_COUNTER
	//sf::Text txt_fps;
	//txt_fps.setFont(Assets::font);
	//txt_fps.setPosition(Window::WINDOW_WIDTH - 100, 10);
	sf::Clock fpsClock;
	int fps_counter = 0;
#endif
	bool slowDown = false;

	sf::Clock dtClock;

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

		sf::Time time = dtClock.restart();

		//Input::Update(time);
		SDL_Event event;
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			}
		}

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
			//Camera::MoveCameraWithArrows(100.f, time.asSeconds());
		}

		if (!frameByFrame || Keyboard::IsKeyJustPressed(DEBUG_FRAME_BY_FRAME_NEXT) || Keyboard::IsKeyJustPressed(RESTART))
#endif
		{
#ifdef _DEBUG
			ClearDebugVecs();
#endif
			float dt = time.asSeconds();
			if (dt> 0.06f) // less than 17 FPS
			{
				dt = 0.06f; //Slow game down instead of epic jumps
				slowDown = true;
			}
			mainClock += dt;
			currentScene->Update(dt);
		}

		currentScene->Draw();

#ifdef _DEBUG
		if (Debug::Draw) {
			DrawDebugVecs();
		}
#endif

		//Camera::StartGuiDraw();

#ifdef _FPS_COUNTER
		fps_counter++;
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f)
		{
			Debug::out << std::to_string(int(fps_counter / fpsClock.restart().asSeconds())) + (slowDown ? "!" : "");
			//txt_fps.setString(std::to_string(int(fps_counter / fpsClock.restart().asSeconds())) + (slowDown ? "!" : ""));
			slowDown = false;
			fps_counter = 0;
		}
		//window.draw(txt_fps);
#endif

#ifdef _DEBUG
		//ImGui::SFML::Render();
#endif
		//Camera::EndGuiDraw();


		//SDL_RenderClear(Window::renderer);
		//SDL_RenderCopy(Window::renderer, Assets::casaTexture, NULL, NULL);

		//Update the surface
		SDL_RenderPresent(Window::renderer);

	}

#ifdef _DEBUG
	//ImGui::SFML::Shutdown();
#endif

	SDL_DestroyWindow(window);
	SDL_Quit();
}
