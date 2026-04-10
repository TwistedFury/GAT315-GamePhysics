#pragma once
#include <raylib.h>

struct Contact
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass = 1.0f;
	float size = 1.0f;
	float restitution = 1.0f;
};

// Methods