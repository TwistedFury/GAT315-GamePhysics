#pragma once
#include <vector>
#include <raylib.h>
#include "Body.h"

class World
{
public:
	World()
	{
		gravity = { 0, -9.81f };
		gravityScale = -100;
	}

	void AddBody(Body body);
	void AddEffector(class Effector* effector);

	void Step(float dt);
	void Draw();

private:
	static Vector2 gravity;
	static int gravityScale;

	std::vector<Body> bodies;
	std::vector<class Effector*> effectors;
};