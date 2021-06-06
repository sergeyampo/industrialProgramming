#pragma once
#include <tuple>

class Vehicle
{
protected:
	int speed;
	int volume;
	double price;
	int distance;
public:
	Vehicle(std::tuple<int, int, double>, int dist);
	double sumCost(int mass, int dist);
	double sumTime(int dist);
	int getDistance();
};


