#include "RegisterScreen.h"

RegisterScreen::RegisterScreen()
{
    username = "";
    password = "";

    usernameActive = false;
    passwordActive = false;

    statusMessage = "";
    statusMessageTime = 0.0;
    showStatusMessage = false;

    createAccountButton = { 0, 0, 0, 0 };
    backButton = { 0, 0, 0, 0 };
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

    // Status message management
    if (showStatusMessage)
    {
        statusMessageTime += GetFrameTime();
        if (statusMessageTime > 3.0)
        {
            showStatusMessage = false;
            statusMessage = "";
            statusMessageTime = 0.0;
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

    if (usernameActive)
    {
        DrawRectangleLinesEx(
            { (float)(width / 2 - 150), 180, 300, 40 },
            3,
            BLUE
        );
    }
    else
    {
        DrawRectangleLinesEx(
            { (float)(width / 2 - 150), 180, 300, 40 },
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

    if (passwordActive)
    {
        DrawRectangleLinesEx(
            { (float)(width / 2 - 150), 260, 300, 40 },
            3,
            BLUE
        );
    }
    else
    {
        DrawRectangleLinesEx(
            { (float)(width / 2 - 150), 260, 300, 40 },
            1,
            GRAY
        );
    }

    DrawRectangle(
        width / 2 - 149,
        261,
        298,
        38,
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

    // CREATE ACCOUNT button
    createAccountButton = { (float)(width / 2 - 100), 340, 200, 50 };

    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, createAccountButton))
    {
        DrawRectangle(
            width / 2 - 100,
            340,
            200,
            50,
            DARKGREEN
        );
    }
    else
    {
        DrawRectangle(
            width / 2 - 100,
            340,
            200,
            50,
            GREEN
        );
    }

    DrawText(
        "CREATE ACCOUNT",
        width / 2 - 90,
        355,
        20,
        WHITE
    );

    // BACK button - Top left
    backButton = { 30, 20, 100, 40 };

    if (CheckCollisionPointRec(mousePosition, backButton))
    {
        DrawRectangle(
            30,
            20,
            100,
            40,
            DARKGRAY
        );
    }
    else
    {
        DrawRectangle(
            30,
            20,
            100,
            40,
            GRAY
        );
    }

    DrawText(
        "BACK",
        55,
        30,
        18,
        WHITE
    );

    // Status message
    if (showStatusMessage)
    {
        Color messageColor = BLACK;

        if (statusMessage.find("successful") != std::string::npos ||
            statusMessage.find("successfully") != std::string::npos)
        {
            messageColor = DARKGREEN;
        }
        else if (statusMessage.find("exists") != std::string::npos ||
                 statusMessage.find("empty") != std::string::npos)
        {
            messageColor = RED;
        }

        DrawText(
            statusMessage.c_str(),
            width / 2 - MeasureText(statusMessage.c_str(), 18) / 2,
            420,
            18,
            messageColor
        );
    }
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

void RegisterScreen::setStatusMessage(const std::string& message)
{
    statusMessage = message;
    showStatusMessage = true;
    statusMessageTime = 0.0;
}

bool RegisterScreen::isCreateAccountButtonPressed() const
{
    Vector2 mousePosition = GetMousePosition();

    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(mousePosition, createAccountButton);
}

bool RegisterScreen::isBackButtonPressed() const
{
    Vector2 mousePosition = GetMousePosition();

    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(mousePosition, backButton);
}

void RegisterScreen::resetButtonStates()
{
    showStatusMessage = false;
    statusMessage = "";
    statusMessageTime = 0.0;
}
