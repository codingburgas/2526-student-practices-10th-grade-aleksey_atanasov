#include "BookingRepository.h"
#include <fstream>
#include <sstream>

static const char* BOOKINGS_FILE = "bookings.txt";

BookingRepository::BookingRepository()
{
	nextId = 1;
	loadFromFile();
}

void BookingRepository::loadFromFile()
{
	std::ifstream in(BOOKINGS_FILE);
	if (!in) return;

	std::string line;
	while (std::getline(in, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string idStr, username, movieTitle, seatsStr, dateStr, priceStr;

		if (!std::getline(ss, idStr, '|')) continue;
		if (!std::getline(ss, username, '|')) continue;
		if (!std::getline(ss, movieTitle, '|')) continue;
		if (!std::getline(ss, seatsStr, '|')) continue;
		if (!std::getline(ss, dateStr, '|')) continue;
		if (!std::getline(ss, priceStr, '|')) continue;

		int id = std::stoi(idStr);
		double price = std::stod(priceStr);

		std::vector<std::string> seats;
		std::stringstream ssSeats(seatsStr);
		std::string seat;
		while (std::getline(ssSeats, seat, ','))
		{
			if (!seat.empty()) seats.push_back(seat);
		}

		Booking b(id, username, movieTitle, seats, dateStr, price);
		bookings.push_back(b);
		if (id >= nextId) nextId = id + 1;
	}

	in.close();
}

void BookingRepository::saveToFile() const
{
	std::ofstream out(BOOKINGS_FILE, std::ios::trunc);
	if (!out) return;

	for (const auto& b : bookings)
	{
		out << b.getId() << "|" << b.getUsername() << "|" << b.getMovieTitle() << "|";
		// seats joined by comma
		const auto seats = b.getSeats();
		for (size_t i = 0; i < seats.size(); ++i)
		{
			out << seats[i];
			if (i + 1 < seats.size()) out << ",";
		}
		out << "|" << b.getDate() << "|" << b.getTotalPrice() << "\n";
	}

	out.close();
}

int BookingRepository::addBooking(const Booking& booking)
{
	Booking b = booking;
	// assign id if not set
	int assignedId = nextId++;
	// Reconstruct booking with assigned id
	Booking stored(assignedId, b.getUsername(), b.getMovieTitle(), b.getSeats(), b.getDate(), b.getTotalPrice());
	bookings.push_back(stored);
	saveToFile();
	return assignedId;
}

std::vector<Booking> BookingRepository::getAllBookings() const
{
	return bookings;
}

std::vector<Booking> BookingRepository::getBookingsForUser(const std::string& username) const
{
	std::vector<Booking> result;
	for (const auto& b : bookings)
	{
		if (b.getUsername() == username)
			result.push_back(b);
	}
	return result;
}

bool BookingRepository::removeBookingById(int id, Booking& outRemoved)
{
	for (size_t i = 0; i < bookings.size(); ++i)
	{
		if (bookings[i].getId() == id)
		{
			outRemoved = bookings[i];
			bookings.erase(bookings.begin() + i);
		saveToFile();
			return true;
		}
	}
	return false;
}
