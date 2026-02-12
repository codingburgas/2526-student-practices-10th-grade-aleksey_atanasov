#pragma once

class Seat
{
public:
	int row;
	int col;
	bool reserved;

	Seat(int r, int c);
};