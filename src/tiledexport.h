#pragma once

#include <array>

#include "vector.h"
#include "window.h"
#include "bounds.h"

#include <SFML/Graphics.hpp>

struct TiledTiles
{
	static const IntRect tileToTextureRect[];

	enum Value : unsigned short
	{
		NONE = 0,
		ONEWAY_1,
		RSLOPE_1,
		LSLOPE_1,
		SOLID_1,
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
	static const vec map_size;
	static const std::array<Bounds, 0> screens;
};

struct TiledEntities
{
	static const vec spawn;
	static const std::array<vec, 8> waypoint;
	static const vec doggo_begin;
	static const vec doggo_end;
	
};

struct TiledAreas
{
	static const Bounds sun;
	static const Bounds water;
	static const Bounds truck;
	static const Bounds npc;
	
};