#pragma once

#include <SFML/Graphics.hpp>
#include <array>

struct Assets
{
	static void LoadAll();

	static sf::Texture hospitalTexture;
	static sf::Sprite hospitalSprite;

	static sf::Texture marioTexture;
	static sf::Sprite marioSprite;

	static sf::Texture spritesTexture;
	static sf::Sprite spritesSprite;
	static sf::Texture npcTexture;
	static sf::Sprite npcSprite;

	static sf::Texture casaTexture;
	static sf::Sprite casaSprite;
	static sf::Texture plantTexture;

	static sf::Font font;

	static sf::Shader tintShader;
};

