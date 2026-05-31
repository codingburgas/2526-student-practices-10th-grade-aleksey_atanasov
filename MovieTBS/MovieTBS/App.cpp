#include "App.h"

App::App()
    : cinemaService(&data)
{
    cinemaService.seedCinemas();

    currentScreen = Screen::MainMenu;
}

void App::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(900, 600, "MovieFlow");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        int width = GetScreenWidth();
        int height = GetScreenHeight();

        Vector2 mousePosition = GetMousePosition();

        Rectangle loginButton =
        {
            (float)(width / 2 - 120),
            200,
            240,
            50
        };

        Rectangle registerButton =
        {
            (float)(width / 2 - 120),
            280,
            240,
            50
        };

        Rectangle exitButton =
        {
            (float)(width / 2 - 120),
            360,
            240,
            50
        };

        // Navigation
        if (currentScreen == Screen::MainMenu)
        {
            if (CheckCollisionPointRec(mousePosition, loginButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = Screen::Login;
            }

            if (CheckCollisionPointRec(mousePosition, registerButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = Screen::Register;
            }

            if (CheckCollisionPointRec(mousePosition, exitButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
        }

        if (currentScreen != Screen::MainMenu &&
            IsKeyPressed(KEY_BACKSPACE))
        {
            currentScreen = Screen::MainMenu;
        }

        BeginDrawing();

        ClearBackground(BEIGE);

        switch (currentScreen)
        {
        case Screen::MainMenu:

            DrawText(
                "MovieFlow",
                width / 2 - 100,
                80,
                40,
                BLACK
            );

            DrawRectangleRec(loginButton, DARKBLUE);

            DrawText(
                "Login",
                width / 2 - 35,
                215,
                25,
                WHITE
            );

            DrawRectangleRec(registerButton, DARKGREEN);

            DrawText(
                "Create Account",
                width / 2 - 95,
                295,
                25,
                WHITE
            );

            DrawRectangleRec(exitButton, MAROON);

            DrawText(
                "Exit",
                width / 2 - 25,
                375,
                25,
                WHITE
            );

            break;

        case Screen::Login:

            DrawText(
                "LOGIN",
                width / 2 - 60,
                100,
                40,
                BLACK
            );

            DrawText(
                "Press BACKSPACE to return",
                width / 2 - 140,
                180,
                20,
                DARKGRAY
            );

            break;

        case Screen::Register:

            DrawText(
                "CREATE ACCOUNT",
                width / 2 - 170,
                100,
                40,
                BLACK
            );

            DrawText(
                "Press BACKSPACE to return",
                width / 2 - 140,
                180,
                20,
                DARKGRAY
            );

            break;
        }

        EndDrawing();
    }

    CloseWindow();
}