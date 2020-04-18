#include "plant.h"
#include "assets.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 3;

Plant::Plant(vec pos) : BoxEntity(pos, vec(16.0f, 16.0f)) {}

void Plant::Update(float dt) {
  if (height < kMaxHeight && grow_clock.getElapsedTime().asSeconds() > kSecondsToGrow) {
    ++height;
    grow_clock.restart();
  }
}

void Plant::Draw(sf::RenderTarget& window) const {
  sf::Sprite sprite;
  sprite.setTexture(Assets::plantTexture);
  sf::IntRect texture_rect(0, 64 - 16*height, 16, 16*height);
  sprite.setTextureRect(texture_rect);
  sprite.setPosition(pos);
  window.draw(sprite);
}
