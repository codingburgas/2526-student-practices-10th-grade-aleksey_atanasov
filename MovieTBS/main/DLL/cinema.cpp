#include "cinema.h"
using namespace std;

Cinema::Cinema()
{
	id = 0;
	city = "";
	name = "";
}

Cinema::Cinema(int id, const string& city, const string& name)
{
	this->id = id;
	this->city = city;
	this->name = name;
}
int Cinema::getId() const
{
	return id;
}
string Cinema::getCity() const
{
	return city;
}
string Cinema::getName() const
{
	return name;
}