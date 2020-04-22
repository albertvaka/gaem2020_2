#pragma once

#include "selfregister.h"
#include "entity.h"
#include "animation.h"
#include "singleinstance.h"
#include "rand.h"
#include "collider.h"
#include "input.h"
#include "mates.h"
#include "debug.h"
#include "assets.h"
#include "jumpman.h"

const vec kCarryPositionOffset = {8.0f, -8.0f};

struct Cistell : BoxEntity, EntS<Cistell>
{
	enum Contents : char {
		EMPTY = 0,
		TOMATOES,
		WATER,
	};

	Contents contents = EMPTY;

	Cistell() : BoxEntity(vec(), vec(25,28)) {
	}

	void Update(float dt)
	{
    if (carrier != nullptr) {
      pos = carrier->pos;
      pos.x += (carrier->lookingLeft ? -1 : 1) * kCarryPositionOffset.x;
      pos.y += kCarryPositionOffset.y - size.y/2.0f;
    }
		if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_KILLALL)) {
			if (contents == EMPTY) {
				contents = TOMATOES;
			} else if (contents == TOMATOES) {
				contents = WATER;
			}
			else if (contents == WATER) {
				contents = EMPTY;
			}
		}
	}

	void Draw() const
	{
		IntRect rect;
		if (contents == TOMATOES) {
			rect = IntRect(168, 97, 25, 28);
		}
		else if (contents == WATER) {
			rect = IntRect(141, 97, 25, 28);
		}
		else {
			rect = IntRect(114, 97, 25, 28);
		}
		pos.Debuggerino();
		Window::Draw(Assets::spritesTexture, pos)
			.withRect(rect)
			.withOrigin(size / 2.f);

		if (Debug::Draw) {
			bounds().Draw();
		}
	}

	void Drop()
	{
		pos.y = carrier->pos.y - size.y/2.0f;
		carrier = nullptr;
	}
	bool IsBeingCarried() const { return !(carrier == nullptr); }
	bool IsCarriedBy(const JumpMan* carrier) const { return carrier == this->carrier; }
	void PickUpBy(const JumpMan* carrier) { this->carrier = carrier; }


	const JumpMan* carrier = nullptr;
};