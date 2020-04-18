#pragma once

#include "entity.h"
#include "selfregister.h"
#include "jumpman.h"


struct Plant : public BoxEntity, EntS<Plant> {
  Plant(vec pos);
  void Update(float dt);
	void Draw(sf::RenderTarget& window) const;

  float getBottomY() const;
  bool IsBeingCarried() const;
  bool IsCarriedBy(const JumpMan* carrier) const;
  void PickUpBy(const JumpMan* carrier);
  void Drop();
  bool HasTomato() const;
  void PickTomato();
  void Grow();  // Exposed for debug.

  void SetHitByWater(bool hit);
  void SetHitByLight(bool hit);


  const JumpMan* carrier = nullptr;
  // number of tiles of height, including pot.
  int height = 1;

  // Stats.
  bool gets_water = false;
  float water = 0;
  bool gets_light = false;
  float light = 0;
  bool has_tomato = false;
  sf::Time tomato_timer;
  vec tomato_offset;

  sf::Clock grow_clock;

private:
  void DrawStatBar(float value, float y_offset, sf::Color color, sf::RenderTarget& window) const;
};
