#pragma once

#include <string>

#include "raylib.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"

#include "../MovieTBS_DAL/system_data.h"
#include "../MovieTBS_DAL/UserRepo.h"

#include "../MovieTBS_BLL/cinema_service.h"
#include "../MovieTBS_BLL/AuthService.h"

enum class Screen
{
    MainMenu,
    Login,
    Register
};

class App
{
private:
    SystemData data;
    CinemaService cinemaService;

    UserRepository userRepository;
    AuthService authService;

    LoginScreen loginScreen;
    RegisterScreen registerScreen;

    Screen currentScreen;

    std::string usernameInput;
    std::string passwordInput;

    bool usernameActive;
    bool passwordActive;

    std::string statusMessage;

    bool isLoggedIn;
    std::string currentUser;

    Rectangle usernameBox;
    Rectangle passwordBox;

    Rectangle loginButton;
    Rectangle registerButton;
    Rectangle createAccountButton;

public:
    App();

    void run();
};