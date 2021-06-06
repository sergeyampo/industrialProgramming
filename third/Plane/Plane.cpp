#include "Plane.h"

Plane::Plane() : Vehicle(std::make_tuple(200, 100, 500.0), 0) {}

Plane::Plane(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, 0) {}
