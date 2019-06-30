#pragma once

class Plane
{
    public:
        Plane();
        Plane(int number, int created);
        Plane(int number, int created, int fuel);
        int getCreationTime();
        int getFlightNumber();
        int getFuelAmount();

    private:
        int flightNumber;
        int creationTime;
        int fuelAmount;
};
