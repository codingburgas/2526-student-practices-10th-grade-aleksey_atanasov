#pragma once

#include <string>

class Movie
{
private:
	std::string title;
	std::string genre;
	int duration;  // in minutes
	double rating; // 1-10
	int posterColor; // Raylib color code

public:
	Movie();

	Movie(
		const std::string& title,
		const std::string& genre,
		int duration,
		double rating,
		int posterColor
	);

	std::string getTitle() const;
	std::string getGenre() const;
	int getDuration() const;
	double getRating() const;
	int getPosterColor() const;
};
