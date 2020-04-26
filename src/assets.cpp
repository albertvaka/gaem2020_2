#include "window.h"

#include "assets.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

SDL_Texture* Assets::hospitalTexture;

std::array<SDL_Texture*, 3> Assets::sunTextures;	

SDL_Texture* Assets::marioTexture;

SDL_Texture* Assets::casaTexture;
SDL_Texture* Assets::plantTexture;

SDL_Texture* Assets::spritesTexture;
SDL_Texture* Assets::npcTexture;

SDL_Texture* Assets::doggoTexture;

TTF_Font* Assets::font_30;
TTF_Font* Assets::font_30_outline;

Emyl::Buffer Assets::BufferBucketTomatoes;
Emyl::Sound Assets::soundBucketTomatoes;
Emyl::Buffer Assets::BufferBuy;
Emyl::Sound Assets::soundBuy;
Emyl::Buffer Assets::BufferSell1;
Emyl::Sound Assets::soundSell1;
Emyl::Buffer Assets::BufferSell2;
Emyl::Sound Assets::soundSell2;
Emyl::Buffer Assets::BufferWater;
Emyl::Sound Assets::soundWater;
Emyl::Buffer Assets::BufferBucketWater;
Emyl::Sound Assets::soundBucketWater;
Emyl::Buffer Assets::BufferJump1;
Emyl::Sound Assets::soundJump1;
Emyl::Buffer Assets::BufferJump2;
Emyl::Sound Assets::soundJump2;
Emyl::Buffer Assets::BufferLand;
Emyl::Sound Assets::soundLand;
Emyl::Buffer Assets::BufferPickupDrop;
Emyl::Sound Assets::soundPickupDrop;
Emyl::Buffer Assets::BufferDeath;
Emyl::Sound Assets::soundDeath;

Emyl::Buffer Assets::BufferDoggo1;
Emyl::Sound Assets::soundDoggo1;

Emyl::Buffer Assets::BufferDoggo2;
Emyl::Sound Assets::soundDoggo2;

Emyl::Buffer Assets::BufferDoggo3;
Emyl::Sound Assets::soundDoggo3;

Emyl::Music Assets::sceneMusic[2];

SDL_Texture* loadImage(const std::string& path) {

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (!texture) {
        printf("Unable to create texture image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }


    SDL_FreeSurface(surface);

    return texture;
}

TTF_Font* loadFont(const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        printf("Unable to load font %s! SDL_ttf Error: %s\n", path.c_str(), TTF_GetError());
    }
    return font;
}
TTF_Font* loadFontOutline(const std::string& path, int size, int outline) {
    TTF_Font* font = loadFont(path, size);
    TTF_SetFontOutline(font, outline);
    return font;
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

    BufferBucketTomatoes.loadFromFile("data/bucket_tomatoes.ogg");
    soundBucketTomatoes.setBuffer(BufferBucketTomatoes);

    BufferDoggo1.loadFromFile("data/doggo1.ogg");
    soundDoggo1.setBuffer(BufferDoggo1);

    BufferDoggo2.loadFromFile("data/doggo2.ogg");
    soundDoggo2.setBuffer(BufferDoggo2);

    BufferDoggo3.loadFromFile("data/doggo3.ogg");
    soundDoggo3.setBuffer(BufferDoggo3);

    BufferBuy.loadFromFile("data/buy.ogg");
    soundBuy.setBuffer(BufferBuy);

    BufferSell1.loadFromFile("data/sell1.ogg");
    soundSell1.setBuffer(BufferSell1);

    BufferSell2.loadFromFile("data/sell2.ogg");
    soundSell2.setBuffer(BufferSell2);

    BufferWater.loadFromFile("data/water.ogg");
    soundWater.setBuffer(BufferWater);

    BufferBucketWater.loadFromFile("data/bucket_water.ogg");
    soundBucketWater.setBuffer(BufferBucketWater);

    BufferJump1.loadFromFile("data/jump1.ogg");
    soundJump1.setBuffer(BufferJump1);
    soundJump1.setVolume(50);

    BufferJump2.loadFromFile("data/jump2.ogg");
    soundJump2.setBuffer(BufferJump2);
    soundJump2.setVolume(50);

    BufferLand.loadFromFile("data/land.ogg");
    soundLand.setBuffer(BufferLand);

    BufferPickupDrop.loadFromFile("data/pickup_drop.ogg");
    soundPickupDrop.setBuffer(BufferPickupDrop);

    BufferDeath.loadFromFile("data/death.ogg");
    soundDeath.setBuffer(BufferDeath);

    sceneMusic[0].openFromFile("data/plantetes_gameplay.ogg");
    sceneMusic[0].setVolume(60);
    sceneMusic[0].setLoop(true);
    sceneMusic[1].openFromFile("data/plantetes_menu.ogg");
    sceneMusic[1].setVolume(60);
    sceneMusic[1].setLoop(true);
}
