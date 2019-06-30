#include "main.h"

Plane::Plane()
{
    flightNumber = -1;
    creationTime = -1;
    fuelAmount = -1;
}

Plane::Plane(int number, int created)
{
    flightNumber = number;
    creationTime = created;
    fuelAmount = -1;
}

Plane::Plane(int number, int created, int fuel)
{
    flightNumber = number;
    creationTime = created;
    fuelAmount = fuel;
}

int Plane::getCreationTime()
{
    return creationTime;
}

int Plane::getFlightNumber()
{
    return flightNumber;
}

int Plane::getFuelAmount()
{
    return fuelAmount;
}
