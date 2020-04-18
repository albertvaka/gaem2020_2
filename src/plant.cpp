#include "plant.h"
#include "assets.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 4;
const vec kCarryPositionOffset = {8.0f, -8.0f};

Plant::Plant(vec pos) : BoxEntity(pos, vec(16.0f, 16.0f)) {}

void Plant::Update(float dt) {
  if (carrier != nullptr) {
    pos = carrier->pos;
    pos.x += (carrier->lookingLeft ? -1:1) * kCarryPositionOffset.x;
    pos.y += kCarryPositionOffset.y - 8.0f * height;
  }
  if (height < kMaxHeight && grow_clock.getElapsedTime().asSeconds() > kSecondsToGrow) {
    ++height;
    pos.y -= 8.0f;
    size.y += 16.0f;
    grow_clock.restart();
  }
}

void Plant::Draw(sf::RenderTarget& window) const {
  sf::Sprite sprite;
  sprite.setTexture(Assets::plantTexture);
  sf::IntRect texture_rect(0, 64 - 16*height, 16, 16*height);
  sprite.setTextureRect(texture_rect);
  sprite.setPosition(pos - size*0.5f);
  window.draw(sprite);
}

bool Plant::IsBeingCarried() const
{
  return carrier != nullptr;
}

void Plant::PickUpBy(const JumpMan* player)
{
  carrier = player;
}

void Plant::Drop()
{
  pos.y = carrier->pos.y - 8.0f * height;
  carrier = nullptr;
}

