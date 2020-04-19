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

struct Npc : BoxEntity, SingleInstance<Npc>
{
	float timer = 0;
	Animation animation;
	bool selling = false;

	Npc() : BoxEntity(vec(-35, 270), vec(30,50)) {
		animation.Ensure(NPC_WALK);
	}

	bool isSelling() {
		return selling;
	}

	void Update(float dt)
	{
		if (timer < 4.f) {
			timer += dt;
			if (timer > 4.f) {
				animation.Ensure(NPC_IDLE);
				timer = 4.f;
			}
			pos = vec(-20 + timer * 20, 245);
		}
		else {
			timer += dt;
			pos = vec(-20 + 4 * 20, 245);
			selling = true;
		}
		animation.Update(dt * 1000);
	}

	void Draw(sf::RenderTarget& window) const
	{
		sf::Sprite& spr = Assets::npcSprite;
		//spr.setScale(1.f, 1.f);
		spr.setOrigin(15,25);
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(animation.CurrentFrame());
		window.draw(spr);
		spr.setOrigin(0, 0);
		spr.setScale(1.f, 1.f);

		if (timer > 4.f) {
			sf::Sprite& spr = Assets::spritesSprite;
			spr.setOrigin(45, 64);
			float scale = Mates::MinOf((timer-4)*5,1.f);
			spr.setScale(scale, scale);
			spr.setPosition(pos.x, pos.y+4);
			spr.setTextureRect(sf::IntRect(0,41,89,128-42));
			window.draw(spr);
			spr.setOrigin(0, 0);
			spr.setScale(1.f, 1.f);
		}

		if (Debug::Draw) {
			bounds().Draw(window);
		}
	}
};