#include "system_data.h"

void SystemData::addCinema(const Cinema& cinema)
{
	cinemas.push_back(cinema);
}
std::vector<Cinema> SystemData::getCinemas() const
{
	return cinemas;
}