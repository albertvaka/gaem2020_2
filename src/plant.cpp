#include "plant.h"
#include "assets.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 4;
const vec kCarryPositionOffset = {8.0f, -8.0f};
const float kMaxStats = 100.0f;
const float kLightIncrease = 10.0f;

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
  if (gets_light) {
    light = std::min(kMaxStats, light + dt * kLightIncrease);
  }
}

void Plant::Draw(sf::RenderTarget& window) const {
  sf::Sprite sprite;
  sprite.setTexture(Assets::plantTexture);
  sf::IntRect texture_rect(0, 64 - 16*height, 16, 16*height);
  sprite.setTextureRect(texture_rect);
  sprite.setPosition(pos - size*0.5f);
  window.draw(sprite);

  // Draw stats if they are changing
  const float bar_height = 3.0f;
  const float outline = 1.0f;
  const float width_multiplier = 1/100.0f * 20.0f;
  if (gets_light) {
    sf::RectangleShape background(vec(kMaxStats * width_multiplier + 2.0f*outline, bar_height + 2.0f*outline));
    background.setPosition(vec(pos.x, getBottomY()) + vec(-0.5f * (kMaxStats * width_multiplier + 2.0f*outline), 10.0f));
    background.setFillColor(sf::Color::Black);
    window.draw(background);
    sf::RectangleShape filled_bar(vec(light * width_multiplier, bar_height));
    filled_bar.setPosition(vec(pos.x, getBottomY()) + vec(-0.5f*light * width_multiplier, 11.0f));
    filled_bar.setFillColor(sf::Color::Yellow);
    window.draw(filled_bar);
  }
}

float Plant::getBottomY() const
{
  return pos.y + 8.0f * height;
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

void Plant::SetHitByWater(bool hit)
{
  gets_water = hit;
}

void Plant::SetHitByLight(bool hit)
{
  gets_light = hit;
}

