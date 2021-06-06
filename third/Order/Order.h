#pragma once
#include <string>
#include "../Track/Track.h"
#include "../Data.h"
#include "../Car/Car.h"
#include "../Train/Train.h"
#include "../Plane/Plane.h"
#include "../Car/CarFactory.h"
#include "../Plane/PlaneFactory.h"
#include "../Train/TrainFactory.h"

enum Type { Turbo, Standart, Economy };

class Order
{
	double cost;
	int volume;
	std::string startPoint;
	std::string finishPoint;
	enum::Type type;
	Track track;
	
	CarFactory carFactory;
	PlaneFactory planeFactory;
	TrainFactory trainFactory;
	
public:
	Order();
	Order(Type, std::string, std::string, int);
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);
};
