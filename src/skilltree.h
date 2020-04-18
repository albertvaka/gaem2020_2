#pragma once

#include "singleinstance.h"
#include <SFML/Graphics.hpp>

struct SkillTree : SingleInstance<SkillTree>
{
	enum Skill {
		BREAK = 0,
		BOUNCY = 1,
		RANGE_1 = 2,
		RAPID_FIRE = 3,
		DMG_1 = 4,
		RANGE_2 = 5,
	};

	SkillTree();
	void Update(float dt);
	void DrawMenu(sf::RenderTarget& window) const;
	void DrawOverlay(sf::RenderTarget& window) const;

	bool open = false;
	int gunpoints = 0;
	sf::Vector2i prevIndex;
	sf::Vector2i index;

};

