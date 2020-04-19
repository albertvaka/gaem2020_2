#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

struct Assets
{
	static void LoadAll();


	static sf::Texture hospitalTexture;
	static sf::Sprite hospitalSprite;

	

  static std::array<sf::Texture, 3> sunTextures;	
	static std::array<sf::Sprite, 3> sunSprites;

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

	static sf::SoundBuffer soundBucketTomatoes;
	static sf::SoundBuffer soundBuy;
	static sf::SoundBuffer soundSell1;
	static sf::SoundBuffer soundSell2;
	static sf::SoundBuffer soundWater;
	static sf::SoundBuffer soundBucketWater;
	static sf::SoundBuffer soundJump1;
	static sf::SoundBuffer soundJump2;
	static sf::SoundBuffer soundLand;
	static sf::SoundBuffer soundPikcupDrop;
	static sf::SoundBuffer soundDeath;
	
};

