#include "plant.h"
#include "assets.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 4;
const vec kCarryPositionOffset = { 8.0f, -8.0f };
const float kMaxStats = 100.0f;
const float kLightIncrease = 10.0f;

const float kLightLostPerSecond = 1.0f;
const float kWaterLostPerSecond = 1.0f;

const float kAdditionalWaterLostWhenGetsLight = 1.f;

const float kMinLightForTomato = 50.0f;
const float kMinWaterForTomato = 50.0f;
// TODO: Slow on purpose for testing.
const sf::Time kMinTimeForTomato = sf::seconds(5.0f);

const float kWaterToDie = 5.0f;
const float kSunToDie = 5.0f;

const sf::Time kWaterEffectDuration = sf::seconds(2.0f);

Plant::Plant(vec pos) : BoxEntity(pos, vec(16.0f, 16.0f)) {
    water = kMaxStats/2;
    light = kMaxStats / 2;
}

void Plant::Grow() {
  if (height >= kMaxHeight) return;
  ++height;
  pos.y -= 8.0f;
  size.y += 16.0f;
  grow_clock.restart();
}

void Plant::Update(float dt) {
    water -= kWaterLostPerSecond * dt;
    light -= kLightLostPerSecond * dt;

  if (carrier != nullptr) {
    pos = carrier->pos;
    pos.x += (carrier->lookingLeft ? -1 : 1) * kCarryPositionOffset.x;
    pos.y += kCarryPositionOffset.y - 8.0f * height;
  }


  if (!alive) return;

  if (height < kMaxHeight && grow_clock.getElapsedTime().asSeconds() > kSecondsToGrow) {
    Grow();
  }
  if (gets_light) {
    light = std::min(kMaxStats, light + dt * kLightIncrease);
    water -= kAdditionalWaterLostWhenGetsLight * dt;
  }
  if (gets_water) {
    water = std::min(kMaxStats, water + dt * kLightIncrease);
    if (water_clock.getElapsedTime() >= kWaterEffectDuration) {
      gets_water = false;
    }
  }


  if (light < kSunToDie || water < kWaterToDie) {
      alive = false;
      
      if (height >= kMaxHeight) {
          height = kMaxHeight - 1;
      }
  }

  if (light > kMinLightForTomato&&
    water > kMinWaterForTomato &&
    !has_tomato) {
    tomato_timer += sf::seconds(dt);
    if (tomato_timer >= kMinTimeForTomato) {
      has_tomato = true;
      // Random offset.
      for (int i = 0; i < kNumTomatoes; ++i) {
        tomato_offset[i] = vec(Random::rollf(-8.0f, 8.0f), Random::rollf(-16.0f, 16.0f));
      }
    }
  }
}

bool Plant::HasTomato() const {
  return has_tomato;
}

void Plant::PickTomato() {
  has_tomato = false;
  tomato_timer = sf::Time::Zero;
}

void Plant::Draw(sf::RenderTarget& window) const {
  // Draw tomato
  if (alive && has_tomato) {
    sf::Sprite sprite;
    sprite.setTexture(Assets::plantTexture);
    sf::IntRect texture_rect(22, 54, 10, 10);
    sprite.setTextureRect(texture_rect);
    sprite.setOrigin(5, 5);
    for (int i = 0; i < kNumTomatoes; ++i) {
      sprite.setPosition(pos + tomato_offset[i]);
      window.draw(sprite);
    }
  }

  sf::Sprite sprite;
  sprite.setTexture(Assets::plantTexture);
  sf::IntRect texture_rect(0, 64 - 16 * height, 16, 16 * height);
  if (!alive) {
      sprite.setColor(sf::Color(128,128,128,255));
  }
  else {
      sprite.setColor(sf::Color(255, 255, 255, 255));
  }
  sprite.setTextureRect(texture_rect);
  sprite.setPosition(pos - size * 0.5f);
  window.draw(sprite);

  // Draw stats if they are changing
  if (gets_light) {
    DrawStatBar(light, 0.0f, sf::Color::Yellow, window);
  }
  if (gets_water) {
    DrawStatBar(water, 7.0f, sf::Color::Cyan, window);
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

bool Plant::IsCarriedBy(const JumpMan* carrier) const
{
  return carrier == this->carrier;
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

void Plant::SetHitByWater()
{
  gets_water = true;
  water_clock.restart();
}

void Plant::SetHitByLight(bool hit)
{
  gets_light = hit;
}

void Plant::DrawStatBar(float value, float y_offset, sf::Color color, sf::RenderTarget& window) const
{
  const float bar_height = 3.0f;
  const float outline = 1.0f;
  const float width_multiplier = 1 / 100.0f * 20.0f;
  const float y = 10.0f + y_offset;
  sf::RectangleShape background(vec(kMaxStats * width_multiplier + 2.0f * outline, bar_height + 2.0f * outline));
  background.setPosition(vec(pos.x, getBottomY()) + vec(-0.5f * (kMaxStats * width_multiplier + 2.0f * outline), y));
  background.setFillColor(sf::Color::Black);
  window.draw(background);
  sf::RectangleShape filled_bar(vec(value * width_multiplier, bar_height));
  filled_bar.setPosition(vec(pos.x, getBottomY()) + vec(-0.5f * value * width_multiplier, y + 1.0f));
  filled_bar.setFillColor(color);
  window.draw(filled_bar);
}

