#pragma once

#include "entity.h"
#include "selfregister.h"
#include "jumpman.h"


struct Plant : public BoxEntity, EntS<Plant> {
  Plant(vec pos);
  void Update(float dt);
	void Draw(sf::RenderTarget& window) const;

  bool IsBeingCarried() const;
  void PickUpBy(const JumpMan* carrier);
  void Drop();



  const JumpMan* carrier = nullptr;
  // number of tiles of height, including pot.
  int height = 1;

  // Stats.
  int water = 0;
  int light = 0;

  sf::Clock grow_clock;
};
