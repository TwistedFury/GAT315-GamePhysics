#pragma once
#include <raylib.h>

struct Body
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass = 1.0f;
	float size = 1.0f;
	float restitution = 1.0f;
	float gravityScale = 1.0f;
	float damping = 0.0f;

	void Step(float dt);
	void Draw() const;
	void AddForce(Vector2 force);
};