#include "cinema_service.h"

CinemaService::CinemaService(SystemData* data)
{
	this->data = data;
}

void CinemaService::seedCinemas()
{
	data->addCinema(Cinema(1, "Cinema City", "Sofia"));
	data->addCinema(Cinema(2, "Arena", "Plovdiv"));
}

std::vector<Cinema> CinemaService::getCinemas() const
{
	return data->getCinemas();
}