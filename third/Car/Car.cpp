#include "Car.h"

Car::Car() : Vehicle(std::make_tuple(100, 60, 50.0), 0) {}

Car::Car(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, dist) {}
