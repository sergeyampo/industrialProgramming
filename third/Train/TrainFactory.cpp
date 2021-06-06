#include "TrainFactory.h"

Vehicle* TrainFactory::createVehicle()
{
    return new Train();
}

Vehicle* TrainFactory::createVehicle(std::tuple<int, int, double> params, int dist)
{
    return new Train(params, dist);
}
