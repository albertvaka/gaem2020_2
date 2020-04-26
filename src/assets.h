#pragma once

#include <emyl.h>
#include <array>


struct SDL_Texture;
struct TTF_Font;

struct Assets
{
	static void LoadAll();


	static SDL_Texture* hospitalTexture;

	static std::array<SDL_Texture*, 3> sunTextures;

	static SDL_Texture* marioTexture;

	static SDL_Texture* spritesTexture;
	static SDL_Texture* npcTexture;

	static SDL_Texture* casaTexture;
	static SDL_Texture* plantTexture;

	static SDL_Texture* doggoTexture;

	static TTF_Font* font_30;
	static TTF_Font* font_30_outline;

	static Emyl::Buffer BufferBucketTomatoes;
	static Emyl::Sound soundBucketTomatoes;
	static Emyl::Buffer BufferBuy;
	static Emyl::Sound soundBuy;
	static Emyl::Buffer BufferSell1;
	static Emyl::Sound soundSell1;
	static Emyl::Buffer BufferSell2;
	static Emyl::Sound soundSell2;
	static Emyl::Buffer BufferWater;
	static Emyl::Sound soundWater;
	static Emyl::Buffer BufferBucketWater;
	static Emyl::Sound soundBucketWater;
	static Emyl::Buffer BufferJump1;
	static Emyl::Sound soundJump1;
	static Emyl::Buffer BufferJump2;
	static Emyl::Sound soundJump2;
	static Emyl::Buffer BufferLand;
	static Emyl::Sound soundLand;
	static Emyl::Buffer BufferPickupDrop;
	static Emyl::Sound soundPickupDrop;
	static Emyl::Buffer BufferDeath;
	static Emyl::Sound soundDeath;

	static Emyl::Buffer BufferDoggo1;
	static Emyl::Sound soundDoggo1;

	static Emyl::Buffer BufferDoggo2;
	static Emyl::Sound soundDoggo2;

	static Emyl::Buffer BufferDoggo3;
	static Emyl::Sound soundDoggo3;


	static Emyl::Music sceneMusic[2];
};

