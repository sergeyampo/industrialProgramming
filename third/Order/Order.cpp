#include "Order.h"

Order::Order()
{
	this->cost = 0;
	this->volume = 0;
	this->startPoint = "";
	this->finishPoint = "";
	this->track = Track();
	this->type = Type::Economy;
}

Order::Order(Type deliv, std::string startP, std::string finishP, int vol)
{
	this->startPoint = startP;
	this->finishPoint = finishP;
	type = deliv;
	this->track = best(startP, finishP, deliv, vol);
	this->cost = track.getCost();
	this->volume = vol;
}

Track Order::best(std::string startP, std::string finishP, Type deliv, int volume)
{
	int start = decr(startP);
	int finish = decr(finishP);
	std::vector<Vehicle*> vehicles;
	int** mat = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
		mat[i] = new int[SIZE];
	mat = matrixUpd(deliv);
	int* path = new int[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		path[i] = -1;
	}
	path = optim(mat, start, finish);
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (path[i] != -1)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	switch (count)
	{
	case 1:
	{
		Vehicle* car1 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[0]]))
			{
				car1 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[0]][path[1]]);
			}
		}
		vehicles.push_back(car1);
		Track track = Track(vehicles, volume);
		return track;
	}
	case 3:
	{
		Vehicle* car1 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[0]]))
			{
				car1 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[0]][path[1]]);
			}
		}
		Vehicle* car2 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[2]]))
			{
				car2 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[2]][path[3]]);
			}
		}
		Vehicle* train1 = trainFactory.createVehicle();
		Vehicle* plane1 = planeFactory.createVehicle();
		Track track = Track();

		vehicles.push_back(car1);
		vehicles.push_back(car2);
		vehicles.push_back(train1);
		vehicles.push_back(plane1);

		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[1]]) && Data::getInstance().points[path[1]].find("TS"))
			{
				train1 = trainFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 1], Data::getInstance().matrixDist[path[1]][path[2]]);
				track = Track(vehicles, volume);
			}

			if ((*it).first.find(Data::getInstance().points[path[1]]) && Data::getInstance().points[path[1]].find("AP"))
			{
				plane1 = planeFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3], Data::getInstance().matrixDist[path[1]][path[2]]);
				track = Track(vehicles, volume);
			}
		}

		return track;
	}
	case 5:
	{

		Vehicle* car1 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[0]]))
			{
				car1 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[0]][path[1]]);
			}
		}

		Vehicle* train1 = trainFactory.createVehicle();
		Vehicle* plane1 = planeFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[1]]) && Data::getInstance().points[path[1]].find("TS"))
			{
				train1 = trainFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 1], Data::getInstance().matrixDist[path[1]][path[2]]);
			}
			if ((*it).first.find(Data::getInstance().points[path[1]]) && Data::getInstance().points[path[1]].find("AP"))
			{
				plane1 = planeFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3], Data::getInstance().matrixDist[path[1]][path[2]]);
			}
		}

		Vehicle* car2 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[2]]))
			{
				car2 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[2]][path[3]]);
			}
		}

		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[3]]) && Data::getInstance().points[path[3]].find("AP"))
			{
				plane1 = planeFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3], Data::getInstance().matrixDist[path[3]][path[4]]);
			}
			if ((*it).first.find(Data::getInstance().points[path[3]]) && Data::getInstance().points[path[3]].find("TS"))
			{
				train1 = trainFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 1], Data::getInstance().matrixDist[path[3]][path[4]]);
			}
		}

		Vehicle* car3 = new  Car();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[4]]))
			{
				car3 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[4]][path[5]]);
			}
		}

		vehicles.push_back(car1);
		vehicles.push_back(car2);
		vehicles.push_back(car3);
		vehicles.push_back(train1);
		vehicles.push_back(plane1);

		Track track = Track(vehicles, volume);
		return track;
	}

	case 7:
	{
		Vehicle* car1 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[0]]))
			{
				car1 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[0]][path[1]]);
			}
		}

		Vehicle* train1 = trainFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[1]]))
			{
				train1 = trainFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 1], Data::getInstance().matrixDist[path[1]][path[2]]);
			}
		}

		Vehicle* car2 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[2]]))
			{
				car2 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[2]][path[3]]);
			}
		}

		Vehicle* plane1 = planeFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[3]]))
			{
				plane1 = planeFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3], Data::getInstance().matrixDist[path[3]][path[4]]);
			}
		}

		Vehicle* car3 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[4]]))
			{
				car3 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[4]][path[5]]);
			}
		}

		Vehicle* train2 = trainFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[5]]))
			{
				train2 = trainFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 1], Data::getInstance().matrixDist[path[5]][path[6]]);
			}
		}

		Vehicle* car4 = carFactory.createVehicle();
		for (auto it = Data::getInstance().table.begin(); it != Data::getInstance().table.end(); it++)
		{
			if ((*it).first.find(Data::getInstance().points[path[6]]))
			{
				car4 = carFactory.createVehicle(Data::getInstance().tableCost[(*it).second * 3 + 2], Data::getInstance().matrixDist[path[6]][path[7]]);
			}
		}

		vehicles.push_back(car1);
		vehicles.push_back(car2);
		vehicles.push_back(car3);
		vehicles.push_back(train1);
		vehicles.push_back(plane1);

		Track track = Track(vehicles, volume);

		return track;
	}
	}
}

int** Order::matrixUpd(Type type)
{
	int** matrix = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		matrix[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = Data::getInstance().matrixDist[i][j];
		}
	}
	switch (type)
	{
	case Economy:
		for (int i = 0; i < SIZE; i++)
		{
			if (Data::getInstance().points[i].find("TS"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Standart:
		for (int i = 0; i < SIZE; i++)
		{
			if (Data::getInstance().points[i].find("AP"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Turbo:
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
				if (matrix[i][j] == 0)
					matrix[i][j] = 99999;
		}
	}
	return matrix;
}

int* Order::optim(int** arr, int beginPoint, int endPoint)
{
	int* d = new int[SIZE];
	int* v = new int[SIZE];
	int temp, minindex, min;
	int begin_index = beginPoint;

	for (int i = 0; i < SIZE; i++)
	{
		d[i] = 99999;
		v[i] = 1;
	}
	d[begin_index] = 0;

	do {
		minindex = 99999;
		min = 99999;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 99999)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (arr[minindex][i] > 0)
				{
					temp = min + arr[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 99999);

	int* ver = new int[SIZE];
	int end = endPoint;
	ver[0] = end;
	int k = 1;
	int weight = d[end];

	while (end != begin_index)
	{
		for (int i = 0; i < SIZE; i++)
			if (arr[end][i] != 0)
			{
				int temp = weight - arr[end][i];
				if (temp == d[i])
				{
					weight = temp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
	}
	for (int i = 0; i < k / 2; i++)
		std::swap(ver[i], ver[k - 1 - i]);
	delete[] d, v;
	return ver;
}

int Order::decr(std::string str)
{
	for (auto it = Data::getInstance().towns.begin(); it != Data::getInstance().towns.end(); it++)
	{
		if (str._Equal((*it).first))
			return (*it).second;
	}
	return -1;
}

