#include "bat.h"

#include "jumpman.h"
#include "assets.h"
#include "window.h"
#include "debug.h"

const float awake_player_distance = 100.f;
const float awake_nearby_distance = 70.f;

void AwakeNearbyBats(const vec& pos) {
	for (Bat* bat : Bat::getAll()) {
		if (pos.DistanceSq(bat->pos) < (awake_nearby_distance * awake_nearby_distance)) {
			bat->awakened = true;
		}
	}
}

Bat::Bat(const vec& pos, bool awake)
	: SteeringEntity(pos + vec(8.f, -2.f), 8.0f, 90.f, vec::Rand(-10.f, 0.f, 10.f, 10.f))
	, steering(this)
	, state(State::SIESTA)
{
	if (awake) {
		state = State::FLYING;
		anim.Ensure(BAT_FLYING);
		anim.loopable = true;
	}
	else {
		anim.Ensure(BAT_SIESTA);
		anim.Update(Random::roll(0, anim.GetCurrentAnimDuration())); // Start blink anim at different time intervals
	}

	steering.TileMapAvoidanceOn(TileMap::instance());
	steering.ForwardOn();
	steering.WanderOn();

	steering.BoundsAvoidanceOn(Camera::GetBounds());
}

void Bat::DrawSenseArea() const
{
	CircleBounds(pos, awake_player_distance).Draw(255,255,0);
	CircleBounds(pos, awake_nearby_distance).Draw(0, 255, 255);
}

void Bat::Update(float dt)
{

	anim.Update(dt * 1000);

	switch (state) {
	case State::SIESTA:
	{

		for (JumpMan* p : JumpMan::getAll()) {
			if (pos.DistanceSq(p->bounds().Center()) < (awake_player_distance * awake_player_distance) || awakened) {
				state = State::FLYING;
				anim.Ensure(BAT_FLYING);
				AwakeNearbyBats(pos);
				break;
			}
		}
		break;
	}
	break;
	case State::FLYING:
	{

		vec oldVel = vel;

		// Override velocity :D yolo
		vel = steering.CalculatePrioritized(dt);

		// Stay horizontal
		if (abs(vel.x) < abs(vel.y)) vel.x *= 2;

		// Always move at max speed
		vel = vel.Normalized() * max_speed;

		pos += vel * dt;

		// Flip anim
		if ((oldVel.x < 0 && vel.x > 0) || (oldVel.x > 0 && vel.x < 0)) {
			anim.Ensure(BAT_FLIP);
			anim.loopable = false;
		}
		if (anim.complete) {
			anim.Ensure(BAT_FLYING);
			anim.loopable = true;
		}
	}
	break;
	}

}


void Bat::Draw() const
{
	Window::Draw(Assets::marioTexture, pos)
		.withFlip(vel.x > 0)
		.withOrigin(16.f, 14.f)
		.withRect(anim.CurrentFrame());

}

