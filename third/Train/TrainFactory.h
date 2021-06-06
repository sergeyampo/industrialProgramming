#pragma once
#include "../Vehicle/VehicleFactory.h"
#include "Train.h"

class TrainFactory : public VehicleFactory
{
public:
	Vehicle* createVehicle() override;
	Vehicle* createVehicle(std::tuple<int, int, double>, int dist) override;
};
