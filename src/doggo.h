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
const float kMenjarBubbleDuration = 3.0f;
static int doggo_ids = 0;

struct Doggo : BoxEntity, EntS<Doggo>
{
	float menjar = kMaxMenjar;
	float menjar_bubble_timer = 0.0f;
	Animation anim;
	int id = doggo_ids++;
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
		menjar_bubble_timer -= dt;

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
#ifdef _DEBUG
      ImGui::Begin((std::string("doggo") + ::std::to_string(id)).c_str());
      ImGui::SliderFloat("menjar", &menjar, 0.f, kMaxMenjar);
      ImGui::End();
#endif
	}

  void Draw(sf::RenderTarget& window) const
  {
    sf::Sprite& spr = Assets::doggoSprite;
    spr.setOrigin(size / 2.0f);
    spr.setPosition(pos.x, pos.y);
    spr.setTextureRect(anim.CurrentFrame());
    pos.Debuggerino();
    window.draw(spr);
    if (Debug::Draw) {
      bounds().Draw(window);
    }

    if (menjar_bubble_timer > 0.0f && int(menjar_bubble_timer) != 1) {
      sf::Sprite bubble_sprite;
      bubble_sprite.setTexture(Assets::plantTexture);
      bubble_sprite.setTextureRect({16,0,18,23});
      bubble_sprite.setPosition(vec(pos) + vec(17.0f, -15.f));
      window.draw(bubble_sprite);
    }

		// Draw bottom status.
    sf::Sprite status_sprite;
    status_sprite.setTexture(Assets::plantTexture);
    status_sprite.setTextureRect({ 52,32,17,16 });
    status_sprite.setOrigin(17 / 2, 0);
    status_sprite.setPosition(pos + vec(0.0f, 17.0f));
    window.draw(status_sprite);
    // Draw face.
    int happiness = std::min(int(menjar / (kMaxMenjar / 5)), 4);
    status_sprite.setTextureRect({ 106,52 - 12 * happiness,13,12 });
    status_sprite.setOrigin(6, 0);
    status_sprite.setPosition(pos + vec(0.0f, 20.0f));
    window.draw(status_sprite);
  }

	void Feed() {
		menjar = kMaxMenjar;
		menjar_bubble_timer = kMenjarBubbleDuration;
	}

};