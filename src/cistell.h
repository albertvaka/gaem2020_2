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

	void Draw(sf::RenderTarget& window) const
	{
		sf::Sprite& spr = Assets::spritesSprite;
		spr.setOrigin(size/2.0f);
		spr.setPosition(pos.x, pos.y);
		if (contents == TOMATOES) {
			spr.setTextureRect(sf::Rect(168, 97, 25, 28));
		}
		else if (contents == WATER) {
			spr.setTextureRect(sf::Rect(141, 97, 25, 28));
		}
		else {
			spr.setTextureRect(sf::Rect(114, 97, 25, 28));
		}
		//spr.setScale(0.8f, 0.8f);
		pos.Debuggerino();
		window.draw(spr);

		if (Debug::Draw) {
			bounds().Draw(window);
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