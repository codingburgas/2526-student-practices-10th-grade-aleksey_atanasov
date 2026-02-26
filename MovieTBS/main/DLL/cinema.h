#pragma once
#include <string>

class Cinema
{
private:
	int id;
	string city;
	string name;

public:
	Cinema();

	Cinema(int id, const string& city, const string& name)

		int getId() const;
	string getCity() const;
	string getName() const;
};