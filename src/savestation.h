#pragma once

#include "vector.h"
#include "entity.h"
#include "selfregister.h"

struct SaveStation : BoxEntity, EntS<SaveStation>
{
	bool enabled = false;

	SaveStation(const vec& p);
	void Update(float dt);
	void Draw(sf::RenderTarget& window) const;
};

