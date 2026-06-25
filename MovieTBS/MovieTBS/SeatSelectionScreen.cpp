#include "SeatSelectionScreen.h"
#include <sstream>
#include <iomanip>

SeatSelectionScreen::SeatSelectionScreen()
{
	selectedMovie = nullptr;
	backButton = { 0, 0, 0, 0 };
	bookTicketsButton = { 0, 0, 0, 0 };
	initializeSeats();
}

void SeatSelectionScreen::setMovie(const Movie* movie)
{
	selectedMovie = movie;
}

void SeatSelectionScreen::initializeSeats()
{
	seats.clear();
	seatOccupancy.clear();

	// Create 8 columns (A-H) x 6 rows
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			char rowChar = 'A' + row;
			int colNum = col + 1;

			Seat seat(rowChar, colNum, SeatState::Available);
			seats.push_back(seat);

			seatOccupancy[seat.getSeatCode()] = false;
		}
	}
}

void SeatSelectionScreen::setSeatOccupancy(const std::map<std::string, bool>& occupancy)
{
	seatOccupancy = occupancy;

	// Update seat states based on occupancy
	for (auto& seat : seats)
	{
		std::string code = seat.getSeatCode();
		if (seatOccupancy[code])
		{
			seat.setState(SeatState::Occupied);
		}
	}
}

