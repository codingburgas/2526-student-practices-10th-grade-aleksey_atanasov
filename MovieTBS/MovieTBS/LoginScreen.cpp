#include "LoginScreen.h"

LoginScreen::LoginScreen()
{
    username = "";
    password = "";

    usernameActive = false;
    passwordActive = false;

    statusMessage = "";
    statusMessageTime = 0.0;
    showStatusMessage = false;

    loginButton = { 0, 0, 0, 0 };
    registerButton = { 0, 0, 0, 0 };
    backButton = { 0, 0, 0, 0 };
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

    // Управление на статус съобщенията
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

    // LOGIN button - Left side
    loginButton = { (float)(width / 2 - 160), 340, 120, 50 };

    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, loginButton))
    {
        DrawRectangle(
            width / 2 - 160,
            340,
            120,
            50,
            DARKBLUE
        );
    }
    else
    {
        DrawRectangle(
            width / 2 - 160,
            340,
            120,
            50,
            BLUE
        );
    }

    DrawText(
        "LOGIN",
        width / 2 - 145,
        355,
        20,
        WHITE
    );

    // REGISTER button - Right side
    registerButton = { (float)(width / 2 + 40), 340, 120, 50 };

    if (CheckCollisionPointRec(mousePosition, registerButton))
    {
        DrawRectangle(
            width / 2 + 40,
            340,
            120,
            50,
            DARKGREEN
        );
    }
    else
    {
        DrawRectangle(
            width / 2 + 40,
            340,
            120,
            50,
            GREEN
        );
    }

    DrawText(
        "REGISTER",
        width / 2 + 50,
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
        else if (statusMessage.find("not found") != std::string::npos ||
                 statusMessage.find("Incorrect") != std::string::npos ||
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

void LoginScreen::setStatusMessage(const std::string& message)
{
    statusMessage = message;
    showStatusMessage = true;
    statusMessageTime = 0.0;
}

bool LoginScreen::isLoginButtonPressed() const
{
    Vector2 mousePosition = GetMousePosition();

    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(mousePosition, loginButton);
}

bool LoginScreen::isRegisterButtonPressed() const
{
    Vector2 mousePosition = GetMousePosition();

    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(mousePosition, registerButton);
}

bool LoginScreen::isBackButtonPressed() const
{
    Vector2 mousePosition = GetMousePosition();

    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(mousePosition, backButton);
}

void LoginScreen::resetButtonStates()
{
    showStatusMessage = false;
    statusMessage = "";
    statusMessageTime = 0.0;
}
