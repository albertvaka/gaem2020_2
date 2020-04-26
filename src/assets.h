#pragma once

#include <array>

#include "Sound.h"


struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;
typedef struct _Mix_Music Mix_Music;

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

	static Sound soundBucketTomatoes;
	static Sound soundBuy;
	static Sound soundSell1;
	static Sound soundSell2;
	static Sound soundWater;
	static Sound soundBucketWater;
	static Sound soundJump1;
	static Sound soundJump2;
	static Sound soundLand;
	static Sound soundPickupDrop;
	static Sound soundDeath;

	static Sound soundDoggo1;
	static Sound soundDoggo2;
	static Sound soundDoggo3;

	static Mix_Music* sceneMusic[2];
};

