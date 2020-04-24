#pragma once

#include <string>

#include "scene_manager.h"
#include "mates.h"
#include "input.h"
#include "doggo.h"
#include "assets.h"
#include "text.h"
//#include "richtext.h"
#include "scene_jumpman.h"

extern float mainClock;

struct IntroScene : Scene {
	
	Text text;
	RotoText rototext;
	//sfe::RichText credits;

	IntroScene() : text(Assets::font_30, Assets::font_30_outline) /*, credits(Assets::font)*/  {
		Camera::SetZoom(Window::GAME_ZOOM);
		Camera::SetCenter(vec(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 4));
	}

	void EnterScene() override
	{
		Assets::soundDoggo1.setVolume(0.f);
		Assets::soundDoggo2.setVolume(0.f);
		Assets::soundDoggo3.setVolume(0.f);

		new Doggo();

		rototext.ShowMessage("Who let the doggos in?");
		rototext.Update(100);

		text.setString("PRESS START");
		text.setFillColor(255,255,255);
		text.setOutlineColor(0, 0, 0);
		/*

		credits << "A game by:\n\nAlbert Martinez\nAlbert Vaca Cintora\n\nMusic by:\n\nVeuskemini";
		credits.setPosition(15, 300);
		credits.setScale(0.39f, 0.45f);
				*/
	}

	void ExitScene() override {
		Doggo::deleteAll();
		Assets::soundDoggo1.setVolume(100.f);
		Assets::soundDoggo1.stop();
		Assets::soundDoggo2.setVolume(100.f);
		Assets::soundDoggo2.stop();
		Assets::soundDoggo3.setVolume(100.f);
		Assets::soundDoggo3.stop();
	}

	void Update(float dt) override {
		rototext.Update(dt);
		for (Doggo* doggo : Doggo::getAll()) {
			doggo->Update(dt);
			if (doggo->wantFood) {
				doggo->anim.current_frame = (int(mainClock*1000)/200)%2;
				doggo->wantFood = false;
			}
		}
		if (Keyboard::IsKeyJustPressed(GameKeys::START)) {
			SceneManager::SetScene(new JumpScene());
			//Change scene
		}
	}

	void Draw() override
	{
		Window::Clear(34, 32, 52);

		Window::Draw(Assets::casaTexture, vec(0,0));
		for (Doggo* doggo : Doggo::getAll()) {
			doggo->Draw();
		}

		rototext.Draw();
		
		if ((int(mainClock*1000)/350)%2) {
			Window::Draw(text, vec(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 3 + 55)).withScale(0.65f).withOrigin(text.getSize().x/2,0);
		}

		/*
		int i = 0;
		for (auto line : credits.getLines()) {
			auto p = line.getPosition();
			if (i++ > 0) {
				p.y -= 10;
				if (i > 4) {
					p.y -= 10;
					if (i > 6) {
						p.y -= 10;
					}
				}
			}
			line.setPosition(p);
			window.draw(line, credits.getTransform());
		}
		*/
	}

};
