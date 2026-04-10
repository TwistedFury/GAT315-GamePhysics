#include "Body.h"
#include <raylib.h>
#include <raymath.h>

void Body::Step(float dt)
{
}

void Body::Draw() const
{
	DrawCircleV(position, size, RED);
}

void Body::AddForce(Vector2 force)
{
	acceleration += force / mass;
}
