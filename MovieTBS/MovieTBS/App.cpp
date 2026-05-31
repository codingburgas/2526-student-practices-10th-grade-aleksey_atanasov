#include "App.h"

App::App() : cinemaService(&data)
{
	cinemaService.seedCinemas();
}

void App::run()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 600, "Movie Ticket Booking System");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		int width = GetScreenWidth();
		int height = GetScreenHeight();

		int count = cinemaService.getCinemas().size();

		BeginDrawing();
		ClearBackground(BEIGE);

		const char* title = "Movie Ticket Booking System";
		int titleSize = 30;
		int titleWidth = MeasureText(title, titleSize);

		DrawText(title, width / 2 - titleWidth / 2, height / 2 - 50, titleSize, BLACK);

		DrawText(TextFormat("Cinemas: %d", count), width / 2 - 80, height / 2 + 20, 20, DARKGRAY);

		DrawText("Press ESC to exit", width / 2 - 90, height - 40, 18, GRAY);

		EndDrawing();
	}
	CloseWindow();
}