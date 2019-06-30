#include "main.h"

Variation_3::Variation_3() : Variation_0()
{
    // Parentin rakentaja
}

void Variation_3::runSimulation()
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
            processArrival(runway1, landingQueue, helperQueue);

            flightNumber++;
            landingsRequested++;
        }

        // Apujono
        processQueue(runway2, helperQueue, Runway_activity::landing);

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

        // Jonot ristiin, jos jommassa kummassa on vielä tilaa
        processQueue(runway2, landingQueue, Runway_activity::landing);
        processQueue(runway1, takeoffQueue, Runway_activity::takeoff);

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

void Variation_3::processArrival(Runway &activeRunway, Extended_queue &activeQueue, Extended_queue &helperQueue)
{
    Plane arrivingPlane(flightNumber, currentTime);

    if (activeRunway.getStatus() == Runway_activity::idle)
    {
        landingsGranted++;
        activeRunway.setStatus(Runway_activity::landing);
        std::cout << "Plane number " << flightNumber << " landed immediately." << std::endl;
    }
    else if (activeQueue.size() < queueLimit)
    {
        landingsQueued++;
        activeQueue.append(arrivingPlane);
        std::cout << "Plane number " << flightNumber << " ready to land." << std::endl;
    }
    else if (helperQueue.size() < queueLimit)
    {
        landingsQueued++;
        helperQueue.append(arrivingPlane);
        std::cout << "Plane number " << flightNumber << " ready to land." << std::endl;
    }
    else
    {
        landingsRefused++;
        std::cout << "Plane number " << flightNumber << " directed to another airport." << std::endl;
    }
}
