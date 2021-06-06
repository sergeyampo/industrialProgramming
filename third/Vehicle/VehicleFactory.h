#pragma once
#include "Vehicle.h"

//Used Factory Method

class VehicleFactory
{
public:
	virtual Vehicle* createVehicle() = 0;
	virtual Vehicle* createVehicle(std::tuple<int, int, double>, int dist) = 0;
};

