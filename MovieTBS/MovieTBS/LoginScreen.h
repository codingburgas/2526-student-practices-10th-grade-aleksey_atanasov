#pragma once

#include <string>

#include "raylib.h"

class LoginScreen
{
private:
    std::string username;
    std::string password;

    bool usernameActive;
    bool passwordActive;

    Rectangle loginButton;
    Rectangle registerButton;
    Rectangle backButton;

    std::string statusMessage;
    double statusMessageTime;
    bool showStatusMessage;

public:
    LoginScreen();

    void update();

    void draw(int width, int height);

    std::string getUsername() const;
    std::string getPassword() const;

    void clearInputs();

    void setStatusMessage(const std::string& message);

    bool isLoginButtonPressed() const;
    bool isRegisterButtonPressed() const;
    bool isBackButtonPressed() const;

    void resetButtonStates();
};