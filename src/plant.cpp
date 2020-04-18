#include "plant.h"
#include "assets.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 4;
const vec kCarryPositionOffset = {0.0f, -20.0f};

Plant::Plant(vec pos) : BoxEntity(pos, vec(16.0f, 16.0f)) {}

void Plant::Update(float dt) {
  if (carrier != nullptr) {
    pos = carrier->pos + kCarryPositionOffset;
    pos.y -= 16.0f * (height-1);
  }
  if (height < kMaxHeight && grow_clock.getElapsedTime().asSeconds() > kSecondsToGrow) {
    ++height;
    pos.y -= 16.0f;
    size.y += 16.0f;
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

bool Plant::IsBeingCarried() const
{
  return carrier != nullptr;
}

void Plant::PickUpBy(const Entity* player)
{
  carrier = player;
}

void Plant::Drop()
{
  carrier = nullptr;
  pos -= kCarryPositionOffset;
  pos.y -= 16.0f;
}

