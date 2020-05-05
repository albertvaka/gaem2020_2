#pragma once

#include <array>

#include "sound.h"
#include "shader.h"

struct GPU_Image;
typedef struct _TTF_Font TTF_Font;
typedef struct _Mix_Music Mix_Music;

struct Assets
{
	static void LoadAll();


	static GPU_Image* hospitalTexture;

	static std::array<GPU_Image*, 3> sunTextures;

	static GPU_Image* marioTexture;

	static GPU_Image* spritesTexture;
	static GPU_Image* npcTexture;

	static GPU_Image* casaTexture;
	static GPU_Image* plantTexture;

	static GPU_Image* doggoTexture;

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

	static Shader tintShader;
};

