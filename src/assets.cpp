#include "assets.h"

sf::Texture Assets::hospitalTexture;
sf::Sprite Assets::hospitalSprite;

sf::Texture Assets::marioTexture;
sf::Sprite Assets::marioSprite;

<<<<<<< HEAD
sf::Texture Assets::plantTexture;

sf::Texture Assets::fogTexture;
=======
sf::Texture Assets::casaTexture;
sf::Sprite Assets::casaSprite;
>>>>>>> a02cb5501132c46e0461a29dcbf7de1e66600446

sf::Font Assets::font;

sf::Shader Assets::tintShader;

void Assets::LoadAll() {

    hospitalTexture.loadFromFile("data/spritesheet.png");
    hospitalSprite.setTexture(hospitalTexture);

    marioTexture.loadFromFile("data/mario.png");
    marioSprite.setTexture(marioTexture);

<<<<<<< HEAD
    plantTexture.loadFromFile("data/plant.png");

    fogTexture.loadFromFile("data/fog.png");
=======
    casaTexture.loadFromFile("data/bg.png");
    casaSprite.setTexture(casaTexture);
>>>>>>> a02cb5501132c46e0461a29dcbf7de1e66600446

    font.loadFromFile("data/PressStart2P.ttf");

    tintShader.loadFromFile("data/tint.frag", sf::Shader::Fragment);

}
