#pragma once

class Variation_0
{
    public:
        Variation_0();
        void requestParams();
        void printStatistics();
        void processArrival(Runway &activeRunway, Extended_queue &activeQueue);
        void processDeparture(Runway &activeRunway, Extended_queue &activeQueue);
        void processQueue(Runway &activeRunway, Extended_queue &activeQueue, Runway_activity activity);

    protected:
        // simulation
        int currentTime = 0;
        int flightNumber = 0;

        // Asetukset
        int timeLimit;
        int queueLimit;
        double arrivalRate;
        double departureRate;

        // Jonot
        Extended_queue landingQueue;
        Extended_queue takeoffQueue;

        // Random
        std::default_random_engine generator;
        std::poisson_distribution<int> arrivalPoisson;
        std::poisson_distribution<int> departurePoisson;

        // Statistiikat
        int landingsRequested;
        int landingsGranted;
        int landingsQueued;
        int landingsRefused;

        int takeoffsRequested;
        int takeoffsGranted;
        int takeoffsQueued;
        int takeoffsRefused;

        int landingWait;
        int takeoffWait;
        int idleTime;
};
