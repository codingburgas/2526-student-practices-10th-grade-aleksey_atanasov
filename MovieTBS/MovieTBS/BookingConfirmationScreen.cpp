#include "BookingConfirmationScreen.h"
#include <iomanip>
#include <sstream>

BookingConfirmationScreen::BookingConfirmationScreen()
{
	selectedMovie = nullptr;
	totalPrice = 0.0;
	backToMoviesButton = { 0, 0, 0, 0 };
}

void BookingConfirmationScreen::setBookingInfo(const Movie* movie, const std::vector<std::string>& seats, double price)
{
	selectedMovie = movie;
	bookedSeats = seats;
	totalPrice = price;
}

void BookingConfirmationScreen::update()
{
	// No complex interactions needed
}

void BookingConfirmationScreen::draw(int width, int height, const std::string& username)
{
	if (selectedMovie == nullptr)
	{
		DrawText("No booking information available", width / 2 - 150, height / 2, 20, RED);
		return;
	}

	// Background
	DrawRectangle(0, 0, width, height, BEIGE);

	// Draw success message
	DrawText(
		"BOOKING CONFIRMED!",
		width / 2 - 150,
		40,
		40,
		DARKGREEN
	);

	// Draw confirmation box
	Rectangle confirmationBox = { 60.0f, 120.0f, (float)width - 120, (float)height - 220 };
	DrawRectangleRec(confirmationBox, WHITE);
	DrawRectangleLinesEx(confirmationBox, 2, DARKBLUE);

	// Movie info
	float contentX = 100.0f;
	float contentY = 160.0f;

	// Movie Title
	DrawText(
		"Movie Title:",
		(int)contentX,
		(int)contentY,
		16,
		DARKGRAY
	);

	DrawText(
		selectedMovie->getTitle().c_str(),
		(int)(contentX + 20),
		(int)(contentY + 30),
		20,
		DARKBLUE
	);

	contentY += 80;

	// Selected Seats
	DrawText(
		"Selected Seats:",
		(int)contentX,
		(int)contentY,
		16,
		DARKGRAY
	);

	std::string seatsDisplay = "";
	for (size_t i = 0; i < bookedSeats.size(); i++)
	{
		seatsDisplay += bookedSeats[i];
		if (i < bookedSeats.size() - 1)
			seatsDisplay += ", ";
	}

	DrawText(
		seatsDisplay.c_str(),
		(int)(contentX + 20),
		(int)(contentY + 30),
		18,
		GREEN
	);

	contentY += 80;

	// Number of tickets
	std::string numTickets = "Number of Tickets: " + std::to_string(bookedSeats.size());
	DrawText(
		numTickets.c_str(),
		(int)contentX,
		(int)contentY,
		16,
		DARKGRAY
	);

	contentY += 50;

	// Price (highlighted)
	DrawRectangle(
		(int)(contentX - 10),
		(int)(contentY - 5),
		250,
		50,
		SKYBLUE
	);

	std::ostringstream priceStream;
	priceStream << std::fixed << std::setprecision(2) << totalPrice;
	std::string priceText = "Total Price: $" + priceStream.str();

	DrawText(
		priceText.c_str(),
		(int)contentX,
		(int)contentY,
		20,
		DARKBLUE
	);

	// Confirmation details
	contentY += 80;

	DrawText(
		"Your tickets have been successfully booked!",
		(int)contentX,
		(int)contentY,
		14,
		DARKGREEN
	);

	contentY += 30;

	DrawText(
		"These seats are now reserved and cannot be selected by other users.",
		(int)contentX,
		(int)contentY,
		12,
		DARKGRAY
	);

	// Back to Movies button
	backToMoviesButton = { (float)(width / 2 - 100), (float)(height - 80), 200.0f, 50.0f };

	Vector2 mousePos = GetMousePosition();

	if (CheckCollisionPointRec(mousePos, backToMoviesButton))
	{
		DrawRectangleRec(backToMoviesButton, DARKBLUE);
	}
	else
	{
		DrawRectangleRec(backToMoviesButton, BLUE);
	}

	DrawRectangleLinesEx(backToMoviesButton, 2, DARKBLUE);

	std::string buttonText = "BACK TO MOVIES";
	int buttonTextWidth = MeasureText(buttonText.c_str(), 16);
	DrawText(
		buttonText.c_str(),
		(int)(backToMoviesButton.x + (backToMoviesButton.width - buttonTextWidth) / 2),
		(int)(backToMoviesButton.y + 15),
		16,
		WHITE
	);
}

bool BookingConfirmationScreen::isBackToMoviesButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, backToMoviesButton);
}

const Movie* BookingConfirmationScreen::getSelectedMovie() const
{
	return selectedMovie;
}
