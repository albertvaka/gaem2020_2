#include "window.h"

#include "assets.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

GPU_Image* Assets::hospitalTexture;

std::array<GPU_Image*, 3> Assets::sunTextures;	

GPU_Image* Assets::marioTexture;

GPU_Image* Assets::casaTexture;
GPU_Image* Assets::plantTexture;

GPU_Image* Assets::spritesTexture;
GPU_Image* Assets::npcTexture;

GPU_Image* Assets::doggoTexture;

TTF_Font* Assets::font_30;
TTF_Font* Assets::font_30_outline;

Sound Assets::soundBucketTomatoes;
Sound Assets::soundBuy;
Sound Assets::soundSell1;
Sound Assets::soundSell2;
Sound Assets::soundWater;
Sound Assets::soundBucketWater;
Sound Assets::soundJump1;
Sound Assets::soundJump2;
Sound Assets::soundLand;
Sound Assets::soundPickupDrop;
Sound Assets::soundDeath;

Sound Assets::soundDoggo1;

Sound Assets::soundDoggo2;

Sound Assets::soundDoggo3;

Mix_Music* Assets::sceneMusic[2];

Shader Assets::tintShader;

GPU_Image* loadImage(const std::string& path) {

    GPU_Image* texture = GPU_LoadImage(path.c_str());
    if (!texture) {
        Debug::out << "Unable to load image '" << path.c_str() << "': " << IMG_GetError();
        return nullptr;
    }
    GPU_SetImageFilter(texture, GPU_FILTER_NEAREST);
    return texture;
}

TTF_Font* loadFont(const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        Debug::out << "Unable to load font '" << path.c_str() << "': " << TTF_GetError();
    }
    return font;
}
TTF_Font* loadFontOutline(const std::string& path, int size, int outline) {
    TTF_Font* font = loadFont(path, size);
    TTF_SetFontOutline(font, outline);
    return font;
}

Mix_Music* loadMusic(const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        Debug::out << "Unable to load music '" << path.c_str() << "': " << Mix_GetError();
    }
    return music;
}

void Assets::LoadAll() {

    hospitalTexture = loadImage("data/spritesheet.png");
    marioTexture = loadImage("data/mario.png");

    for (int i = 0; i < 3; ++i) {	
      std::string filename = "data/sun" + std::to_string(i) + ".png";	
      sunTextures[i] = loadImage(filename);
    }
    spritesTexture = loadImage("data/sprites.png");
    npcTexture = loadImage("data/npc.png");
    casaTexture = loadImage("data/bg.png");
    doggoTexture = loadImage("data/doggo.png");
    plantTexture = loadImage("data/plant.png");

    font_30 = loadFont("data/PressStart2P.ttf", 30);
    font_30_outline = loadFontOutline("data/PressStart2P.ttf", 30, 3);
    
    soundDoggo1.load("data/doggo1.ogg");
    soundDoggo2.load("data/doggo2.ogg");
    soundDoggo3.load("data/doggo3.ogg");

    soundBuy.load("data/buy.ogg");
    soundSell1.load("data/sell1.ogg");
    soundSell2.load("data/sell2.ogg");
    soundDeath.load("data/death.ogg");

    soundBucketTomatoes.load("data/bucket_tomatoes.ogg");
    soundBucketWater.load("data/bucket_water.ogg");
    soundWater.load("data/water.ogg");
    soundPickupDrop.load("data/pickup_drop.ogg");

    soundJump1.load("data/jump1.ogg");
    soundJump1.setVolume(50);
    soundJump2.load("data/jump2.ogg");
    soundJump2.setVolume(50);
    soundLand.load("data/land.ogg");

    sceneMusic[0] = loadMusic("data/plantetes_gameplay.ogg");
    sceneMusic[1] = loadMusic("data/plantetes_menu.ogg");
    MusicPlayer::SetVolume(60);

    tintShader.Build()
        .withVertex("data/default.vert")
        .withFragment("data/tint.frag");

}
