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

void Assets::LoadAll() {

    hospitalTexture.loadFromFile("data/spritesheet.png");
    hospitalSprite.setTexture(hospitalTexture);

    for (int i = 0; i < 3; ++i) {
      std::string filename = "data/sun" + std::to_string(i) + ".png";
      sunTextures[i].loadFromFile(filename);
      sunSprites[i].setTexture(sunTextures[i]);
      sunSprites[i].setPosition(217.0f, 0.0f);
    }

    marioTexture.loadFromFile("data/mario.png");
    marioSprite.setTexture(marioTexture);

    spritesTexture.loadFromFile("data/sprites.png");
    spritesSprite.setTexture(spritesTexture);

    npcTexture.loadFromFile("data/npc.png");
    npcSprite.setTexture(npcTexture);

    casaTexture.loadFromFile("data/bg.png");
    casaSprite.setTexture(casaTexture);

    plantTexture.loadFromFile("data/plant.png");

    font.loadFromFile("data/PressStart2P.ttf");

    tintShader.loadFromFile("data/tint.frag", sf::Shader::Fragment);

}
