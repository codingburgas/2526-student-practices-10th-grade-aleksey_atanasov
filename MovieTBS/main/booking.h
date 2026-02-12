#pragma once
#include <vector>
#include "../main/Seats.h"
using namespace std;

class Booking
{
public:
	vector<Seat> seats;

	void addSeat(Seat s);
	double calculateTotal(double price);
};