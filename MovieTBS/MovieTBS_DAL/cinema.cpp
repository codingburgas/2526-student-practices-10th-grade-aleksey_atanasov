#include "cinema.h"

Cinema::Cinema()
{
	id = 0;
	name = "";
	city = "";
}

Cinema::Cinema(int id, const std::string& name, const std::string& city)
{
	this->id = id;
	this->name = name;
	this->city = city;
}

int Cinema::getId() const
{
	return id;
}
std::string Cinema::getName() const
{

	return name;
}
std::string Cinema::getCity() const
{
	return city;
}