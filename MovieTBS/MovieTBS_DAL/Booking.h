#pragma once

#include <string>
#include <vector>

class Booking
{
private:
	int id;
	std::string username;
	std::string movieTitle;
	std::vector<std::string> seats;
	std::string date;
	double totalPrice;

public:
	Booking();
	Booking(int id, const std::string& username, const std::string& movieTitle,
			const std::vector<std::string>& seats, const std::string& date, double totalPrice);

	int getId() const;
	std::string getUsername() const;
	std::string getMovieTitle() const;
	std::vector<std::string> getSeats() const;
	std::string getDate() const;
	double getTotalPrice() const;
};
