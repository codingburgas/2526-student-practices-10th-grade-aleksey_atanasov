#include "MovieRepository.h"

MovieRepository::MovieRepository()
{
	initializeMovies();
}

void MovieRepository::initializeMovies()
{
	movies.push_back(Movie("The Matrix", "Sci-Fi", 136, 8.7, 0, "A computer hacker learns from mysterious rebels about the true nature of reality.", 1999));
	movies.push_back(Movie("Inception", "Sci-Fi", 148, 8.8, 1, "A skilled thief who steals corporate secrets through dream-sharing technology.", 2010));
	movies.push_back(Movie("Titanic", "Romance", 194, 7.8, 2, "A seventeen-year-old aristocrat falls in love with a kind but poor artist aboard the luxurious, ill-fated R.M.S. Titanic.", 1997));
	movies.push_back(Movie("Avatar", "Action", 162, 7.8, 3, "A paraplegic Marine dispatched to the moon Pandora on a unique mission becomes torn between following his orders and protecting the world he feels is his home.", 2009));
	movies.push_back(Movie("Interstellar", "Sci-Fi", 169, 8.6, 4, "A team of explorers travel through a wormhole in space in an attempt to ensure humanity's survival.", 2014));
}

const std::vector<Movie>& MovieRepository::getMovies() const
{
	return movies;
}
