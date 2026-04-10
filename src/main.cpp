/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>
#include "../Body.h"
#include "../Random.h"
#include "../Integrator.h"
#include "../World.h"
#include <string>
#include "../PointEffector.h"

Vector2 gravity{ 0, 9.81f };

int main ()
{
	std::vector<Body> bodies;
	bodies.reserve(1000);

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	World world;

	float timeAccum = 0.0f;
	float fixedTimeStep = 1.0f / 60.0f;
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float dt = GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_GRAVE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			Body body;
			body.position = GetMousePosition();
			
			// Get Random Unit Circle Vector
			float angle = GetRandomFloat() * (2 * PI);
			Vector2 dir = { cosf(angle), sinf(angle) };

			body.velocity = dir * ((GetRandomFloat() * 300) + 50.0f);
			body.size = (GetRandomFloat() * 20.0f) + 5;
			body.restitution = 0.5f + (GetRandomFloat() * 0.5f);
			body.mass = 1;
			body.acceleration = { 0, 0 };

			world.AddBody(body);
		}

		// UPDATE
		timeAccum += dt;
		while (timeAccum > fixedTimeStep)
		{
			world.Step(fixedTimeStep);
			timeAccum -= fixedTimeStep;
		}

		for (auto& body : bodies) body.acceleration = gravity * body.gravityScale * 100;
		//for (auto& body : bodies) body.AddForce(gravity * 100);

		// POINT EFFECTOR
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 pos = GetMousePosition();
			PointEffector* pe = new PointEffector(pos, 100, -2500);
			world.AddEffector(pe);
		}

		

		// DRAW
		BeginDrawing();

		DrawCircleV(GetMousePosition(), 5, BEIGE);

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		std::string fpsText = "FPS: ";
		fpsText += std::to_string(GetFPS());
		DrawText(fpsText.c_str(), 40, 40, 20, WHITE);

		// Draw Bodies
		world.Draw();
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
