#pragma once

#include "entity.h"
#include "selfregister.h"

struct Plant : public BoxEntity, EntS<Plant> {
  void Update(float dt);
	void Draw(sf::RenderTarget& window) const;
};
