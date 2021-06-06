#include "PlaneFactory.h"

Vehicle* PlaneFactory::createVehicle()
{
    return new Plane();
}

Vehicle* PlaneFactory::createVehicle(std::tuple<int, int, double> params, int dist)
{
    return new Plane(params, dist);
}
