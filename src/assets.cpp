#include "assets.h"

sf::Texture Assets::hospitalTexture;
sf::Sprite Assets::hospitalSprite;

std::array<sf::Texture, 3> Assets::sunTextures;	
std::array<sf::Sprite, 3> Assets::sunSprites;	

sf::Texture Assets::marioTexture;
sf::Sprite Assets::marioSprite;

sf::Texture Assets::casaTexture;
sf::Sprite Assets::casaSprite;
sf::Texture Assets::plantTexture;

sf::Texture Assets::spritesTexture;
sf::Sprite Assets::spritesSprite;
sf::Texture Assets::npcTexture;
sf::Sprite Assets::npcSprite;

sf::Font Assets::font;

sf::Shader Assets::tintShader;

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

sf::Music Assets::sceneMusic[2];

void Assets::LoadAll() {

    hospitalTexture.loadFromFile("data/spritesheet.png");
    hospitalSprite.setTexture(hospitalTexture);

    marioTexture.loadFromFile("data/mario.png");
    marioSprite.setTexture(marioTexture);

    for (int i = 0; i < 3; ++i) {	
      std::string filename = "data/sun" + std::to_string(i) + ".png";	
      sunTextures[i].loadFromFile(filename);	
      sunSprites[i].setTexture(sunTextures[i]);	
      sunSprites[i].setPosition(217.0f, 0.0f);	
    }

    spritesTexture.loadFromFile("data/sprites.png");
    spritesSprite.setTexture(spritesTexture);

    npcTexture.loadFromFile("data/npc.png");
    npcSprite.setTexture(npcTexture);

    casaTexture.loadFromFile("data/bg.png");
    casaSprite.setTexture(casaTexture);

    plantTexture.loadFromFile("data/plant.png");

    font.loadFromFile("data/PressStart2P.ttf");

    tintShader.loadFromFile("data/tint.frag", sf::Shader::Fragment);

    soundBufferBucketTomatoes.loadFromFile("data/bucket_tomatoes.ogg");
    soundBucketTomatoes.setBuffer(soundBufferBucketTomatoes);

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
