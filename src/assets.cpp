#include "assets.h"
#include "window.h"

#include <SDL_image.h>

SDL_Texture* Assets::hospitalTexture;

std::array<SDL_Texture*, 3> Assets::sunTextures;	

SDL_Texture* Assets::marioTexture;

SDL_Texture* Assets::casaTexture;
SDL_Texture* Assets::plantTexture;

SDL_Texture* Assets::spritesTexture;
SDL_Texture* Assets::npcTexture;

SDL_Texture* Assets::doggoTexture;

/*
sf::Font Assets::font;
*/
sf::SoundBuffer Assets::soundBufferBucketTomatoes;
sf::Sound Assets::soundBucketTomatoes;
sf::SoundBuffer Assets::soundBufferBuy;
sf::Sound Assets::soundBuy;
sf::SoundBuffer Assets::soundBufferSell1;
sf::Sound Assets::soundSell1;
sf::SoundBuffer Assets::soundBufferSell2;
sf::Sound Assets::soundSell2;
sf::SoundBuffer Assets::soundBufferWater;
sf::Sound Assets::soundWater;
sf::SoundBuffer Assets::soundBufferBucketWater;
sf::Sound Assets::soundBucketWater;
sf::SoundBuffer Assets::soundBufferJump1;
sf::Sound Assets::soundJump1;
sf::SoundBuffer Assets::soundBufferJump2;
sf::Sound Assets::soundJump2;
sf::SoundBuffer Assets::soundBufferLand;
sf::Sound Assets::soundLand;
sf::SoundBuffer Assets::soundBufferPickupDrop;
sf::Sound Assets::soundPickupDrop;
sf::SoundBuffer Assets::soundBufferDeath;
sf::Sound Assets::soundDeath;

sf::SoundBuffer Assets::soundBufferDoggo1;
sf::Sound Assets::soundDoggo1;

sf::SoundBuffer Assets::soundBufferDoggo2;
sf::Sound Assets::soundDoggo2;

sf::SoundBuffer Assets::soundBufferDoggo3;
sf::Sound Assets::soundDoggo3;

sf::Music Assets::sceneMusic[2];

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

    /*
    font.loadFromFile("data/PressStart2P.ttf");
    */
    soundBufferBucketTomatoes.loadFromFile("data/bucket_tomatoes.ogg");
    soundBucketTomatoes.setBuffer(soundBufferBucketTomatoes);

    soundBufferDoggo1.loadFromFile("data/doggo1.ogg");
    soundDoggo1.setBuffer(soundBufferDoggo1);

    soundBufferDoggo2.loadFromFile("data/doggo2.ogg");
    soundDoggo2.setBuffer(soundBufferDoggo2);

    soundBufferDoggo3.loadFromFile("data/doggo3.ogg");
    soundDoggo3.setBuffer(soundBufferDoggo3);

    soundBufferBuy.loadFromFile("data/buy.ogg");
    soundBuy.setBuffer(soundBufferBuy);

    soundBufferSell1.loadFromFile("data/sell1.ogg");
    soundSell1.setBuffer(soundBufferSell1);

    soundBufferSell2.loadFromFile("data/sell2.ogg");
    soundSell2.setBuffer(soundBufferSell2);

    soundBufferWater.loadFromFile("data/water.ogg");
    soundWater.setBuffer(soundBufferWater);

    soundBufferBucketWater.loadFromFile("data/bucket_water.ogg");
    soundBucketWater.setBuffer(soundBufferBucketWater);

    soundBufferJump1.loadFromFile("data/jump1.ogg");
    soundJump1.setBuffer(soundBufferJump1);
    soundJump1.setVolume(50);

    soundBufferJump2.loadFromFile("data/jump2.ogg");
    soundJump2.setBuffer(soundBufferJump2);
    soundJump2.setVolume(50);

    soundBufferLand.loadFromFile("data/land.ogg");
    soundLand.setBuffer(soundBufferLand);

    soundBufferPickupDrop.loadFromFile("data/pickup_drop.ogg");
    soundPickupDrop.setBuffer(soundBufferPickupDrop);

    soundBufferDeath.loadFromFile("data/death.ogg");
    soundDeath.setBuffer(soundBufferDeath);

    sceneMusic[0].openFromFile("data/plantetes_gameplay.ogg");
    sceneMusic[0].setVolume(60);
    sceneMusic[0].setLoop(true);
    sceneMusic[1].openFromFile("data/plantetes_menu.ogg");
    sceneMusic[1].setVolume(60);
    sceneMusic[1].setLoop(true);
}
