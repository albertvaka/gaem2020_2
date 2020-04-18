#include "scene_jumpman.h"
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

	Camera::SetZoom(GameData::GAME_ZOOM);
	Camera::SetCameraCenter(vec(GameData::WINDOW_WIDTH / (2*GameData::GAME_ZOOM), GameData::WINDOW_HEIGHT/(2*GameData::GAME_ZOOM)));
	
	player.pos = vec(160,160);
	InitMap();

	player.pos = TiledEntities::spawn;
	map.LoadFromTiled();

	for (const sf::Vector2f& v : TiledEntities::save) {
		new SaveStation(v);
	}

	Camera::SetCameraCenter(player.pos);
}

void JumpScene::ExitScene()
{
	bulletPartSys.Clear();
	Bullet::deleteAll();
}

void JumpScene::Update(float dt)
{
	if (Keyboard::IsKeyJustPressed(GameKeys::RESTART)) {
		ExitScene();
		EnterScene();
	}
	
	player.Update(dt);

	Camera::ChangeZoomWithPlusAndMinus(10.f, dt);

	for (Bullet* e  : Bullet::getAll()) {
		e->Update(dt);
		if (e->explode) continue;

		bulletPartSys.pos = e->pos + vec::Rand(-4, -4, 4, 4);
		bulletPartSys.Spawn(dt);
	}
	Bullet::deleteNotAlive();

	bulletPartSys.UpdateParticles(dt);

	contextActionButton = GameKeys::NONE;
	for (SaveStation* ss : SaveStation::getAll()) {
		ss->Update(dt);
		if (Collide(ss->bounds(), player.bounds())) {
			contextActionButton = GameKeys::ACTIVATE;

			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				ss->enabled = !ss->enabled;
			}
		}
	}
}

void JumpScene::Draw(sf::RenderTarget& window)
{
	window.clear(sf::Color(31, 36, 50));

	map.Draw(window);

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
		//player.pos.Debuggerino(sf::Color::White);
		//player.bounds().Center().Debuggerino(sf::Color::Magenta);
	}

	//player.polvito.DrawImGUI("Polvito");
}



void JumpScene::InitMap() {
	player.pos = vec(160, 160);

	randomSeed = Random::roll(0, 10000);
	map.Randomize(randomSeed);

	sf::Vector2i pos = map.toTiles(player.pos);
	map.setTile(pos.x - 1, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 2, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 3, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 4, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 5, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 6, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 3, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x + 1, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x + 2, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x + 3, pos.y + 1, Tile::SOLID_1);
	map.setTile(pos.x - 1, pos.y, Tile::NONE);
	map.setTile(pos.x, pos.y, Tile::NONE);
	map.setTile(pos.x - 1, pos.y - 1, Tile::NONE);
	map.setTile(pos.x, pos.y - 1, Tile::NONE);
	map.setTile(pos.x - 1, pos.y - 2, Tile::NONE);
	map.setTile(pos.x, pos.y - 2, Tile::NONE);
	map.setTile(pos.x + 1, pos.y, Tile::RSLOPE_1);
	map.setTile(pos.x + 2, pos.y, Tile::SOLID_1);
	map.setTile(pos.x + 3, pos.y - 1, Tile::SOLID_1);
	map.setTile(pos.x + 3, pos.y, Tile::SOLID_1);
	map.setTile(pos.x + 2, pos.y - 1, Tile::RSLOPE_1);
	map.setTile(pos.x + 3, pos.y - 2, Tile::RSLOPE_1);
	map.setTile(pos.x + 4, pos.y - 2, Tile::SOLID_1);
	map.setTile(pos.x + 5, pos.y - 2, Tile::SOLID_1);
	map.setTile(pos.x - 4, pos.y, Tile::LSLOPE_1);
	map.setTile(pos.x - 5, pos.y, Tile::SOLID_1);
	map.setTile(pos.x - 5, pos.y - 1, Tile::LSLOPE_1);
	map.setTile(pos.x - 6, pos.y - 1, Tile::SOLID_1);
	map.setTile(pos.x - 6, pos.y, Tile::SOLID_1);
	map.setTile(pos.x - 6, pos.y - 2, Tile::LSLOPE_1);
	map.setTile(pos.x - 7, pos.y - 2, Tile::SOLID_1);
	map.setTile(pos.x - 8, pos.y - 2, Tile::SOLID_1);
	map.setTile(pos.x - 9, pos.y - 2, Tile::SOLID_1);
	map.setTile(pos.x - 10, pos.y - 2, Tile::SOLID_1);
}