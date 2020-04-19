#include "scene_jumpman.h"
#include "plant.h"
#include "input.h"
#include "imgui.h"
#include "bullet.h"
#include "assets.h"
#include "simplexnoise.h"
#include "savestation.h"
#include "debug.h"
#include "richtext.h"

extern sf::Clock mainClock;

JumpScene::JumpScene()
	: map(TiledMap::map_size.x, TiledMap::map_size.y)
{
	bulletPartSys.AddSprite(Assets::marioTexture, sf::IntRect(5, 37, 6, 6));

	float vel = 15;
	bulletPartSys.max_vel = vec(vel, vel);
	bulletPartSys.min_vel = vec(-vel, -vel);
	bulletPartSys.min_ttl = 0.5f;
	bulletPartSys.max_ttl = 1.f;
	bulletPartSys.min_interval = 0.03f;
	bulletPartSys.max_interval = 0.06f;
	bulletPartSys.min_scale = 0.5f;
	bulletPartSys.max_scale = 0.9f;
	bulletPartSys.scale_vel = -2.5f;
	bulletPartSys.min_rotation = 0.f;
	bulletPartSys.max_rotation = 360.f;
	bulletPartSys.rotation_vel = 180.f;
	bulletPartSys.alpha = 0.75f;

}

void JumpScene::EnterScene() 
{
	player.Reset();

	player.pos = TiledEntities::spawn;
	map.LoadFromTiled();

	new Plant(vec(8.0f, 8.0f) + TileMap::alignToTiles(310.0f, 260.0f));

	Camera::SetZoom(Window::GAME_ZOOM);
	Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH/4, Window::WINDOW_HEIGHT / 4));
	
	cistell.pos = TiledEntities::spawn;

	npc.timer = 0;
}

void JumpScene::ExitScene()
{
	bulletPartSys.Clear();
	Bullet::deleteAll();
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
	for (Bullet* e  : Bullet::getAll()) {
		e->Update(dt);
		if (e->explode) continue;

		bulletPartSys.pos = e->pos + vec::Rand(-4, -4, 4, 4);
		bulletPartSys.Spawn(dt);
	}
	Bullet::deleteNotAlive();

	bulletPartSys.UpdateParticles(dt);

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
				cistell.contents = Cistell::WATER;
			}
			can_drop = false;
		}

		if (can_carry) {
			contextActionButton = GameKeys::ACTIVATE;
		}
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			if (can_drop) {
				cistell.Drop();
				player.Carry(JumpMan::Holdable::None);
			} else if (can_carry) {
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
					plant->Drop();
					player.Carry(JumpMan::Holdable::None);
				} else if (can_carry) {
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
}

void JumpScene::Draw(sf::RenderTarget& window)
{
	window.clear(sf::Color(34, 32, 52));

	window.draw(Assets::casaSprite);

	if (Debug::Draw) {
		map.Draw(window);
	}

	//Fountain
	sf::Sprite& spr = Assets::spritesSprite;
	spr.setPosition(420, 338);
	spr.setOrigin(0, 0);
	spr.setTextureRect(Animation::AnimFrame(FOUNTAIN, mainClock.getElapsedTime().asMilliseconds()));
	window.draw(spr);

	for (auto* plant : Plant::getAll()) {
		plant->Draw(window);
	}

	for (const SaveStation* ss : SaveStation::getAll()) {
		ss->Draw(window);
	}

	bulletPartSys.Draw(window);

	for (const Bullet* e : Bullet::getAll()) {
		e->Draw(window);
		if (Debug::Draw) {
			e->drawBounds(window);
		}
	}

	npc.Draw(window);

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
		spr.setTextureRect(Animation::AnimFrame(anim, mainClock.getElapsedTime().asMilliseconds()));
		window.draw(spr);
	}

	sfe::RichText text(Assets::font);
	text.setPosition(10, 10);
	text.setScale(0.8f, 0.8f);
	text << sfe::Outline(sf::Color::Black, 2) << sf::Color::Cyan << "$" << std::to_string(moneys);
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


