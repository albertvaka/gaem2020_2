#pragma once

#include "vector.h"
#include "bounds.h"

struct Entity
{
	Entity() : pos (0.f,0.f) {}
	Entity(const vec& pos) : pos(pos) {}
	vec pos;
	vec vel = vec(0.f,0.f);
	bool alive = true;
};

struct BoxEntity : Entity {
	BoxEntity(const vec& pos, const vec& size) : Entity(pos), size(size) {}
	BoxEntity(const Bounds& b) : Entity(b.Center()), size(b.Size()) {} //note that entities position is on their center

	vec size;

	Bounds bounds() const {
		return Bounds::fromCenter(pos, size);
	}

	void drawBounds(short r, short g, short b) const {
		bounds().Draw(r,g,b);
	}
};

struct CircleEntity : Entity {
	CircleEntity() : radius(8.f) {}
	CircleEntity(const vec& pos, float radius) : Entity(pos), radius(radius) {}

	float radius;
	
	CircleBounds bounds() const {
		return CircleBounds(pos, radius);
	}

	void drawBounds(short r, short g, short b) const {
		bounds().Draw(r,g,b);
	}
};


