#include "assets.h"

sf::Texture Assets::hospitalTexture;
sf::Sprite Assets::hospitalSprite;

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
