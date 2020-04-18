#pragma once

#include <array>

#include <SFML/Graphics.hpp>

struct TiledTiles
{
	static const sf::IntRect tileToTextureRect[];

	enum Value : unsigned short
	{
		NONE = 0,
		ONEWAY_1,
		RSLOPE_1,
		LSLOPE_1,
		SOLID_1,
		SOLID_2,
		SOLID_3,
		BREAKABLE_1,
		SOLID_TRANSPARENT,
	};

	static const Value ONEWAY_BEGIN = ONEWAY_1;
	static const Value RSLOPE_BEGIN = RSLOPE_1;
	static const Value LSLOPE_BEGIN = LSLOPE_1;
	static const Value SOLID_BEGIN = SOLID_1;
	static const Value BREAKABLE_BEGING = BREAKABLE_1;

	// Aliases

};

struct TiledMap
{
	static const unsigned short map[];
	static const sf::Vector2f map_size;
	static const std::array<sf::Rect<float>, 0> screens;
};

struct TiledEntities
{
	static const sf::Vector2f spawn;
	
};

struct TiledAreas
{
	static const sf::Rect<float> sun;
	static const sf::Rect<float> water;
	static const sf::Rect<float> truck;
	static const sf::Rect<float> npc;
	
};