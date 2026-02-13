#include "raylib.h"

enum ScreenState
{
    SCREEN_MENU = 0,
    SCREEN_MOVIES,
    SCREEN_SEATS,
    SCREEN_BOOKINGS
};

static bool IsButtonClicked(Rectangle btn)
{
    // check if mouse is hovers the button
    Vector2 m = GetMousePosition();
    return CheckCollisionPointRec(m, btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

int main()
{
    // initialize window
    InitWindow(900, 600, "Movie Ticket Booking System");
    SetTargetFPS(60);

    ScreenState screen = SCREEN_MENU;

    // buttons
    Rectangle btnMovies = { 350, 200, 200, 60 };
    Rectangle btnSeats = { 350, 280, 200, 60 };
    Rectangle btnBookings = { 350, 360, 200, 60 };
    Rectangle btnBack = { 20, 20, 120, 45 };

    while (!WindowShouldClose())
    {
        // input
        if (screen == SCREEN_MENU)
        {
            if (IsButtonClicked(btnMovies))   screen = SCREEN_MOVIES;
            if (IsButtonClicked(btnSeats))    screen = SCREEN_SEATS;
            if (IsButtonClicked(btnBookings)) screen = SCREEN_BOOKINGS;
        }
        else
        {
            if (IsButtonClicked(btnBack)) screen = SCREEN_MENU;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // add title
        DrawText("Movie Ticket Booking System", 200, 70, 32, BLACK);

        if (screen == SCREEN_MENU)
        {
            // draw menu buttons
            DrawRectangleRec(btnMovies, LIGHTGRAY);
            DrawText("Movies", 410, 218, 24, BLACK);

            DrawRectangleRec(btnSeats, LIGHTGRAY);
            DrawText("Seats", 420, 298, 24, BLACK);

            DrawRectangleRec(btnBookings, LIGHTGRAY);
            DrawText("Bookings", 395, 378, 24, BLACK);

            DrawText("Click a button to continue", 310, 470, 18, DARKGRAY);
        }
        else
        {
            // draw back button
            DrawRectangleRec(btnBack, LIGHTGRAY);
            DrawText("< Back", 40, 32, 20, BLACK);

            // screen placeholders
            if (screen == SCREEN_MOVIES)
            {
                DrawText("Movies Screen", 360, 220, 28, BLACK);
                DrawText("Stage 1: UI only (no data yet)", 280, 270, 18, DARKGRAY);
            }
            else if (screen == SCREEN_SEATS)
            {
                DrawText("Seats Screen", 370, 220, 28, BLACK);
                DrawText("Stage 1: UI only (no data yet)", 280, 270, 18, DARKGRAY);
            }
            else if (screen == SCREEN_BOOKINGS)
            {
                DrawText("Bookings Screen", 340, 220, 28, BLACK);
                DrawText("Stage 1: UI only (no data yet)", 280, 270, 18, DARKGRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
