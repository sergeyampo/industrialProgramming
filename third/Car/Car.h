#pragma once
#include "../Vehicle/Vehicle.h"

class Car : public Vehicle
{
public:
	Car();
	Car(std::tuple<int, int, double>, int);
};

