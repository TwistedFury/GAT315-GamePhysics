#include "World.h"
#include "Effector.h"
#include "Integrator.h"

Vector2 World::gravity;
int World::gravityScale;

// In step::: for auto* effector : effectors effector->Apply(bodies) This is after resetting acceleration
// In Draw::: need to add the for loop and draw the effectors as well!

void World::AddBody(Body body)
{
	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
}

void World::Step(float dt)
{
	for (auto* effector : effectors) effector->Apply(bodies);
	for (auto& body : bodies)
	{
		// Integration
		SemiImplicitEuler(body, dt);
		//body.velocity += gravity * 100 * dt;
		//body.position += body.velocity * dt;

		if (body.position.x + body.size > GetScreenWidth())
		{
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < 0)
		{
			body.position.x = 0 + body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y + body.size > GetScreenHeight())
		{
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < 0)
		{
			body.position.y = 0 + body.size;
			body.velocity.y *= -body.restitution;
		}

		body.acceleration = Vector2Zeros;
		body.AddForce(gravity * body.gravityScale * gravityScale);
	}
}

void World::Draw()
{
	for (auto* effector : effectors) effector->Draw();
	for (auto& body : bodies) body.Draw();
}
