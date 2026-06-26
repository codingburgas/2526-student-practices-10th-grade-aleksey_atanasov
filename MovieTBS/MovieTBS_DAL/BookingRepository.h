#pragma once

#include <vector>
#include <string>
#include "Booking.h"

class BookingRepository
{
private:
	std::vector<Booking> bookings;
	int nextId;

	void loadFromFile();
	void saveToFile() const;

public:
	BookingRepository();

	int addBooking(const Booking& booking); // returns assigned id
	std::vector<Booking> getAllBookings() const;
	std::vector<Booking> getBookingsForUser(const std::string& username) const;
	bool removeBookingById(int id, Booking& outRemoved);
};
