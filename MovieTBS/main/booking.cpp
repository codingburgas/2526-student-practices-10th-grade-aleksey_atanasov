#include "../main/booking.h"

void Booking::addSeat(Seat s)
{
	seats.push_back(s);
}

double Booking::calculateTotal(double price)
{
	return seats.size() * price;
}
