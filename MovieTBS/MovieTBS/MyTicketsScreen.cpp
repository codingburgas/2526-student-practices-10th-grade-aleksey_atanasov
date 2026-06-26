#include "MyTicketsScreen.h"
#include <sstream>
#include <iomanip>

#include "MyTicketsScreen.h"
#include <sstream>
#include <iomanip>

MyTicketsScreen::MyTicketsScreen()
{
	backButton = { 0, 0, 0, 0 };
	hoveredBookingIndex = -1;
	hoveredCancelIndex = -1;
	showConfirm = false;
	pendingCancelIndex = -1;
	confirmYesFlag = false;
	confirmNoFlag = false;
}

void MyTicketsScreen::setBookings(const std::vector<Booking>& bks)
{
	bookings = bks;
}

void MyTicketsScreen::update()
{
	Vector2 mousePos = GetMousePosition();
	hoveredBookingIndex = -1;
	hoveredCancelIndex = -1;

	// If confirmation modal is showing, handle its buttons
	if (showConfirm)
	{
		// Modal button rects (centered)
		float modalW = 400, modalH = 160;
		float modalX = GetScreenWidth() / 2 - modalW / 2;
		float modalY = GetScreenHeight() / 2 - modalH / 2;
		Rectangle yesRect = { modalX + 60, modalY + 100, 100, 40 };
		Rectangle noRect = { modalX + 240, modalY + 100, 100, 40 };
		if (CheckCollisionPointRec(mousePos, yesRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			confirmYesFlag = true;
			showConfirm = false;
		}
		else if (CheckCollisionPointRec(mousePos, noRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			confirmNoFlag = true;
			showConfirm = false;
		}
		return;
	}

	// Determine hovered card
	for (int i = 0; i < (int)bookings.size(); ++i)
	{
		int col = i % 2;
		int row = i / 2;
		float cardX = 60 + col * 420;
		float cardY = 120 + row * 180;
		Rectangle cardRect = { cardX, cardY, 380, 160 };
		if (CheckCollisionPointRec(mousePos, cardRect))
		{
			hoveredBookingIndex = i;
			// Check cancel button rect
			Rectangle cancelRect = { cardX + 260, cardY + 110, 100, 30 };
			if (CheckCollisionPointRec(mousePos, cancelRect))
			{
				hoveredCancelIndex = i;
				// If clicked, open confirmation
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					pendingCancelIndex = i;
					showConfirm = true;
				}
			}
		}
	}
}

void MyTicketsScreen::draw(int width, int height, const std::string& username)
{
	DrawText("MY TICKETS", 60, 20, 32, BLACK);

	std::string userText = "User: " + username;
	int userTextWidth = MeasureText(userText.c_str(), 18);

	DrawText(userText.c_str(), width - userTextWidth - 140, 25, 18, DARKBLUE);

	// Back to Movies button
	backButton = { (float)(width - 130), 20, 120, 40 };

	Vector2 mousePos = GetMousePosition();

	if (CheckCollisionPointRec(mousePos, backButton))
	{
		DrawRectangleRec(backButton, DARKBLUE);
	}
	else
	{
		DrawRectangleRec(backButton, BLUE);
	}

	DrawText("< BACK", width - 115, 31, 18, WHITE);

	if (bookings.empty())
	{
		DrawText("You have no bookings yet.", width / 2 - 120, height / 2 - 20, 18, DARKGRAY);
		return;
	}

	// Draw booking cards (2 columns)
	for (int i = 0; i < (int)bookings.size(); ++i)
	{
		int col = i % 2;
		int row = i / 2;
		float cardX = 60 + col * 420;
		float cardY = 120 + row * 180;
		Rectangle cardRect = { cardX, cardY, 380, 160 };

		// Card background
		if (hoveredBookingIndex == i)
		{
			DrawRectangleRec(cardRect, LIGHTGRAY);
			DrawRectangleLinesEx(cardRect, 2, DARKBLUE);
		}
		else
		{
			DrawRectangleRec(cardRect, WHITE);
			DrawRectangleLinesEx(cardRect, 1, GRAY);
		}

		// Movie Title
		DrawText(bookings[i].getMovieTitle().c_str(), (int)(cardX + 10), (int)(cardY + 10), 18, BLACK);

		// Date and total
		DrawText(bookings[i].getDate().c_str(), (int)(cardX + 10), (int)(cardY + 40), 14, DARKGRAY);

		std::ostringstream priceStream;
		priceStream << std::fixed << std::setprecision(2) << bookings[i].getTotalPrice();
		std::string priceText = "Total: $" + priceStream.str();
		DrawText(priceText.c_str(), (int)(cardX + 10), (int)(cardY + 60), 14, DARKGREEN);

		// Seats
		std::string seatsStr = "Seats: ";
		auto seats = bookings[i].getSeats();
		for (size_t s = 0; s < seats.size(); ++s)
		{
			seatsStr += seats[s];
			if (s < seats.size() - 1) seatsStr += ", ";
		}
		DrawText(seatsStr.c_str(), (int)(cardX + 10), (int)(cardY + 90), 14, DARKBLUE);

		// Cancel button
		Rectangle cancelRect = { cardX + 260, cardY + 110, 100, 30 };
		if (hoveredCancelIndex == i)
		{
			DrawRectangleRec(cancelRect, RED);
		}
		else
		{
			DrawRectangleRec(cancelRect, MAROON);
		}
		DrawText("CANCEL", (int)(cancelRect.x + 20), (int)(cancelRect.y + 6), 14, WHITE);
	}

	// Draw confirmation modal if needed
	if (showConfirm && pendingCancelIndex >= 0 && pendingCancelIndex < (int)bookings.size())
	{
		float modalW = 400, modalH = 160;
		float modalX = width / 2 - modalW / 2;
		float modalY = height / 2 - modalH / 2;
		Rectangle modalRect = { modalX, modalY, modalW, modalH };
		DrawRectangleRec(modalRect, WHITE);
		DrawRectangleLinesEx(modalRect, 2, DARKBLUE);

		std::string prompt = "Cancel booking for " + bookings[pendingCancelIndex].getMovieTitle() + "?";
		DrawText(prompt.c_str(), (int)(modalX + 20), (int)(modalY + 30), 16, BLACK);

		// Yes/No buttons
		Rectangle yesRect = { modalX + 60, modalY + 100, 100, 40 };
		Rectangle noRect = { modalX + 240, modalY + 100, 100, 40 };

		Vector2 m = GetMousePosition();
		if (CheckCollisionPointRec(m, yesRect)) DrawRectangleRec(yesRect, DARKGREEN); else DrawRectangleRec(yesRect, GREEN);
		if (CheckCollisionPointRec(m, noRect)) DrawRectangleRec(noRect, DARKGRAY); else DrawRectangleRec(noRect, LIGHTGRAY);

		DrawText("YES", (int)(yesRect.x + 30), (int)(yesRect.y + 10), 18, WHITE);
		DrawText("NO", (int)(noRect.x + 35), (int)(noRect.y + 10), 18, BLACK);
	}
}

bool MyTicketsScreen::isBackButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();
	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, backButton);
}

