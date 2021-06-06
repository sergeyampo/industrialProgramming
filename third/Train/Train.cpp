#include "Train.h"

Train::Train() : Vehicle(std::make_tuple(200, 100, 500.0), 0) {}

Train::Train(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, dist) {}
