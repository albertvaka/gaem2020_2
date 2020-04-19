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

sf::SoundBuffer Assets::soundBucketTomatoes;
sf::SoundBuffer Assets::soundBuy;
sf::SoundBuffer Assets::soundSell1;
sf::SoundBuffer Assets::soundSell2;
sf::SoundBuffer Assets::soundWater;
sf::SoundBuffer Assets::soundBucketWater;
sf::SoundBuffer Assets::soundJump1;
sf::SoundBuffer Assets::soundJump2;
sf::SoundBuffer Assets::soundLand;
sf::SoundBuffer Assets::soundPikcupDrop;
sf::SoundBuffer Assets::soundDeath;

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

    soundBucketTomatoes.loadFromFile("data/bucket_tomatoes.ogg");
    soundBuy.loadFromFile("data/buy.ogg");
    soundSell1.loadFromFile("data/sell1.ogg");
    soundSell2.loadFromFile("data/sell2.ogg");
    soundWater.loadFromFile("data/water.ogg");
    soundBucketWater.loadFromFile("data/bucket_water.ogg");
    soundJump1.loadFromFile("data/jump1.ogg");
    soundJump2.loadFromFile("data/jump2.ogg");
    soundLand.loadFromFile("data/land.ogg");
    soundPikcupDrop.loadFromFile("data/pickup_drop.ogg");
    soundDeath.loadFromFile("data/death.ogg");
}