int MyTicketsScreen::getHoveredBookingIndex() const
{
	return hoveredBookingIndex;
}

bool MyTicketsScreen::isCancelBookingPressed(int bookingIndex) const
{
	if (bookingIndex < 0 || bookingIndex >= (int)bookings.size()) return false;
	Vector2 mousePos = GetMousePosition();
	int col = bookingIndex % 2;
	int row = bookingIndex / 2;
	float cardX = 60 + col * 420;
	float cardY = 120 + row * 180;
	Rectangle cancelRect = { cardX + 260, cardY + 110, 100, 30 };
	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, cancelRect);
}

int MyTicketsScreen::getBookingIdAt(int bookingIndex) const
{
	if (bookingIndex < 0 || bookingIndex >= (int)bookings.size()) return -1;
	return bookings[bookingIndex].getId();
}

int MyTicketsScreen::getPendingCancelBookingIndex() const
{
	return pendingCancelIndex;
}

bool MyTicketsScreen::isConfirmYesPressed()
{
	if (confirmYesFlag)
	{
		confirmYesFlag = false;
		return true;
	}
	return false;
}

bool MyTicketsScreen::isConfirmNoPressed()
{
	if (confirmNoFlag)
	{
		confirmNoFlag = false;
		return true;
	}
	return false;
}

void MyTicketsScreen::clearPendingCancel()
{
	pendingCancelIndex = -1;
	showConfirm = false;
	confirmYesFlag = false;
	confirmNoFlag = false;
}
