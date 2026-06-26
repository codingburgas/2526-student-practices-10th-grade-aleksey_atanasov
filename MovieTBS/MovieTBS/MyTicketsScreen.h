#pragma once

#include <vector>
#include "raylib.h"
#include "../MovieTBS_DAL/Booking.h"

class MyTicketsScreen
{
private:
	std::vector<Booking> bookings; // bookings to display (filtered by user)

	Rectangle backButton;

	// For per-card interactions
	int hoveredBookingIndex;
	int hoveredCancelIndex;

	// Confirmation modal
	bool showConfirm;
	int pendingCancelIndex;
	bool confirmYesFlag;
	bool confirmNoFlag;

public:
	MyTicketsScreen();

	void setBookings(const std::vector<Booking>& bks);

	void update();
	void draw(int width, int height, const std::string& username);

	bool isBackButtonPressed() const;

	int getHoveredBookingIndex() const;
	bool isCancelBookingPressed(int bookingIndex) const;

	// Confirmation related
	int getPendingCancelBookingIndex() const;
	bool isConfirmYesPressed();
	bool isConfirmNoPressed();
	void clearPendingCancel();

	int getBookingIdAt(int bookingIndex) const;
};
