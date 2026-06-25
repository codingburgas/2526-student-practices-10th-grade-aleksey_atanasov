#include "MoviesScreen.h"

MoviesScreen::MoviesScreen()
{
	logoutButton = { 0, 0, 0, 0 };
	hoveredMovieIndex = -1;
	hoveredButtonIndex = -1;
}

void MoviesScreen::setMovies(const std::vector<Movie>& movieList)
{
	movies = movieList;
}

void MoviesScreen::update()
{
	Vector2 mousePos = GetMousePosition();
	hoveredMovieIndex = -1;
	hoveredButtonIndex = -1;

	// Check which movie card is hovered
	for (int i = 0; i < (int)movies.size(); i++)
	{
		int col = i % 3;
		int row = i / 3;

		Rectangle cardRect = {
			(float)(60 + col * 280),
			(float)(120 + row * 250),
			260,
			220
		};

		if (CheckCollisionPointRec(mousePos, cardRect))
		{
			hoveredMovieIndex = i;
		}
	}
}

void MoviesScreen::draw(int width, int height, const std::string& username)
{
	// Draw title
	DrawText(
		"BROWSE MOVIES",
		60,
		20,
		32,
		BLACK
	);

	// Draw user info and logout button
	std::string userText = "User: " + username;
	int userTextWidth = MeasureText(userText.c_str(), 18);

	DrawText(
		userText.c_str(),
		width - userTextWidth - 140,
		25,
		18,
		DARKBLUE
	);

	// Logout button
	logoutButton = { (float)(width - 130), 20, 120, 40 };

	Vector2 mousePos = GetMousePosition();

	if (CheckCollisionPointRec(mousePos, logoutButton))
	{
		DrawRectangleRec(logoutButton, RED);
	}
	else
	{
		DrawRectangleRec(logoutButton, MAROON);
	}

	DrawText(
		"LOGOUT",
		width - 120,
		31,
		18,
		WHITE
	);

	// Draw movie cards
	for (int i = 0; i < (int)movies.size(); i++)
	{
		int col = i % 3;
		int row = i / 3;

		float cardX = 60 + col * 280;
		float cardY = 120 + row * 250;

		Rectangle cardRect = { cardX, cardY, 260, 220 };

		// Draw card background
		if (hoveredMovieIndex == i)
		{
			DrawRectangleRec(cardRect, LIGHTGRAY);
			DrawRectangleLinesEx(cardRect, 3, DARKBLUE);
		}
		else
		{
			DrawRectangleRec(cardRect, WHITE);
			DrawRectangleLinesEx(cardRect, 1, GRAY);
		}

		// Draw poster placeholder
		Rectangle posterRect = { cardX + 10, cardY + 10, 240, 120 };

		// Get color based on posterColor code
		Color posterColor = WHITE;
		switch (movies[i].getPosterColor())
		{
			case 0: posterColor = PURPLE; break;
			case 1: posterColor = BLUE; break;
			case 2: posterColor = DARKBLUE; break;
			case 3: posterColor = SKYBLUE; break;
			case 4: posterColor = VIOLET; break;
			default: posterColor = GRAY; break;
		}

		DrawRectangleRec(posterRect, posterColor);
		DrawText("Poster", (int)(cardX + 100), (int)(cardY + 50), 16, WHITE);

		// Draw movie info
		DrawText(
			movies[i].getTitle().c_str(),
			(int)(cardX + 10),
			(int)(cardY + 140),
			14,
			BLACK
		);

		// Genre
		std::string genreText = "Genre: " + movies[i].getGenre();
		DrawText(
			genreText.c_str(),
			(int)(cardX + 10),
			(int)(cardY + 160),
			12,
			DARKGRAY
		);

		// Duration and Rating
		std::string durationText = std::to_string(movies[i].getDuration()) + " min";
		DrawText(
			durationText.c_str(),
			(int)(cardX + 10),
			(int)(cardY + 178),
			12,
			DARKGRAY
		);

		std::string ratingText = "Rating: " + std::to_string(movies[i].getRating()).substr(0, 3);
		DrawText(
			ratingText.c_str(),
			(int)(cardX + 130),
			(int)(cardY + 178),
			12,
			DARKGRAY
		);

		// View Details button
		Rectangle detailsButton = { cardX + 10, cardY + 195, 240, 25 };

		if (hoveredMovieIndex == i && CheckCollisionPointRec(mousePos, detailsButton))
		{
			DrawRectangleRec(detailsButton, DARKBLUE);
			hoveredButtonIndex = i;
		}
		else if (hoveredMovieIndex == i)
		{
			DrawRectangleRec(detailsButton, BLUE);
		}
		else
		{
			DrawRectangleRec(detailsButton, SKYBLUE);
		}

		DrawText(
			"View Details",
			(int)(cardX + 75),
			(int)(cardY + 200),
			12,
			WHITE
		);
	}
}

bool MoviesScreen::isLogoutButtonPressed() const
{
	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, logoutButton);
}

bool MoviesScreen::isViewDetailsPressed(int movieIndex) const
{
	if (movieIndex < 0 || movieIndex >= (int)movies.size())
	{
		return false;
	}

	int col = movieIndex % 3;
	int row = movieIndex / 3;

	float cardX = 60 + col * 280;
	float cardY = 120 + row * 250;

	Rectangle detailsButton = { cardX + 10, cardY + 195, 240, 25 };

	Vector2 mousePos = GetMousePosition();

	return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
		   CheckCollisionPointRec(mousePos, detailsButton);
}

int MoviesScreen::getHoveredMovieIndex() const
{
	return hoveredMovieIndex;
}
