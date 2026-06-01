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

public:
    RegisterScreen();

    void update();

    void draw(int width, int height);

    std::string getUsername() const;
    std::string getPassword() const;

    void clearInputs();
};