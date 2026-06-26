#pragma once

#include <string>
#include <map>
#include <vector>

#include "raylib.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"
#include "MoviesScreen.h"
#include "MovieDetailsScreen.h"
#include "SeatSelectionScreen.h"
#include "BookingConfirmationScreen.h"
#include "MyTicketsScreen.h"

#include "../MovieTBS_DAL/system_data.h"
#include "../MovieTBS_DAL/UserRepo.h"
#include "../MovieTBS_DAL/MovieRepository.h"
#include "../MovieTBS_DAL/BookingRepository.h"

#include "../MovieTBS_BLL/cinema_service.h"
#include "../MovieTBS_BLL/AuthService.h"

enum class Screen
{
    MainMenu,
    Login,
    Register,
    Movies,
    MovieDetails,
    MyTickets,
    SeatSelection,
    BookingConfirmation
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
    SeatSelectionScreen seatSelectionScreen;
    BookingConfirmationScreen bookingConfirmationScreen;
    MyTicketsScreen myTicketsScreen;

    Screen currentScreen;

    int selectedMovieIndex;
    std::map<std::string, bool> globalSeatOccupancy;  // Persists across bookings

    // Bookings repository (DAL)
    BookingRepository bookingRepository;

    std::string usernameInput;
    std::string passwordInput;

    bool usernameActive;
    bool passwordActive;

    std::string statusMessage;
    float statusTimer; // seconds remaining for status message

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
    void handleSeatSelectionScreen();
    void handleBookingConfirmationScreen();
    void handleMyTicketsScreen();

public:
    App();

    void run();
};