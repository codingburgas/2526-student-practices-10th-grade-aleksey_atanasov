#pragma once

#include <vector>
#include "raylib.h"
#include "../MovieTBS_DAL/Movie.h"

class MoviesScreen
{
private:
	std::vector<Movie> movies;

	Rectangle logoutButton;

	int hoveredMovieIndex;
	int hoveredButtonIndex;

public:
	MoviesScreen();

	void setMovies(const std::vector<Movie>& movieList);

	void update();

	void draw(int width, int height, const std::string& username);

	bool isLogoutButtonPressed() const;

	bool isViewDetailsPressed(int movieIndex) const;

	int getHoveredMovieIndex() const;
};
