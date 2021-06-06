#include "CarFactory.h"

Vehicle* CarFactory::createVehicle()
{
    return new Car();
}

Vehicle* CarFactory::createVehicle(std::tuple<int, int, double> params, int dist)
{
    return new Car(params, dist);
}
