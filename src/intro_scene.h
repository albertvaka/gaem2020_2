#pragma once

#include <string>
#include <array>

#include "scene_manager.h"
#include "mates.h"
#include "input.h"
#include "doggo.h"
#include "assets.h"
#include "text.h"
#include "scene_jumpman.h"
#include "bat.h"

extern float mainClock;

struct IntroScene : Scene {
	
	TileMap map;
	Text credits;
	Text text;
	RotoText rototext;

	IntroScene() : text(Assets::font_30, Assets::font_30_outline), credits(Assets::font_30, Assets::font_30_outline)
		, map(TiledMap::map_size.x, TiledMap::map_size.y) {
		Camera::SetZoom(Window::GAME_ZOOM, false);
			map.LoadFromTiled();
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
		
		credits.setString("A game by:\n\nAlbert Martinez\nAlbert Vaca Cintora\n\nMusic by:\n\nVeuskemini");

	}

	void ExitScene() override {
		Doggo::deleteAll();
		Bat::deleteAll();
		Assets::soundDoggo1.setVolume(100.f);
		Assets::soundDoggo2.setVolume(100.f);
		Assets::soundDoggo3.setVolume(100.f);
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

		for (int player = 0; player < PlayerInput::kMaxPlayers; ++player) {
			if (PlayerInput::IsActionJustPressed(player, GameKeys::START)) {
        SceneManager::SetScene(new JumpScene(player));
        //Change scene
			}
		}

		if (PlayerInput::IsActionJustPressed(0, GameKeys::DEBUG_KILLALL)) {
			new Bat(vec::Rand(vec::Zero, Camera::GetSize()), true);
		}
		
		for (Bat* b : Bat::getAll()) {
			b->Update(dt);
		}

	}

	void Draw() override
	{
		Window::Clear(34, 32, 52);

		Window::Draw(Assets::casaTexture, vec(0,0));

		for (Doggo* doggo : Doggo::getAll()) {
			doggo->Draw();
		}
		
		for (Bat* b : Bat::getAll()) {
			b->Draw();

			if (Debug::Draw) {
				b->DrawSenseArea();
			}
		}

		rototext.Draw();
		
		if ((int(mainClock*1000)/350)%2) {
			Window::Draw(text, Camera::GetCenter()+vec(0, 90))
				.withScale(0.65f)
				.withOrigin(text.getSize().x/2,0);
		}

		Window::Draw(credits, vec(15, 300)).withScale(0.39f, 0.45f);
	}

};
