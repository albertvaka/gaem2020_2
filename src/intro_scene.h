#pragma once

#include <string>

#include "scene_manager.h"
#include "mates.h"
#include "input.h"
#include "doggo.h"
#include "assets.h"
#include "scene_jumpman.h"

extern sf::Clock mainClock;

struct IntroScene : Scene {

	sf::Text text;
	RotoText rototext;

	IntroScene() {
		Camera::SetZoom(Window::GAME_ZOOM);
		Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 4));

	}

	void EnterScene() override
	{
		Assets::soundDoggo1.setVolume(0.f);
		Assets::soundDoggo2.setVolume(0.f);
		Assets::soundDoggo3.setVolume(0.f);

		rototext.setCharacterSize(28);
		rototext.ShowMessage("Who let the doggos in?");

		new Doggo();

		text.setFont(Assets::font);
		text.setPosition(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 3 + 55);
		text.setString("PRESS START");
		
		text.setOutlineColor(sf::Color(0,0,0,255));
		text.setOutlineThickness(2);
		text.setOrigin(text.getLocalBounds().width/2,0);
		text.setScale(0.65f, 0.65f);

	}

	void ExitScene() override {
		Doggo::deleteAll();
		Assets::soundDoggo1.setVolume(100.f);
		Assets::soundDoggo2.setVolume(100.f);
		Assets::soundDoggo3.setVolume(100.f);

	}

	void Update(float dt) override {
		rototext.Update(dt);
		for (Doggo* doggo : Doggo::getAll()) {
			doggo->Update(dt);
			doggo->wantFood = false;
		}
		if (Keyboard::IsKeyJustPressed(GameKeys::START) || GamePad::IsButtonJustPressed(0, GamePad::Button::A)) {
			SceneManager::SetScene(new JumpScene());
			//Change scene
		}
	}

	void Draw(sf::RenderTarget& window) override
	{
		window.clear(sf::Color(34, 32, 52));

		window.draw(Assets::casaSprite);
		for (Doggo* doggo : Doggo::getAll()) {
			doggo->Draw(window);
		}

		rototext.Draw(window);
		
		if ((mainClock.getElapsedTime().asMilliseconds()/350)%2) {
			window.draw(text);
		}

	}

};
