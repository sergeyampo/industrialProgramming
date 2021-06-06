#include "Track.h"

Track::Track()
{
	this->cost = 0;
	this->time = 0;
	this->volume = 0;
}

Track::Track(std::vector<Vehicle*> vehicles, int volume)
{
	cost = 0;
	time = 0;
	this->volume = volume;
	for (int i = 0; i < vehicles.size(); i++)
	{
		cost += vehicles.at(i)->sumCost(volume, vehicles.at(i)->getDistance());
		time += vehicles.at(i)->sumTime(vehicles.at(i)->getDistance());
	}
}

double Track::getCost()
{
	return this->cost;
}
