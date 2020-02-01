#include <map>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include "entity_system.h"
#include "game_data.h"
#include "input.h"
#include "mates.h"
#include "player.h"
#include "cadaver.h"
#include "pared.h"
#include "spawner.h"
#include "mesa.h"


sf::Font font;
sf::Texture texture;
sf::Sprite sprite;


const int TILE_SIZE = 16;

std::vector< std::string > mapita_inicial = { // (23 * 17 tiles)
"XXXXXXXXXXXSXXXXXXXXXXX",
"XX0      XDDBXXXXXXXXXX",
"XX XXXXX XAXBX       XX",
"X  X   X XAXBX XXXXX XX",
"X  XFGFX XACCX X   X XX",
"XX X   X       XFGFX XX",
"XX XX XX       X   X XX",
"XX       XXXXX XX XX XX",
"XX XXXXX X   X       XX",
"XX X   X XFGFX XXXXX XX",
"XX XFGFX X   X X   X XX",
"XX X   X XX XX XFGFX  X",
"XX XX XX X   X X   X  X",
"XX             XX XX XX",
"XXXXXXXXXXXBX        XX",
"CCCCCCCCCCCCXXXXXXXXXXX",
};

enum TileType
{
	WALL,
	FLOOR
};

std::vector< std::vector<TileType> > mapita;

std::vector< std::vector<bool> > passable;

TileType TileFromChar(char c)
{
	switch (c)
	{
		case 'X':
		{
			return TileType::WALL;
		} break;
	}
	return TileType::FLOOR;
}

void LoadGame(sf::RenderWindow& window)
{
	texture.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	Input::Init(window);
	Camera::SetZoom(4.f);
	Camera::SetCameraCenter(vec(GameData::WINDOW_WIDTH / 8, GameData::WINDOW_HEIGHT/8));

	passable.resize(mapita_inicial[0].size(), std::vector<bool>(mapita_inicial.size()));
	mapita.resize(mapita_inicial[0].size(), std::vector<TileType>(mapita_inicial.size()));


	int x = 0, y = 0;
	for (auto row : mapita_inicial) 
	{
		for (char c : row) 
		{
			vec pos(16 * x, 16 * y);
			switch (c) 
			{
				case '0': new Player(0, pos); break;
				case '1': new Player(1, pos); break;
				case '2': new Player(2, pos); break;
				case '3': new Player(3, pos); break;
				case 'X': new Pared(pos); break;
				case 'A': new Cinta(pos, EntityDirection::UP); break;
				case 'B': new Cinta(pos, EntityDirection::DOWN); break;
				case 'C': new Cinta(pos, EntityDirection::LEFT); break;
				case 'D': new Cinta(pos, EntityDirection::RIGHT); break;
				case 'G': new Mesa(pos); break;
				case 'S': 
					new Spawner(pos); 
					new Cinta(pos, EntityDirection::DOWN); 
					break;
				
			}

			//passable[x][y] = (c != 'X' && c != 'G' && c!= 'F');
			passable[x][y] = (c != 'X' && c != 'G' && c != 'F' && c !='A' &&  c != 'B' &&  c != 'C' &&  c != 'D');
			mapita[x][y] = TileFromChar(c);
			x += 1;
		}
		y += 1;
		x = 0;
	}

	loadExtremityMap();
}

void DrawGui()
{
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	ImGui::Text(EntS<Player>::getAll()[0]->pos.ToString().c_str());
	if (ImGui::Button("SPAWN CADAVER"))
	{
		for (Spawner* s : EntS<Spawner>::getAll()) {
			s->spawn();
		}
	}

	ImGui::End();
}

sf::IntRect TileTex(TileType type)
{
	if (type == TileType::FLOOR)
	{
		return sf::IntRect(64, 48, 16, 16);
	}
	if (type == TileType::WALL)
	{
		return sf::IntRect(64+16, 48, 16, 16);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_WIDTH, GameData::WINDOW_HEIGHT), GameData::GAME_TITLE);
	LoadGame(window);

	int fps_counter = 0;
	sf::Clock dtClock;
	sf::Clock fpsClock;

	sf::Text txt_fps;
	txt_fps.setPosition(10, 10);
	txt_fps.setFont(font);

	while (window.isOpen()) 
	{
		sf::Time time = dtClock.restart();

		Input::Update(time);

		//#if _DEBUG
		//Camera::MoveCameraWithArrows(50, time.asSeconds());
		//Camera::ChangeZoomWithPlusAndMinus(0.5f, time.asSeconds());
		//#endif

		UpdateEntities(time.asMilliseconds());


		window.clear(sf::Color(100, 100, 200));


		for (int i = 0; i < mapita.size(); ++i)
		{
			for (int j = 0; j < mapita[i].size(); ++j)
			{
				sprite.setPosition(i*TILE_SIZE, j*TILE_SIZE);

				sprite.setTextureRect(TileTex(mapita[i][j]));

				window.draw(sprite);
				
			}
		}

		DrawEntities(sprite, window);
		//DrawEntities(texture, window);

		Camera::StartGuiDraw();
		DrawGui();
		ImGui::SFML::Render(window);
		fps_counter++;
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f) 
		{
			txt_fps.setString(std::to_string(static_cast<int>(fps_counter / fpsClock.restart().asSeconds())));
			fps_counter = 0;
		}
		window.draw(txt_fps);
		Camera::EndGuiDraw();
		
		window.display();
	}

	ImGui::SFML::Shutdown();
}
