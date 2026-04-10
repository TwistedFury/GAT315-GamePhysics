#pragma once
#include "Effector.h"
#include <raylib.h>

class PointEffector : public Effector
{
public:
	PointEffector(Vector2 pos, float size, float fm) : 
		position{pos}, 
		size{size}, 
		forceMagnitude{fm}
	{ }

	void Apply(std::vector<Body>& bodies) override;
	void Draw() override;

private:
	Vector2 position;
	float size;
	float forceMagnitude;

};

