#include "Vehicle.h"

double Vehicle::sumCost(int mass, int dist)
{
	return (mass / volume) * sumTime(dist) * price;
}

double Vehicle::sumTime(int dist)
{
	return dist / speed;
}

int Vehicle::getDistance()
{
	return this->distance;
}

Vehicle::Vehicle(std::tuple<int, int, double> tuple, int dist)
{
	this->price = std::get<0>(tuple);
	this->speed = std::get<1>(tuple);
	this->volume = std::get<2>(tuple);
	this->distance = dist;
}
