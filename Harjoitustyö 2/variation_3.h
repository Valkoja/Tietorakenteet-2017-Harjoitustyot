#pragma once

class Variation_3 : public Variation_0
{
    public:
        Variation_3();
        void runSimulation();
        void processArrival(Runway &activeRunway, Extended_queue &activeQueue, Extended_queue &helperQueue);

    private:
        Runway runway1;
        Runway runway2;
        Extended_queue helperQueue;
};
