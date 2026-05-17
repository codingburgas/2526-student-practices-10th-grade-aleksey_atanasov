#pragma once
#include "raylib.h"
#include "../MovieTBS_BLL/cinema_service.h"

class App
{
private:
	SystemData data;
	CinemaService cinemaService;

public:
	App();

	void run();
};