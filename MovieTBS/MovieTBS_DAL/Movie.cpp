#include "Movie.h"

Movie::Movie()
{
	title = "";
	genre = "";
	duration = 0;
	rating = 0.0;
	posterColor = 0;
	description = "";
	releaseYear = 0;
}

Movie::Movie(
	const std::string& title,
	const std::string& genre,
	int duration,
	double rating,
	int posterColor,
	const std::string& description,
	int releaseYear
)
{
	this->title = title;
	this->genre = genre;
	this->duration = duration;
	this->rating = rating;
	this->posterColor = posterColor;
	this->description = description;
	this->releaseYear = releaseYear;
}

std::string Movie::getTitle() const
{
	return title;
}

std::string Movie::getGenre() const
{
	return genre;
}

int Movie::getDuration() const
{
	return duration;
}

double Movie::getRating() const
{
	return rating;
}

int Movie::getPosterColor() const
{
	return posterColor;
}

std::string Movie::getDescription() const
{
	return description;
}

int Movie::getReleaseYear() const
{
	return releaseYear;
}
