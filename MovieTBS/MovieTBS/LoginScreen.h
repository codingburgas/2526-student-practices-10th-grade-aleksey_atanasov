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
public:
    LoginScreen();

    void update();

    void draw(int width, int height);

    std::string getUsername() const;
    std::string getPassword() const;

    void clearInputs();
};