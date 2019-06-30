#include "main.h"

Variation_2::Variation_2() : Variation_0()
{
    // Parentin rakentaja
}

void Variation_2::runSimulation()
{
    arrivalPoisson = std::poisson_distribution<int>(arrivalRate);
    departurePoisson = std::poisson_distribution<int>(departureRate);

    std::cout << std::endl;
    std::cout << "Simulation has started" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl;

    while (currentTime < timeLimit)
    {
        runway1.setStatus(Runway_activity::idle);
        runway2.setStatus(Runway_activity::idle);

        std::cout << "Time unit " << currentTime + 1 << ":" << std::endl;

        // Laskutumisjono
        processQueue(runway1, landingQueue, Runway_activity::landing);

        // Uudet saapujat
        int arrivals = arrivalPoisson(generator);

        for (int i = 0; i < arrivals; i++)
        {
            processArrival(runway1, landingQueue);

            flightNumber++;
            landingsRequested++;
        }

        // Nousujono
        processQueue(runway2, takeoffQueue, Runway_activity::takeoff);

        // Uudet lähtijät
        int departures = departurePoisson(generator);

        for (int i = 0; i < departures; i++)
        {
            processDeparture(runway2, takeoffQueue);

            flightNumber++;
            takeoffsRequested++;
        }

        // Kentällä tyhjää
        if (runway1.getStatus() == Runway_activity::idle && runway2.getStatus() == Runway_activity::idle)
        {
            idleTime++;
            std::cout << "Airport is idle" << std::endl;
        }

        currentTime++;
        std::cout << std::endl;
    }

    printStatistics();
}
