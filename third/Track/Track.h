#pragma once
#include <vector>
#include "../Vehicle/Vehicle.h"

class Track
{
	double cost;
	double time;
	int volume;
public:
	Track();
	Track(std::vector<Vehicle*>, int volume);
	double getCost();
};
