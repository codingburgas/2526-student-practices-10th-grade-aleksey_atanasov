#include "Booking.h"

Booking::Booking()
	: id(0), username(""), movieTitle(""), seats(), date(""), totalPrice(0.0)
{
}

Booking::Booking(int id, const std::string& username, const std::string& movieTitle,
	const std::vector<std::string>& seats, const std::string& date, double totalPrice)
	: id(id), username(username), movieTitle(movieTitle), seats(seats), date(date), totalPrice(totalPrice)
{
}

int Booking::getId() const { return id; }
std::string Booking::getUsername() const { return username; }
std::string Booking::getMovieTitle() const { return movieTitle; }
std::vector<std::string> Booking::getSeats() const { return seats; }
std::string Booking::getDate() const { return date; }
double Booking::getTotalPrice() const { return totalPrice; }
