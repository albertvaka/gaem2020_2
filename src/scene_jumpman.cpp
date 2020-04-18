#include "scene_jumpman.h"
#include "plant.h"
#include "input.h"
#include "imgui.h"
#include "bullet.h"
#include "assets.h"
#include "simplexnoise.h"
#include "savestation.h"
#include "debug.h"

const float batClusterSize = 22.f;
const float chanceAngryBat = 0.2f;
const float camSpeed = 2000;

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
	Debug::out << Camera::GetCameraCenter();
	//Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH / 2, Window::WINDOW_HEIGHT / 2));
	Debug::out << Camera::GetCameraCenter();
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
	for (auto* plant : Plant::getAll()) {
		if (Collide(plant->bounds(), player.bounds())) {
			if (!plant->IsBeingCarried()) {
				contextActionButton = GameKeys::ACTIVATE;
			}
			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				if (!plant->IsBeingCarried()) {
					plant->PickUpBy(&player);
				}
				else if (player.grounded) {
					// TODO: This assumes one player.
					plant->Drop();
				}
			}
		}
    plant->SetHitByLight(Collide(plant->bounds(), TiledAreas::sun));
    plant->SetHitByWater(Collide(plant->bounds(), TiledAreas::water));

		plant->Update(dt);
	}
}

void JumpScene::Draw(sf::RenderTarget& window)
{
	window.clear(sf::Color(34, 32, 52));

	window.draw(Assets::casaSprite);

	if (Debug::Draw) {
		map.Draw(window);
	}

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

	player.Draw(window);

	if (contextActionButton != GameKeys::NONE) {
		sf::Sprite& spr = Assets::hospitalSprite;
		spr.setPosition(player.bounds().TopRight() + vec(2, -6));
		AnimationType anim = BUTTON_A_PRESS; // TODO: switch depending on the key
		spr.setTextureRect(Animation::AnimFrame(anim, mainClock.getElapsedTime().asMilliseconds()));
		window.draw(spr);
	}

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


