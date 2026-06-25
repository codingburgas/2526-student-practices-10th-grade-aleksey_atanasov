#pragma once

#include <string>

enum class SeatState
{
	Available,
	Selected,
	Occupied
};

class Seat
{
private:
	char row;        // A-H
	int column;      // 1-6
	SeatState state;

public:
	Seat();

	Seat(char row, int column, SeatState state = SeatState::Available);

	char getRow() const;
	int getColumn() const;
	SeatState getState() const;

	void setState(SeatState newState);

	std::string getSeatCode() const;
};
