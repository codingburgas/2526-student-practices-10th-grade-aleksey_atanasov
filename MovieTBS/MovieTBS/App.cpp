#include "App.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"

App::App()
    : cinemaService(&data),
    authService(&userRepository)
{
    cinemaService.seedCinemas();

    currentScreen = Screen::MainMenu;

    usernameInput = "";
    passwordInput = "";

    usernameActive = false;
    passwordActive = false;

    statusMessage = "";

    isLoggedIn = false;
    currentUser = "";

    usernameBox = { 0,0,0,0 };
    passwordBox = { 0,0,0,0 };

    loginButton = { 0,0,0,0 };
    registerButton = { 0,0,0,0 };
    createAccountButton = { 0,0,0,0 };
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

        Rectangle userButton =
        {
            (float)(width - 60),
            20,
            40,
            40
        };

        // Main Menu -> Login
        if (currentScreen == Screen::MainMenu)
        {
            if (CheckCollisionPointRec(mousePosition, userButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = Screen::Login;
            }
        }

        // Login -> Register
        if (currentScreen == Screen::Login &&
            IsKeyPressed(KEY_R))
        {
            currentScreen = Screen::Register;
        }

        BeginDrawing();

        ClearBackground(BEIGE);

        switch (currentScreen)
        {
        case Screen::MainMenu:

            DrawText(
                "MovieFlow",
                width / 2 - 100,
                60,
                40,
                BLACK
            );

            DrawText(
                "Welcome to MovieFlow",
                width / 2 - 120,
                150,
                25,
                DARKGRAY
            );

            DrawText(
                "Browse movies and book tickets",
                width / 2 - 170,
                190,
                20,
                GRAY
            );

            DrawRectangleRec(
                userButton,
                DARKBLUE
            );

            DrawText(
                "U",
                width - 48,
                28,
                24,
                WHITE
            );

            break;

        case Screen::Login:

            loginScreen.update();

            loginScreen.draw(
                width,
                height
            );

            break;

        case Screen::Register:

            registerScreen.update();

            registerScreen.draw(
                width,
                height
            );

            break;
        }

        EndDrawing();
    }

    CloseWindow();
}