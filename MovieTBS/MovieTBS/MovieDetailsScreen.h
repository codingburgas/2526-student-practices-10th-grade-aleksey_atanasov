#pragma once

#include <vector>
#include "raylib.h"
#include "../MovieTBS_DAL/Movie.h"

class MovieDetailsScreen
{
private:
	const Movie* selectedMovie;

	Rectangle backButton;
	Rectangle chooseSeatsButton;

public:
	MovieDetailsScreen();

	void setMovie(const Movie* movie);

	void update();

	void draw(int width, int height, const std::string& username);

	bool isBackButtonPressed() const;

	bool isChooseSeatsButtonPressed() const;

	const Movie* getSelectedMovie() const;
};
