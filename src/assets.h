#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

struct Assets
{
	static void LoadAll();


	static sf::Texture hospitalTexture;

	static std::array<sf::Texture, 3> sunTextures;

	static sf::Texture marioTexture;

	static sf::Texture spritesTexture;
	static sf::Texture npcTexture;

	static sf::Texture casaTexture;
	static sf::Texture plantTexture;

	static sf::Texture doggoTexture;
	
	/*
	static sf::Font font;
		*/

	static sf::SoundBuffer soundBufferBucketTomatoes;
	static sf::Sound soundBucketTomatoes;
	static sf::SoundBuffer soundBufferBuy;
	static sf::Sound soundBuy;
	static sf::SoundBuffer soundBufferSell1;
	static sf::Sound soundSell1;
	static sf::SoundBuffer soundBufferSell2;
	static sf::Sound soundSell2;
	static sf::SoundBuffer soundBufferWater;
	static sf::Sound soundWater;
	static sf::SoundBuffer soundBufferBucketWater;
	static sf::Sound soundBucketWater;
	static sf::SoundBuffer soundBufferJump1;
	static sf::Sound soundJump1;
	static sf::SoundBuffer soundBufferJump2;
	static sf::Sound soundJump2;
	static sf::SoundBuffer soundBufferLand;
	static sf::Sound soundLand;
	static sf::SoundBuffer soundBufferPickupDrop;
	static sf::Sound soundPickupDrop;
	static sf::SoundBuffer soundBufferDeath;
	static sf::Sound soundDeath;

	static sf::SoundBuffer soundBufferDoggo1;
	static sf::Sound soundDoggo1;

	static sf::SoundBuffer soundBufferDoggo2;
	static sf::Sound soundDoggo2;

	static sf::SoundBuffer soundBufferDoggo3;
	static sf::Sound soundDoggo3;


	static sf::Music sceneMusic[2];
};

