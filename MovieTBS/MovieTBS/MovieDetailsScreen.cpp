#include "MovieDetailsScreen.h"

MovieDetailsScreen::MovieDetailsScreen()
{
	selectedMovie = nullptr;
	backButton = { 0, 0, 0, 0 };
	chooseSeatsButton = { 0, 0, 0, 0 };
}

void MovieDetailsScreen::setMovie(const Movie* movie)
{
	selectedMovie = movie;
}

void MovieDetailsScreen::update()
{
	// Update button positions, calculations done in draw for simplicity
}

void MovieDetailsScreen::draw(int width, int height, const std::string& username)
{
	if (selectedMovie == nullptr)
	{
		DrawText("No movie selected", width / 2 - 100, height / 2, 20, RED);
		return;
	}

	// Draw header with user info and back button
	DrawText(
		"MOVIE DETAILS",
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

	// Main content area
	// Poster on the left
	float posterX = 60;
	float posterY = 80;
	float posterWidth = 220;
	float posterHeight = 300;

	// Get color based on posterColor code
	Color posterColor = WHITE;
	switch (selectedMovie->getPosterColor())
	{
	case 0: posterColor = PURPLE; break;
	case 1: posterColor = BLUE; break;
	case 2: posterColor = DARKBLUE; break;
	case 3: posterColor = SKYBLUE; break;
	case 4: posterColor = VIOLET; break;
	default: posterColor = GRAY; break;
	}

	DrawRectangleRec({ posterX, posterY, posterWidth, posterHeight }, posterColor);
	DrawRectangleLinesEx({ posterX, posterY, posterWidth, posterHeight }, 2, DARKGRAY);
	DrawText("Poster", (int)(posterX + 75), (int)(posterY + 140), 16, WHITE);

	// Movie info on the right
	float infoX = posterX + posterWidth + 40;
	float infoY = 80;

	// Title
	DrawText(
		selectedMovie->getTitle().c_str(),
		(int)infoX,
		(int)infoY,
		28,
		BLACK
	);

	// Divider line
	DrawLineEx(
		{ infoX, infoY + 40 },
		{ (float)width - 60, infoY + 40 },
		2,
		LIGHTGRAY
	);

	float currentY = infoY + 60;

	// Release Year
	std::string yearText = "Release Year: " + std::to_string(selectedMovie->getReleaseYear());
	DrawText(
		yearText.c_str(),
		(int)infoX,
		(int)currentY,
		16,
		DARKGRAY
	);
	currentY += 30;

	// Genre
	std::string genreText = "Genre: " + selectedMovie->getGenre();
	DrawText(
		genreText.c_str(),
		(int)infoX,
		(int)currentY,
		16,
		DARKGRAY
	);
	currentY += 30;

	// Duration
	std::string durationText = "Duration: " + std::to_string(selectedMovie->getDuration()) + " minutes";
	DrawText(
		durationText.c_str(),
		(int)infoX,
		(int)currentY,
		16,
		DARKGRAY
	);
	currentY += 30;

	// Rating
	std::string ratingStr = std::to_string(selectedMovie->getRating());
	// Truncate to 1 decimal place
	size_t dotPos = ratingStr.find('.');
	if (dotPos != std::string::npos && dotPos + 2 < ratingStr.length())
	{
		ratingStr = ratingStr.substr(0, dotPos + 2);
	}
	std::string ratingText = "Rating: " + ratingStr + "/10";
	DrawText(
		ratingText.c_str(),
		(int)infoX,
		(int)currentY,
		16,
		DARKGRAY
	);
	currentY += 40;

	// Description section
	DrawText(
		"Description:",
		(int)infoX,
		(int)currentY,
		18,
		BLACK
	);
	currentY += 30;

	// Draw description text with word wrapping
	std::string description = selectedMovie->getDescription();
	const int maxCharsPerLine = 70;
	int charCount = 0;

	for (size_t i = 0; i < description.length(); i++)
	{
		charCount++;
		if (charCount >= maxCharsPerLine || description[i] == '\n')
		{
			std::string line = description.substr(i - charCount + 1, charCount - 1);
			if (description[i] == '\n')
			{
				line = description.substr(i - charCount + 1, charCount - 2);
			}

			DrawText(
				line.c_str(),
				(int)infoX,
				(int)currentY,
				14,
				DARKGRAY
			);
			currentY += 24;
			charCount = 0;
		}
	}

	// Draw remaining text
	if (charCount > 0)
	{
		std::string line = description.substr(description.length() - charCount, charCount);
		DrawText(
			line.c_str(),
			(int)infoX,
			(int)currentY,
			14,
			DARKGRAY
		);
	}

	// Choose Seats button (large, at the bottom)
	float buttonWidth = 300;
	float buttonHeight = 50;
	float chooseSeatsX = (width - buttonWidth) / 2;
	float chooseSeatsY = (float)height - 90;

	chooseSeatsButton = { chooseSeatsX, chooseSeatsY, buttonWidth, buttonHeight };

	if (CheckCollisionPointRec(mousePos, chooseSeatsButton))
	{
		DrawRectangleRec(chooseSeatsButton, DARKGREEN);
	}
	else
	{
		DrawRectangleRec(chooseSeatsButton, GREEN);
	}

	DrawRectangleLinesEx(chooseSeatsButton, 2, DARKGREEN);

	std::string chooseSeatsText = "CHOOSE SEATS";
	int chooseSeatsTextWidth = MeasureText(chooseSeatsText.c_str(), 20);
	DrawText(
		chooseSeatsText.c_str(),
		(int)(chooseSeatsX + (buttonWidth - chooseSeatsTextWidth) / 2),
		(int)(chooseSeatsY + 15),
		20,
		WHITE
	);
}

bool MovieDetailsScreen::isBackButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, backButton);
}

bool MovieDetailsScreen::isChooseSeatsButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, chooseSeatsButton);
}

const Movie* MovieDetailsScreen::getSelectedMovie() const
{
	return selectedMovie;
}
