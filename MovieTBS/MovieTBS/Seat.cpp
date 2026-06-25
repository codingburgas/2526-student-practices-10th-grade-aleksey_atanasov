#include "Seat.h"
#include <string>

Seat::Seat()
	: row('A'), column(1), state(SeatState::Available)
{
}

Seat::Seat(char row, int column, SeatState state)
	: row(row), column(column), state(state)
{
}

char Seat::getRow() const
{
	return row;
}

int Seat::getColumn() const
{
	return column;
}

SeatState Seat::getState() const
{
	return state;
}

void Seat::setState(SeatState newState)
{
	state = newState;
}

std::string Seat::getSeatCode() const
{
	return std::string(1, row) + std::to_string(column);
}
