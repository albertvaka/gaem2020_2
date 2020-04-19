#include "scene_jumpman.h"
#include "plant.h"
#include "input.h"
#include "imgui.h"
#include "assets.h"
#include "simplexnoise.h"
#include "savestation.h"
#include "debug.h"
#include "richtext.h"

extern sf::Clock mainClock;

JumpScene::JumpScene()
	: map(TiledMap::map_size.x, TiledMap::map_size.y)
{

}

void JumpScene::EnterScene() 
{
	player.Reset();

	player.pos = TiledEntities::spawn;
	map.LoadFromTiled();

	//new Plant(vec(8.0f, 8.0f) + TileMap::alignToTiles(310.0f, 260.0f));

	Camera::SetZoom(Window::GAME_ZOOM);
	Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH/4, Window::WINDOW_HEIGHT / 4));
	
	cistell.pos = TiledEntities::spawn;

	npc.timer = 0;
}

void JumpScene::ExitScene()
{
}

void JumpScene::Update(float dt)
{
	//Camera::MoveCameraWithArrows(50, dt);
	if (Keyboard::IsKeyJustPressed(GameKeys::RESTART)) {
		ExitScene();
		EnterScene();
	}
	
	player.Update(dt);

	Camera::ChangeZoomWithPlusAndMinus(20.f, dt);
	//Debug::out << Camera::GetCameraCenter();

	contextActionButton = GameKeys::NONE;

	npc.Update(dt);
	cistell.Update(dt);
	bool player_had_empty_hands = player.CanCarry();
  if (Collide(cistell.bounds(), player.bounds())) {
		bool can_carry = !cistell.IsBeingCarried() && player_had_empty_hands;
		bool can_drop = cistell.IsCarriedBy(&player) && player.grounded;

		// Agafar tom�quets.
		for (auto* plant : Plant::getAll()) {
      if (Collide(plant->bounds(), cistell.bounds()) && cistell.IsBeingCarried()) {
				// Agafar Tom�euts.
        if ((!cistell.contents) && plant->HasTomato()) {
          // TODO: Treure aix� si la collita passa automaticament.
          contextActionButton = GameKeys::ACTIVATE;
          if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			  Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
            plant->PickTomato();
            cistell.contents = Cistell::TOMATOES;
            can_drop = false;
            // Agafar tom�quets t� prioritat per sobre deixar anar la cistella.
          }
        }
				// Regar plantes.
				else if (cistell.contents == Cistell::WATER) {
					// TODO: Agafar la planta que necessiti m�s aigua?
          contextActionButton = GameKeys::ACTIVATE;
          if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			  Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
            plant->SetHitByWater();
            cistell.contents = Cistell::EMPTY;
            can_drop = false;
          }
				}

			}
		}
		// Agafar aigua.
		if (Collide(TiledAreas::water, cistell.bounds()) && cistell.IsBeingCarried() && (!cistell.contents)) {
			contextActionButton = GameKeys::ACTIVATE;
			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.contents = Cistell::WATER;
			}
			can_drop = false;
		}

		if (can_carry) {
			contextActionButton = GameKeys::ACTIVATE;
		}
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			if (can_drop) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.Drop();
				player.Carry(JumpMan::Holdable::None);
			} else if (can_carry) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.PickUpBy(&player);
				player.Carry(JumpMan::Holdable::Basket);
			}
		}
  }

	for (auto* plant : Plant::getAll()) {
		if (Collide(plant->bounds(), player.bounds())) {
			bool can_carry = !plant->IsBeingCarried() && player.CanCarry() && player_had_empty_hands;
			bool can_drop = plant->IsCarriedBy(&player) && player.grounded;
			if (can_carry) {
				contextActionButton = GameKeys::ACTIVATE;
			}
			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				if (can_drop) {
					Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
					plant->Drop();
					player.Carry(JumpMan::Holdable::None);
				} else if (can_carry) {
					Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
					plant->PickUpBy(&player);
					player.Carry(JumpMan::Holdable::Plant);
				}
			}
		}
		plant->SetHitByLight(Collide(plant->bounds(), TiledAreas::sun));

		plant->Update(dt);
		// For Debug
		if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_SET_PLANTS_AT_MAX_STATS)) {
			// Grow to the max.
			for (int i = 0; i < 5; ++ i) {
				plant->Grow();
			}
			plant->light = 100;
			plant->water = 100;
		}
	}


	if (npc.isSelling() && Collide(player.bounds(), TiledAreas::npc) && player.IsCarrying(JumpMan::Holdable::None)) {
		contextActionButton = GameKeys::ACTIVATE;
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
			if (moneys >= 100) {
				moneys -= 100;
				(new Plant(vec()))->PickUpBy(&player);
				player.Carry(JumpMan::Holdable::Plant);
			}
			else {
				cantbuyTimer = mainClock.getElapsedTime().asMilliseconds() + 1000;
			}
		}
	}

	if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_GET_MONEY)) {
		moneys += 100;
	}

}

void JumpScene::Draw(sf::RenderTarget& window)
{
	window.clear(sf::Color(34, 32, 52));

	window.draw(Assets::casaSprite);

	if (Debug::Draw) {
		map.Draw(window);
	}

	int globalMillis = mainClock.getElapsedTime().asMilliseconds();

	//Fountain
	sf::Sprite& spr = Assets::spritesSprite;
	spr.setPosition(420, 338);
	spr.setOrigin(0, 0);
	spr.setTextureRect(Animation::AnimFrame(FOUNTAIN, globalMillis));
	window.draw(spr);

	npc.Draw(window);

	for (auto* plant : Plant::getAll()) {
		plant->Draw(window);
	}
	
	cistell.Draw(window);
	player.Draw(window);

	//Truck
	spr.setPosition(702, 297);
	spr.setOrigin(0, 0);
	spr.setTextureRect(sf::IntRect(0, 8 * 16, 11 * 16 + 4, 72));
	window.draw(spr);

	if (contextActionButton != GameKeys::NONE) {
		sf::Sprite& spr = Assets::hospitalSprite;
		spr.setPosition(player.bounds().TopRight() + vec(2, -6));
		AnimationType anim = BUTTON_A_PRESS; // TODO: switch depending on the key
		spr.setTextureRect(Animation::AnimFrame(anim, globalMillis));
		window.draw(spr);
	}

	sfe::RichText text(Assets::font);
	text.setPosition(10, 10);
	text.setScale(0.8f, 0.8f);

	if (cantbuyTimer > globalMillis && (globalMillis/100)%2) {
		text << sf::Color::Red;
	}
	else {
		text << sf::Color::Cyan;
	}
	text << sfe::Outline(sf::Color::Black, 2) << "$" << std::to_string(moneys);
	window.draw(text);

	if (Debug::Draw) {
		player.bounds().Draw(window);
		for (const auto& plant : Plant::getAll()) {
			plant->bounds().Draw(window);
		}
		//player.pos.Debuggerino(sf::Color::White);
		//player.bounds().Center().Debuggerino(sf::Color::Magenta);
	}

	//player.polvito.DrawImGUI("Polvito");
}


