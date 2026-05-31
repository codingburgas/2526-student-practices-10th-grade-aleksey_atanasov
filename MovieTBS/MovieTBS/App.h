#pragma once

#include "raylib.h"

#include "../MovieTBS_DAL/system_data.h"
#include "../MovieTBS_BLL/cinema_service.h"

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
    Screen currentScreen;

public:
    App();

    void run();
};