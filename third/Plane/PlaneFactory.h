#pragma once
#include "../Vehicle/VehicleFactory.h"
#include "Plane.h"

class PlaneFactory : public VehicleFactory
{
public:
	Vehicle* createVehicle() override;
	Vehicle* createVehicle(std::tuple<int, int, double>, int dist) override;
};

