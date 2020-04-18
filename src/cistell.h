#pragma once

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

struct Cistell : BoxEntity, SingleInstance<Cistell>
{
	enum Contents : char {
		EMPTY = 0,
		TOMATOES,
		WATER,
	};

	Contents contents = EMPTY;

	Cistell() : BoxEntity(vec(), vec(32,16)) {
	}

	void Update(float dt)
	{
    if (carrier != nullptr) {
      pos = carrier->pos;
      pos.x += (carrier->lookingLeft ? -1 : 1) * kCarryPositionOffset.x;
      pos.y += kCarryPositionOffset.y - 8.0f;
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

	void Draw(sf::RenderTarget& window) const
	{
		sf::Sprite& spr = Assets::spritesSprite;
		spr.setOrigin(0,16);
		spr.setPosition(pos.x, pos.y);
		if (contents == TOMATOES) {
			spr.setTextureRect(sf::Rect(14 * 16, 32, 32, 16));
		}
		else if (contents == WATER) {
			spr.setTextureRect(sf::Rect(14 * 16, 16, 32, 16));
		}
		else {
			spr.setTextureRect(sf::Rect(14 * 16, 0, 32, 16));
		}
		pos.Debuggerino();
		window.draw(spr);

		if (Debug::Draw) {
			bounds().Draw(window);
		}
	}

	void Drop()
	{
		pos.y = carrier->pos.y - 8.0f;
		carrier = nullptr;
	}
	bool IsBeingCarried() const { return !(carrier == nullptr); }
	bool IsCarriedBy(const JumpMan* carrier) const { return carrier == this->carrier; }
	void PickUpBy(const JumpMan* carrier) { this->carrier = carrier; }


	const JumpMan* carrier = nullptr;
};