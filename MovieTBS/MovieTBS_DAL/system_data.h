#pragma once
#include <vector>
#include "cinema.h"

class SystemData
{
private:
	std::vector<Cinema> cinemas;
public:
	void addCinema(const Cinema& cinema);
	std::vector<Cinema> getCinemas() const;
};