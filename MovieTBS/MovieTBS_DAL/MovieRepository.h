#pragma once

#include <vector>
#include "Movie.h"

class MovieRepository
{
private:
	std::vector<Movie> movies;

public:
	MovieRepository();

	void initializeMovies();

	const std::vector<Movie>& getMovies() const;
};
