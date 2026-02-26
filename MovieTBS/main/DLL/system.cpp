#include "system_data.h"
using namespace std;

void SystemData::addCinema(const Cinema& c)
{
    cinemas.push_back(c);
}

vector<Cinema> SystemData::getCinemas() const
{
    return cinemas;
}