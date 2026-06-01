#include "LoginScreen.h"

LoginScreen::LoginScreen()
{
    username = "";
    password = "";

    usernameActive = false;
    passwordActive = false;
}

void LoginScreen::update()
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

void LoginScreen::draw(
    int width,
    int height
)
{
    DrawText(
        "LOGIN",
        width / 2 - 60,
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

    if (usernameActive)
{
    DrawRectangleLinesEx(
        { (float)(width / 2 - 150),180,300,40 },
        3,
        BLUE
    );
}
else
{
    DrawRectangleLinesEx(
        { (float)(width / 2 - 150),180,300,40 },
        1,
        GRAY
    );
}

DrawRectangle(
    width / 2 - 149,
    181,
    298,
    38,
    WHITE
);

    DrawText(
        username.c_str(),
        width / 2 - 140,
        190,
        20,
        BLACK
    );

    if (usernameActive)
    {
        if ((GetTime() * 2) - (int)(GetTime() * 2) < 0.5)
        {
            int textWidth =
                MeasureText(
                    username.c_str(),
                    20
                );

            DrawText(
                "|",
                width / 2 - 140 + textWidth,
                190,
                20,
                BLACK
            );
        }
    }

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

    if (passwordActive)
    {
        if ((GetTime() * 2) - (int)(GetTime() * 2) < 0.5)
        {
            int textWidth =
                MeasureText(
                    hiddenPassword.c_str(),
                    20
                );

            DrawText(
                "|",
                width / 2 - 140 + textWidth,
                270,
                20,
                BLACK
            );
        }
    }

    DrawRectangle(
        width / 2 - 75,
        340,
        150,
        50,
        DARKBLUE
    );

    DrawText(
        "LOGIN",
        width / 2 - 40,
        355,
        25,
        WHITE
    );
}

std::string LoginScreen::getUsername() const
{
    return username;
}

std::string LoginScreen::getPassword() const
{
    return password;
}

void LoginScreen::clearInputs()
{
    username.clear();
    password.clear();
}