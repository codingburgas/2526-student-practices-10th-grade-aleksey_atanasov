#pragma once
#include "../MovieTBS_DAL/system_data.h"

class CinemaService
{
private:
	SystemData* data;

public:
	CinemaService(SystemData* data);

	void seedCinemas();
	std::vector<Cinema> getCinemas() const;
};