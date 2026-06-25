#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include "../MovieTBS_DAL/Movie.h"

class BookingConfirmationScreen
{
private:
	const Movie* selectedMovie;
	std::vector<std::string> bookedSeats;
	double totalPrice;

	Rectangle backToMoviesButton;

public:
	BookingConfirmationScreen();

	void setBookingInfo(const Movie* movie, const std::vector<std::string>& seats, double price);

	void update();

	void draw(int width, int height, const std::string& username);

	bool isBackToMoviesButtonPressed() const;

	const Movie* getSelectedMovie() const;
};
