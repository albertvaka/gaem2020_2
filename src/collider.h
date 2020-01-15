#pragma once

#include "selfregister.h"
#include "entity.h"
#include <functional>
#include "entity_example.h"

bool Collision(Entity* entity_a, Entity* entity_b)
{
	int COLLISION_SIZE = 1600;

	Mates::xy a = entity_a->pos;
	Mates::xy b = entity_b->pos;

	//rectangle colision
	return
		(a.x < b.x + COLLISION_SIZE && a.x + COLLISION_SIZE > b.x &&
			a.y < b.y + COLLISION_SIZE && a.y + COLLISION_SIZE > b.y);
}


template <typename T, typename U>
void collide(const std::vector<T*>& setA, const std::vector<U*>& setB, void (*callback)(T*, U*)) {
	for (auto a : setA) {
		for (auto b : setB) {
			if (a == b) continue;
			if (Collision(a, b)) {
				callback(a, b);
			}
		}
	}
}

//FIXME: this should be a lambda, but doesn't work yet
void entityExample_collision_callback(EntityExample* a, EntityExample* b) {
	if (b->state != EntityState::COLLIDED) {
		b->state = EntityState::COLLIDED;
		b->timer = 0;
		b->speed.x = -b->speed.x;
		b->speed.y = -b->speed.y;
	}
}

void UpdateCollisions(int dt) {
	// If EntityExample collides with EntityExample, call entityExample_collision_callback
	collide(EntS<EntityExample*>::getAll(), EntS<EntityExample*>::getAll(), entityExample_collision_callback);
}
