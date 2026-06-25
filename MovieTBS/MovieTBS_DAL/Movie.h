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
	std::string description;
	int releaseYear;

public:
	Movie();

	Movie(
		const std::string& title,
		const std::string& genre,
		int duration,
		double rating,
		int posterColor,
		const std::string& description,
		int releaseYear
	);

	std::string getTitle() const;
	std::string getGenre() const;
	int getDuration() const;
	double getRating() const;
	int getPosterColor() const;
	std::string getDescription() const;
	int getReleaseYear() const;
};
