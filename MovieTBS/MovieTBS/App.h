#pragma once

#include <string>

#include "raylib.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"
#include "MoviesScreen.h"
#include "MovieDetailsScreen.h"

#include "../MovieTBS_DAL/system_data.h"
#include "../MovieTBS_DAL/UserRepo.h"
#include "../MovieTBS_DAL/MovieRepository.h"

#include "../MovieTBS_BLL/cinema_service.h"
#include "../MovieTBS_BLL/AuthService.h"

enum class Screen
{
    MainMenu,
    Login,
    Register,
    Movies,
    MovieDetails
};

class App
{
private:
    SystemData data;
    CinemaService cinemaService;

    UserRepository userRepository;
    AuthService authService;

    MovieRepository movieRepository;

    LoginScreen loginScreen;
    RegisterScreen registerScreen;
    MoviesScreen moviesScreen;
    MovieDetailsScreen movieDetailsScreen;

    Screen currentScreen;

    int selectedMovieIndex;

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

    void handleLoginScreen();
    void handleRegisterScreen();
    void handleMainMenu();
    void handleMoviesScreen();
    void handleMovieDetailsScreen();

public:
    App();

    void run();
};