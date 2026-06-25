#pragma once

#include <string>

#include "raylib.h"

class RegisterScreen
{
private:
    std::string username;
    std::string password;

    bool usernameActive;
    bool passwordActive;

    std::string statusMessage;
    double statusMessageTime;
    bool showStatusMessage;

    Rectangle createAccountButton;
    Rectangle backButton;

public:
    RegisterScreen();

    void update();

    void draw(int width, int height);

    std::string getUsername() const;
    std::string getPassword() const;

    void clearInputs();

    void setStatusMessage(const std::string& message);

    bool isCreateAccountButtonPressed() const;
    bool isBackButtonPressed() const;

    void resetButtonStates();
};