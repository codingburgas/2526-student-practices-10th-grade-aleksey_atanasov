#pragma once
#include <string>

class Cinema
{
private:
	int id;
	std::string name;
	std::string city;

public:
	Cinema();
	Cinema(int id, const std::string& name, const std::string& city);

	int getId() const;
	std::string getName() const;
	std::string getCity() const;
};