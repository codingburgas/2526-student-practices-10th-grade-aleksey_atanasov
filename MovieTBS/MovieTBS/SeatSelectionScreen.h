#pragma once

#include <vector>
#include <map>
#include "raylib.h"
#include "Seat.h"
#include "../MovieTBS_DAL/Movie.h"

class SeatSelectionScreen
{
private:
	const Movie* selectedMovie;
	std::vector<Seat> seats;
	std::map<std::string, bool> seatOccupancy;  // Key: "A1", "A2", etc.

	Rectangle backButton;
	Rectangle bookTicketsButton;

	const float SEAT_SIZE = 30.0f;
	const float SEAT_SPACING = 5.0f;
	const float GRID_START_X = 150.0f;
	const float GRID_START_Y = 120.0f;
	const int COLUMNS = 8;
	const int ROWS = 6;
	const float TICKET_PRICE = 10.0f;

public:
	SeatSelectionScreen();

	void setMovie(const Movie* movie);

	void initializeSeats();

	void setSeatOccupancy(const std::map<std::string, bool>& occupancy);

	void update();

	void draw(int width, int height, const std::string& username);

	bool isBackButtonPressed() const;

	bool isBookTicketsButtonPressed() const;

	std::vector<std::string> getSelectedSeats() const;

	double getTotalPrice() const;

	void markSeatsAsOccupied(const std::vector<std::string>& seatCodes);

	std::map<std::string, bool> getSeatOccupancy() const;

	const Movie* getSelectedMovie() const;
};