void SeatSelectionScreen::update()
{
	Vector2 mousePos = GetMousePosition();

	// Check for seat clicks
	for (auto& seat : seats)
	{
		if (seat.getState() == SeatState::Occupied)
			continue;

		int row = seat.getRow() - 'A';
		int col = seat.getColumn() - 1;

		float seatX = GRID_START_X + col * (SEAT_SIZE + SEAT_SPACING);
		float seatY = GRID_START_Y + row * (SEAT_SIZE + SEAT_SPACING);

		Rectangle seatRect = { seatX, seatY, SEAT_SIZE, SEAT_SIZE };

		if (CheckCollisionPointRec(mousePos, seatRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (seat.getState() == SeatState::Available)
			{
				seat.setState(SeatState::Selected);
			}
			else if (seat.getState() == SeatState::Selected)
			{
				seat.setState(SeatState::Available);
			}
		}
	}
}

void SeatSelectionScreen::draw(int width, int height, const std::string& username)
{
	if (selectedMovie == nullptr)
	{
		DrawText("No movie selected", width / 2 - 100, height / 2, 20, RED);
		return;
	}

	// Draw header
	DrawText(
		"SELECT SEATS",
		60,
		20,
		32,
		BLACK
	);

	std::string userText = "User: " + username;
	int userTextWidth = MeasureText(userText.c_str(), 18);

	DrawText(
		userText.c_str(),
		width - userTextWidth - 140,
		25,
		18,
		DARKBLUE
	);

	// Back button
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

	DrawText(
		"< BACK",
		width - 115,
		31,
		18,
		WHITE
	);

	// Draw movie title
	std::string movieTitle = "Movie: " + selectedMovie->getTitle();
	DrawText(
		movieTitle.c_str(),
		60,
		70,
		16,
		DARKGRAY
	);

	// Draw screen representation at top
	DrawText(
		"SCREEN",
		(int)(GRID_START_X + COLUMNS * (SEAT_SIZE + SEAT_SPACING) / 2 - 30),
		(int)(GRID_START_Y - 40),
		18,
		DARKGRAY
	);

	// Draw screen line
	DrawLine(
		(int)GRID_START_X,
		(int)(GRID_START_Y - 20),
		(int)(GRID_START_X + COLUMNS * (SEAT_SIZE + SEAT_SPACING)),
		(int)(GRID_START_Y - 20),
		DARKGRAY
	);

	// Draw row labels (A, B, C, etc.)
	for (int row = 0; row < ROWS; row++)
	{
		char rowChar = 'A' + row;
		std::string rowLabel(1, rowChar);
		DrawText(
			rowLabel.c_str(),
			(int)(GRID_START_X - 30),
			(int)(GRID_START_Y + row * (SEAT_SIZE + SEAT_SPACING) + 5),
			14,
			BLACK
		);
	}

	// Draw column labels (1, 2, 3, etc.)
	for (int col = 0; col < COLUMNS; col++)
	{
		std::string colLabel = std::to_string(col + 1);
		DrawText(
			colLabel.c_str(),
			(int)(GRID_START_X + col * (SEAT_SIZE + SEAT_SPACING) + 10),
			(int)(GRID_START_Y - 20),
			12,
			BLACK
		);
	}

	// Draw seats
	for (const auto& seat : seats)
	{
		int row = seat.getRow() - 'A';
		int col = seat.getColumn() - 1;

		float seatX = GRID_START_X + col * (SEAT_SIZE + SEAT_SPACING);
		float seatY = GRID_START_Y + row * (SEAT_SIZE + SEAT_SPACING);

		Rectangle seatRect = { seatX, seatY, SEAT_SIZE, SEAT_SIZE };

		Color seatColor;
		switch (seat.getState())
		{
		case SeatState::Available:
			seatColor = GREEN;
			break;
		case SeatState::Selected:
			seatColor = YELLOW;
			break;
		case SeatState::Occupied:
			seatColor = RED;
			break;
		}

		DrawRectangleRec(seatRect, seatColor);
		DrawRectangleLinesEx(seatRect, 1, DARKGRAY);
	}

	// Draw legend
	float legendX = 600.0f;
	float legendY = 100.0f;

	DrawText("LEGEND:", (int)legendX, (int)legendY, 16, BLACK);

	// Available
	DrawRectangle((int)legendX, (int)(legendY + 30), 20, 20, GREEN);
	DrawText("Available", (int)(legendX + 30), (int)(legendY + 30), 14, DARKGRAY);

	// Selected
	DrawRectangle((int)legendX, (int)(legendY + 60), 20, 20, YELLOW);
	DrawText("Selected", (int)(legendX + 30), (int)(legendY + 60), 14, DARKGRAY);

	// Occupied
	DrawRectangle((int)legendX, (int)(legendY + 90), 20, 20, RED);
	DrawText("Occupied", (int)(legendX + 30), (int)(legendY + 90), 14, DARKGRAY);

	// Display selected seats and total price
	std::vector<std::string> selectedSeats = getSelectedSeats();

	float infoX = 600.0f;
	float infoY = 250.0f;

	DrawText("SELECTED SEATS:", (int)infoX, (int)infoY, 16, BLACK);

	std::string seatsDisplay = "";
	for (size_t i = 0; i < selectedSeats.size(); i++)
	{
		seatsDisplay += selectedSeats[i];
		if (i < selectedSeats.size() - 1)
			seatsDisplay += ", ";
	}

	if (seatsDisplay.empty())
		seatsDisplay = "None";

	DrawText(
		seatsDisplay.c_str(),
		(int)infoX,
		(int)(infoY + 30),
		14,
		DARKBLUE
	);

	// Total price
	double totalPrice = getTotalPrice();
	std::ostringstream priceStream;
	priceStream << std::fixed << std::setprecision(2) << totalPrice;
	std::string priceText = "Total: $" + priceStream.str();

	DrawText(
		priceText.c_str(),
		(int)infoX,
		(int)(infoY + 60),
		16,
		DARKGREEN
	);

	// Book Tickets button
	bookTicketsButton = { 600.0f, (float)(height - 100), 200.0f, 50.0f };

	bool canBook = !selectedSeats.empty();

	if (canBook && CheckCollisionPointRec(mousePos, bookTicketsButton))
	{
		DrawRectangleRec(bookTicketsButton, DARKGREEN);
	}
	else if (canBook)
	{
		DrawRectangleRec(bookTicketsButton, GREEN);
	}
	else
	{
		DrawRectangleRec(bookTicketsButton, LIGHTGRAY);
	}

	DrawRectangleLinesEx(bookTicketsButton, 2, DARKGRAY);

	std::string buttonText = canBook ? "BOOK TICKETS" : "SELECT SEATS";
	int buttonTextWidth = MeasureText(buttonText.c_str(), 14);
	DrawText(
		buttonText.c_str(),
		(int)(bookTicketsButton.x + (bookTicketsButton.width - buttonTextWidth) / 2),
		(int)(bookTicketsButton.y + 15),
		14,
		canBook ? WHITE : DARKGRAY
	);
}

bool SeatSelectionScreen::isBackButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, backButton);
}

bool SeatSelectionScreen::isBookTicketsButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();
	std::vector<std::string> selectedSeats = getSelectedSeats();

	return !selectedSeats.empty() &&
		   IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, bookTicketsButton);
}

std::vector<std::string> SeatSelectionScreen::getSelectedSeats() const
{
	std::vector<std::string> selected;

	for (const auto& seat : seats)
	{
		if (seat.getState() == SeatState::Selected)
		{
			selected.push_back(seat.getSeatCode());
		}
	}

	return selected;
}

double SeatSelectionScreen::getTotalPrice() const
{
	return getSelectedSeats().size() * TICKET_PRICE;
}

void SeatSelectionScreen::markSeatsAsOccupied(const std::vector<std::string>& seatCodes)
{
	for (const auto& code : seatCodes)
	{
		seatOccupancy[code] = true;

		// Update seat state
		for (auto& seat : seats)
		{
			if (seat.getSeatCode() == code)
			{
				seat.setState(SeatState::Occupied);
			}
		}
	}
}

std::map<std::string, bool> SeatSelectionScreen::getSeatOccupancy() const
{
	return seatOccupancy;
}

const Movie* SeatSelectionScreen::getSelectedMovie() const
{
	return selectedMovie;
}
