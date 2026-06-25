#include "MovieRepository.h"

MovieRepository::MovieRepository()
{
	initializeMovies();
}

void MovieRepository::initializeMovies()
{
	// Add 5 predefined movies with color codes (0 = purple, 1 = blue, 2 = dark blue, 3 = sky blue, 4 = dark purple)
	movies.push_back(Movie("The Matrix", "Sci-Fi", 136, 8.7, 0));
	movies.push_back(Movie("Inception", "Sci-Fi", 148, 8.8, 1));
	movies.push_back(Movie("Titanic", "Romance", 194, 7.8, 2));
	movies.push_back(Movie("Avatar", "Action", 162, 7.8, 3));
	movies.push_back(Movie("Interstellar", "Sci-Fi", 169, 8.6, 4));
}

const std::vector<Movie>& MovieRepository::getMovies() const
{
	return movies;
}
