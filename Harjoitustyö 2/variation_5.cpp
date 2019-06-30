#include "main.h"

Variation_5::Variation_5() : Variation_0()
{
    // Parentin rakentaja

    // Statistiikat
    planesCrashed = 0;
}

void Variation_5::runSimulation()
{
    arrivalPoisson = std::poisson_distribution<int>(arrivalRate);
    departurePoisson = std::poisson_distribution<int>(departureRate);
    fuelDistribution = std::uniform_int_distribution<int>(1, (queueLimit * 2));
    fuelToNextAirport = queueLimit / 2;

    std::cout << std::endl;
    std::cout << "Simulation has started" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl;

    while (currentTime < timeLimit)
    {
        runway1.setStatus(Runway_activity::idle);

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
        processQueue(runway1, takeoffQueue, Runway_activity::takeoff);

        // Uudet lähtijät
        int departures = departurePoisson(generator);

        for (int i = 0; i < departures; i++)
        {
            processDeparture(runway1, takeoffQueue);

            flightNumber++;
            takeoffsRequested++;
        }

        // Kentällä tyhjää
        if (runway1.getStatus() == Runway_activity::idle)
        {
            idleTime++;
            std::cout << "Airport is idle" << std::endl;
        }

        currentTime++;
        std::cout << std::endl;
    }

    printStatistics();
}

void Variation_5::processArrival(Runway &activeRunway, Extended_queue &activeQueue)
{
    Plane arrivingPlane(flightNumber, currentTime, fuelDistribution(generator));

    if (arrivingPlane.getFuelAmount() == 1)
    {
        // Polttoaine vähissä, koitetaan laskeutua
        if (activeRunway.getStatus() == Runway_activity::idle)
        {
            landingsGranted++;
            activeRunway.setStatus(Runway_activity::landing);
            std::cout << "Plane number " << flightNumber << " landed immediately." << std::endl;
        }
        else
        {
            planesCrashed++;
            std::cout << "Plane number " << flightNumber << " crashed." << std::endl;
        }
    }
    else if (activeRunway.getStatus() == Runway_activity::idle)
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
    else
    {
        landingsRefused++;

        // Riittääkö polttoaine seuraavalle lentokentälle
        if (arrivingPlane.getFuelAmount() >= fuelToNextAirport)
        {
            std::cout << "Plane number " << flightNumber << " directed to another airport." << std::endl;
        }
        else
        {
            planesCrashed++;
            std::cout << "Plane number " << flightNumber << " directed to another airport but crashed on way." << std::endl;
        }
    }
}

void Variation_5::processQueue(Runway &activeRunway, Extended_queue &activeQueue, Runway_activity activity)
{
    if (activeRunway.getStatus() == Runway_activity::idle && !activeQueue.empty())
    {
        // Kone jonosta
        Plane activePlane;
        activeQueue.serve_and_retrieve(activePlane);

        if (activity == Runway_activity::landing)
        {
            int waited = currentTime - activePlane.getCreationTime();

            if (activePlane.getFuelAmount() <= waited)
            {
                // Statistiikkaa
                landingWait += waited;
                planesCrashed++;

                std::cout << "Plane number " << activePlane.getFlightNumber() << " crashed after " << waited << " time unit" << (waited == 1 ? "" : "s") << " in the landing queue." << std::endl;
            }
            else
            {
                // Statistiikkaa
                landingWait += waited;
                landingsGranted++;

                // Kiitoradan tila ja tulostus
                activeRunway.setStatus(Runway_activity::landing);
                std::cout << "Plane number " << activePlane.getFlightNumber() << " landed after " << waited << " time unit" << (waited == 1 ? "" : "s") << " in the landing queue." << std::endl;
            }
        }
        else
        {
            // Statistiikkaa
            int waited = currentTime - activePlane.getCreationTime();
            takeoffWait += waited;
            takeoffsGranted++;

            // Kiitoradan tila ja tulostus
            activeRunway.setStatus(Runway_activity::takeoff);
            std::cout << "Plane number " << activePlane.getFlightNumber() << " took off after " << waited << " time unit" << (waited == 1 ? "" : "s") << " in the takeoff queue." << std::endl;
        }
    }
}

void Variation_5::printStatistics()
{
        std::cout << "Simulation has concluded after " << timeLimit << " time units." << std::endl;
        std::cout << "Total number of planes processed:                    " << (landingsRequested + takeoffsRequested) << std::endl;
        std::cout << "Total number of planes asking to land:               " << landingsRequested << std::endl;
        std::cout << "Total number of planes asking to take off:           " << takeoffsRequested << std::endl;
        std::cout << "Total number of planes accepted for landing:         " << landingsRequested - landingsRefused << std::endl;
        std::cout << "Total number of planes accepted for takeoff:         " << takeoffsRequested - takeoffsRefused<< std::endl;
        std::cout << "Total number of planes refused for landing:          " << landingsRefused << std::endl;
        std::cout << "Total number of planes refused for takeoff:          " << takeoffsRefused << std::endl;
        std::cout << "Total number of planes that landed:                  " << landingsGranted << std::endl;
        std::cout << "Total number of planes that took off:                " << takeoffsGranted << std::endl;
        std::cout << "Total number of planes that crashed:                 " << planesCrashed << std::endl;
        std::cout << "Total number of planes left in landing queue:        " << landingQueue.size() << std::endl;
        std::cout << "Total number of planes left in takeoff queue:        " << takeoffQueue.size() << std::endl;
        std::cout << "Percentage of time airport idle:                      " << 100.0 * (( float ) idleTime) / (( float ) timeLimit) << "%" << std::endl;
        std::cout << "Average wait in landing queue:                       " << (( float ) landingWait) / (( float ) landingsGranted) << " time units" << std::endl;
        std::cout << "Average wait in takeoff queue:                       " << (( float ) takeoffWait) / (( float ) takeoffsGranted) << " time units" << std::endl;
        std::cout << "Average observed rate of planes wanting to land:     " << (( float ) landingsRequested) / (( float ) timeLimit) << " per time units" << std::endl;
        std::cout << "Average observed rate of planes wanting to take off: " << (( float ) takeoffsRequested) / (( float ) timeLimit) << " per time units" << std::endl;
}
