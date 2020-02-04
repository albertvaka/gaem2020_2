#pragma once

#include <vector>
#include "rand.h"

#include "entity.h"
#include "lever.h"
#include "extremity.h"

struct Mesa;

struct Collector : SortedDrawable, EntS<Collector>
{
	ExtremityType type;
	Mesa* mesa = nullptr;
	Extremity* extremity = nullptr;

	bool mesa_was_empty = true;

	Collector(vec position, ExtremityType et)
	{
		type = et;
		pos = position;
		anim.Ensure(AnimationType::CAPSULE_CLOSED);
		anim.loopable = false;
	}

	void Update(int dt);

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		spr.setScale(1, 1);
		spr.setTextureRect(anim.CurrentFrame());
		spr.setPosition(pos.x, pos.y);
		wnd.draw(spr);
		spr.setScale(1, 1);
	}

};

struct Mesa : SortedDrawable, EntS<Mesa>
{
	Cadaver* cadaver = nullptr;
	Lever* lever = nullptr;

	ExtremityType type;
	Collector* collector = nullptr;

	Mesa(vec position, ExtremityType et)
	{
		type = et;
		pos = position;

		anim.Ensure(AnimationType::POKEMON);
		lever = new Lever(pos-vec(16, 42));
	}

	void Update(int dt)
	{
		lever->isReady = (collector->extremity && cadaver && !cadaver->HasExtremity(type)) && collector->extremity->type == type || (!collector->extremity && cadaver && cadaver->HasExtremity(type));
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		spr.setScale(1.25f, 1.25f);
		spr.setTextureRect(anim.CurrentFrame());
		spr.setPosition(pos.x - 11.2f, pos.y - 22.5f);
		wnd.draw(spr);
		spr.setScale(1,1);

		if (cadaver && lever->isFinished)
		{
			if (collector->extremity)
			{
				if (!cadaver->HasExtremity(type))
				{
					cadaver->AttachExtremity(collector->extremity);
					collector->extremity = nullptr;
				}
			}
			else
			{
				if (cadaver->HasExtremity(type))
				{
					Extremity* e = cadaver->DeatachExtremity(type, collector->pos);
					collector->extremity = e;
				}
			}
			lever->isFinished = false;
		}
	}

};


inline void Collector::Update(int dt)
{
	Collector* c = this;

	bool mesa_empty = !c->mesa->cadaver;

	if (c->mesa_was_empty && (!mesa_empty || c->extremity))
	{
		c->anim.Ensure(AnimationType::CAPSULE_OPENING);
		c->anim.loopable = false;
	}

	if (!c->mesa_was_empty && (mesa_empty && !c->extremity))
	{
		c->anim.Ensure(AnimationType::CAPSULE_CLOSING);
		c->anim.loopable = false;
	}

	c->mesa_was_empty = (mesa_empty && !c->extremity);
}
