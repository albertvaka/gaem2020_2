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

<<<<<<< HEAD
	static sf::Texture plantTexture;

	static sf::Texture fogTexture;
=======
	static sf::Texture casaTexture;
	static sf::Sprite casaSprite;
>>>>>>> a02cb5501132c46e0461a29dcbf7de1e66600446

	static sf::Font font;

	static sf::Shader tintShader;
};

