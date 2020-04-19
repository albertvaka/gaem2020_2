#include "plant.h"
#include "assets.h"
#include "imgui.h"
#include "debug.h"
#include "input.h"

const float kSecondsToGrow = 10.0f;
const int kMaxHeight = 4;
const vec kCarryPositionOffset = { 8.0f, -8.0f };

const float kMaxStats = 50.0f;
const float kInitialStats = 25.f;

const float kLightIncreasePerSecond = 3.0f;
const float kWaterIncreasePerWatering = 30.0f;

const float kAdditionalWaterLostWhenGetsLight = 0.5f;

const float kLightLostPerSecond = 0.3f;
const float kWaterLostPerSecond = 0.4f;

const float kWaterAndLighThresholdToGrow = 40.0f;
const float kWaterAndLighThresholdToDie = 5.0f;

const float kWaterBubbleDuration = 3.0f;
// TODO: Slow on purpose for testing.
const sf::Time kGrowInterval = sf::seconds(5.0f);

static int ids = 0;
Plant::Plant(vec pos) : BoxEntity(pos, vec(16.0f, 16.0f)) {
    water = kInitialStats;
    light = kInitialStats;
    id = ids++;
}

void Plant::Update(float dt) {

    // For Debug
    if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_SET_PLANTS_AT_MAX_STATS)) {
        // Grow to the max.
        while(height < kMaxHeight){
            ++height;
            pos.y -= 8.0f;
            size.y += 16.0f;
        }
        light = 100;
        water = 100;
    }

    if (carrier != nullptr) {
        pos = carrier->pos;
        pos.x += (carrier->lookingLeft ? -1 : 1) * kCarryPositionOffset.x;
        pos.y += kCarryPositionOffset.y - 8.0f * height;
    }

    if (!alive) return;

    water -= kWaterLostPerSecond * dt;
    light -= kLightLostPerSecond * dt;

    if (water >= kWaterAndLighThresholdToGrow && light >= kWaterAndLighThresholdToGrow && grow_clock.getElapsedTime().asSeconds() > kSecondsToGrow) {
        grow_clock.restart();
        if (height >= kMaxHeight) {
            if (!has_tomato) {
                has_tomato = true;
                // Random offset.
                for (int i = 0; i < kNumTomatoes; ++i) {
                    tomato_offset[i] = vec(Random::rollf(-8.0f, 8.0f), Random::rollf(-16.0f, 16.0f));
                }
            }
        }
        else {
            ++height;
            pos.y -= 8.0f;
            size.y += 16.0f;
        }
    }
  
    if (gets_light) {
        light = std::min(kMaxStats, light + dt * kLightIncreasePerSecond);
        water -= kAdditionalWaterLostWhenGetsLight * dt;
    }
    if (gets_water) {
        water = std::min(kMaxStats, water + kWaterIncreasePerWatering);
        gets_water = false;
        time_left_water_bubble = kWaterBubbleDuration;
    } else {
      time_left_water_bubble -= dt;
    }

      if (light < kWaterAndLighThresholdToDie || water < kWaterAndLighThresholdToDie) {
          alive = false;
          if (height >= kMaxHeight) {
              height = kMaxHeight - 1;
              pos.y += 8.0f;
              size.y -= 16.0f;
          }
      }
}

bool Plant::HasTomato() const {
  return has_tomato;
}

void Plant::PickTomato() {
  has_tomato = false;
  grow_clock.restart();
}

void Plant::Draw(sf::RenderTarget& window) {
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
  static sf::Clock bubble_timer;
  bool draw_light_bubble = (int(bubble_timer.getElapsedTime().asSeconds()) % 2 == 0);
  bool draw_water_bubble = !draw_light_bubble;
  if (gets_light) {
    //DrawStatBar(light, 0.0f, sf::Color::Yellow, window);
    if (draw_light_bubble) {
      sf::Sprite bubble_sprite;
      bubble_sprite.setTexture(Assets::plantTexture);
      bubble_sprite.setTextureRect({34,0,18,23});
      bubble_sprite.setPosition(vec(pos) + vec(10.0f, -23.f));
      window.draw(bubble_sprite);
    }
  }
  if (time_left_water_bubble > 0.0f) {
    //DrawStatBar(water, 7.0f, sf::Color::Cyan, window);
    if (draw_water_bubble) {
      sf::Sprite bubble_sprite;
      bubble_sprite.setTexture(Assets::plantTexture);
      bubble_sprite.setTextureRect({34,23,18,23});
      bubble_sprite.setPosition(vec(pos) + vec(10.0f, -23.0f));
      window.draw(bubble_sprite);
    }
  }

#ifdef _DEBUG
  ImGui::Begin((std::string("plant")+::std::to_string(id)).c_str());
  ImGui::SliderFloat("water", &water, 0.f, kMaxStats);
  ImGui::SliderFloat("light", &light, 0.f, kMaxStats);
  ImGui::Checkbox("alive", &alive);
  ImGui::End();
#endif
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

