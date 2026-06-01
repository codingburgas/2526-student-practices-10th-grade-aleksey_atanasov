#include "RegisterScreen.h"

RegisterScreen::RegisterScreen()
{
    username = "";
    password = "";

    usernameActive = false;
    passwordActive = false;
}

void RegisterScreen::update()
{
    Rectangle usernameBox =
    {
        300,
        180,
        300,
        40
    };

    Rectangle passwordBox =
    {
        300,
        260,
        300,
        40
    };

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        usernameActive =
            CheckCollisionPointRec(
                mousePosition,
                usernameBox
            );

        passwordActive =
            CheckCollisionPointRec(
                mousePosition,
                passwordBox
            );
    }

    int key = GetCharPressed();

    while (key > 0)
    {
        if (usernameActive)
        {
            username += (char)key;
        }
        else if (passwordActive)
        {
            password += (char)key;
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (usernameActive &&
            !username.empty())
        {
            username.pop_back();
        }

        if (passwordActive &&
            !password.empty())
        {
            password.pop_back();
        }
    }
}

void RegisterScreen::draw(
    int width,
    int height
)
{
    DrawText(
        "CREATE ACCOUNT",
        width / 2 - 160,
        80,
        40,
        BLACK
    );

    DrawText(
        "Username",
        width / 2 - 150,
        150,
        20,
        BLACK
    );

    DrawRectangle(
        width / 2 - 150,
        180,
        300,
        40,
        WHITE
    );

    DrawText(
        username.c_str(),
        width / 2 - 140,
        190,
        20,
        BLACK
    );

    DrawText(
        "Password",
        width / 2 - 150,
        230,
        20,
        BLACK
    );

    DrawRectangle(
        width / 2 - 150,
        260,
        300,
        40,
        WHITE
    );

    std::string hiddenPassword(
        password.length(),
        '*'
    );

    DrawText(
        hiddenPassword.c_str(),
        width / 2 - 140,
        270,
        20,
        BLACK
    );

    DrawRectangle(
        width / 2 - 100,
        340,
        200,
        50,
        DARKGREEN
    );

    DrawText(
        "CREATE ACCOUNT",
        width / 2 - 90,
        355,
        20,
        WHITE
    );
}

std::string RegisterScreen::getUsername() const
{
    return username;
}

std::string RegisterScreen::getPassword() const
{
    return password;
}

void RegisterScreen::clearInputs()
{
    username.clear();
    password.clear();
}