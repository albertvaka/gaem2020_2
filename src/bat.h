#pragma once

#include "vector.h"
#include "animation.h"
#include "selfregister.h"
#include "steering_entity.h"
#include "steering_behavior.h"
#include "steering_behavior_applier.h"

struct JumpMan;
struct TileMap;

void AwakeNearbyBats(const vec& pos);

struct Bat : SteeringEntity, EntS<Bat>
{
	enum class State {
		SIESTA,
		FLYING,
	};

	SteeringBehaviorApplier steering;

	Animation anim;
	State state = State::FLYING;
	float timeToAwake = 1000.f; //Does nothing if > 999
	bool awakened = false;

	Bat(const vec& position, bool awake);

	void Update(float dt);
	void Draw() const;

	void DrawSenseArea() const;
};

