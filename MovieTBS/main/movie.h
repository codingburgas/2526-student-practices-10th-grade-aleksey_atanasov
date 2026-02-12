#pragma once
#include <string>
using namespace std;

class Movie {
public:
	string title;
	string time;
	double price;

	Movie(string t, string tm, double p);
};