#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "collider.h"
#include "mates.h"
#include "debug.h"
#include "assets.h"

const float kVel = 50;
const float kMenjarDecreasePerSecond = 1;
const float kMaxMenjar = 60;

struct Doggo : BoxEntity, EntS<Doggo>
{
	float menjar = kMaxMenjar;
	Animation anim;
	int nextPoint;
	bool forward;
	int destination = 0;
	bool wantFood = false;

	Doggo() : BoxEntity(vec(), vec(28,28)) {
		anim.Ensure(DOGGO_RIGHT);

		static std::set<int> all_destinations;
		if (all_destinations.size() == TiledEntities::waypoint.size()) {
			all_destinations.clear();
		}

		while (true) {
			destination = Random::roll(TiledEntities::waypoint.size());
			if (all_destinations.find(destination) == all_destinations.end()) {
				all_destinations.insert(destination);
				break;
			}
		}

		if (GoodRandom::roll_flipcoin()) {
			pos = TiledEntities::doggo_begin;
			nextPoint = 0;
			forward = true;
		}
		else {
			pos = TiledEntities::doggo_end;
			nextPoint = TiledEntities::waypoint.size()-1;
			forward = false;
		}
	}

	void Update(float dt)
	{

		anim.Update(dt * 1000);

		if (wantFood) {
			menjar -= kMenjarDecreasePerSecond * dt;
		}
		else {
			vec dest = TiledEntities::waypoint[nextPoint];
			vec diff = dest - pos;
			if (diff.x > 0) {
				anim.Ensure(DOGGO_RIGHT);
			}
			else {
				anim.Ensure(DOGGO_LEFT);
			}
			if (diff.Length() < kVel * dt) {
				pos += diff;
				if (nextPoint == destination) {
					anim.Ensure(DOGGO_IDLE);
					wantFood = true;
				}
				else {
					if (forward) {
						nextPoint++;
					}
					else {
						nextPoint--;
					}
				}
			}
			else {
				pos += diff.Normalized() * kVel * dt;
			}
		}

	}

	void Draw(sf::RenderTarget& window) const
	{
		sf::Sprite& spr = Assets::doggoSprite;
		spr.setOrigin(size/2.0f);
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(anim.CurrentFrame());
		pos.Debuggerino();
		window.draw(spr);
		if (Debug::Draw) {
			bounds().Draw(window);
		}
	}

};