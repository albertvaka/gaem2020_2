#pragma once

#include "stats_tracker.h"
#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "collider.h"
#include "mates.h"
#include "debug.h"
#include "assets.h"
#include "stats_tracker.h"

const float kVel = 50;
const float kMenjarDecreasePerSecond = 1;
const float kMaxMenjar = 90;
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


	void PlaySound() {
		switch (Random::roll(3)) {
		case 0:
			Assets::soundDoggo1.play();
			break;
		case 1:
			Assets::soundDoggo2.play();
			break;
		case 2:
			Assets::soundDoggo3.play();
			break;
		default:
			assert(false);
		}
	}

	static std::set<int>& AllDestinations() {
		static std::set<int> all_destinations = { 2 };
		return all_destinations;
	}

	Doggo() : BoxEntity(vec(), vec(28,28)) {
		++StatsTracker::doggos_in_game;
		anim.Ensure(DOGGO_RIGHT);

		
		if (AllDestinations().size() == TiledEntities::waypoint.size()) {
			AllDestinations().clear();
			AllDestinations().insert(2);
		}

		while (true) {
			destination = Random::roll(TiledEntities::waypoint.size());
			if (AllDestinations().find(destination) == AllDestinations().end()) {
				AllDestinations().insert(destination);
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
		PlaySound();
	}

	void Update(float dt)
	{

		anim.Update(dt * 1000);

		if (wantFood) {
			menjar -= kMenjarDecreasePerSecond * dt;

			menjar_bubble_timer -= dt;
			if (menjar_bubble_timer < 0) {
				anim.Ensure(DOGGO_IDLE);
			}
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
					PlaySound();
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

	if (wantFood) {
		// Draw bottom status.
		sf::Sprite status_sprite;
		status_sprite.setTexture(Assets::plantTexture);
		status_sprite.setTextureRect({ 52,32,17,16 });
		status_sprite.setOrigin(17 / 2, 0);
		status_sprite.setPosition(pos + vec(0.0f, 18.0f));
		window.draw(status_sprite);
		// Draw face.
		int happiness = std::min(int(menjar / (kMaxMenjar / 5)), 4);
		status_sprite.setTextureRect({ 106,52 - 12 * happiness,13,12 });
		status_sprite.setOrigin(6, 0);
		status_sprite.setPosition(pos + vec(0.0f, 21.0f));
		window.draw(status_sprite);
	}
  }

	void Feed() {
		menjar = kMaxMenjar;
		menjar_bubble_timer = kMenjarBubbleDuration;
		anim.Ensure(DOGGO_EAT);
		++StatsTracker::doggos_fed;
		PlaySound();
	}

};