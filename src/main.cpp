#include <map>

#ifdef _DEBUG
#include "imgui.h"
#include "imgui-SFML.h"
#endif
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
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

int main()
{

	sf::RenderWindow window(sf::VideoMode(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT), "LD46");

	//window.setFramerateLimit(60);
#ifdef _DEBUG
	ImGui::SFML::Init(window);
#endif
	Input::Init(window);

	Assets::LoadAll();

	srand(time(NULL));

#ifdef _FPS_COUNTER
	sf::Text txt_fps;
	txt_fps.setFont(Assets::font);
	txt_fps.setPosition(Window::WINDOW_WIDTH - 100, 10);
	sf::Clock fpsClock;
	int fps_counter = 0;
#endif
	bool slowDown = false;

	sf::Clock dtClock;

	Scene* currentScene = new IntroScene();
	SceneManager::SetScene(currentScene);
	currentScene->EnterScene();
	while (window.isOpen())
	{
		if (SceneManager::CurrentScene() != currentScene) {
			currentScene->ExitScene();
			delete currentScene;
			currentScene = SceneManager::CurrentScene();
			currentScene->EnterScene();
		}

		sf::Time time = dtClock.restart();

		Input::Update(time);

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
			Camera::MoveCameraWithArrows(100.f, time.asSeconds());
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
			DrawDebugVecs(&window);
		}
#endif

		Camera::StartGuiDraw();

#ifdef _FPS_COUNTER
		fps_counter++;
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f)
		{
			txt_fps.setString(std::to_string(int(fps_counter / fpsClock.restart().asSeconds())) + (slowDown ? "!" : ""));
			slowDown = false;
			fps_counter = 0;
		}
		window.draw(txt_fps);
#endif

#ifdef _DEBUG
		ImGui::SFML::Render(window);
#endif
		Camera::EndGuiDraw();

		window.display();
	}

#ifdef _DEBUG
	ImGui::SFML::Shutdown();
#endif
}
