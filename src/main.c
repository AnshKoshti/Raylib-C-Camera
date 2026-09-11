#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

typedef struct
{
	Vector2 pos;
	float radius;
	Color color;
} Circle;

int rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

int main(void)
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "Raylib camera.");
	SetTargetFPS(60);

	// Player variables.
	Vector2 pos = {0.0f, 0.0f};
	float radius = 50.0f;
	Vector2 direction = {0.0f, 0.0f};
	float speed = 200.0f;

	// Initialize random circles.
	srand((unsigned int)time(NULL));
	Circle circles[100];
	Color choices[] = {RED, GREEN, BLUE, YELLOW, ORANGE};
	int num_choices = sizeof(choices) / sizeof(choices[0]);

	for (int i = 0; i < 100; i++)
	{
		circles[i] = (Circle){
			.pos = {(float)rand_int(-2000, 2000), (float)rand_int(-1000, 1000)},
			.radius = (float)rand_int(50, 200),
			.color = choices[rand() % num_choices]};
	}

	// Camera setup.
	Camera2D camera = {0};
	camera.target = pos;
	camera.offset = (Vector2){1920.0f / 2.0f, 1080.0f / 2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose())
	{
		// Input.
		direction.x = (float)(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
		direction.y = (float)(IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));
		direction = Vector2Normalize(direction);

		// Movement.
		float dt = GetFrameTime();
		pos.x += direction.x * speed * dt;
		pos.y += direction.y * speed * dt;

		// Update camera target to follow player.
		camera.target = pos;

		// Drawing.
		BeginDrawing();
		ClearBackground(WHITE);

		BeginMode2D(camera);
		for (int i = 0; i < 100; i++)
		{
			DrawCircleV(circles[i].pos, circles[i].radius, circles[i].color);
		}
		DrawCircleV(pos, radius, BLACK);
		EndMode2D();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
