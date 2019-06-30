#pragma once

class Variation_5 : public Variation_0
{
    public:
        Variation_5();
        void runSimulation();
        void printStatistics();
        void processArrival(Runway &activeRunway, Extended_queue &activeQueue);
        void processQueue(Runway &activeRunway, Extended_queue &activeQueue, Runway_activity activity);

    private:
        int planesCrashed;
        int fuelToNextAirport;
        Runway runway1;
        std::uniform_int_distribution<int> fuelDistribution;
};
