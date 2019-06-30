#include "main.h"

Variation_0::Variation_0()
{
    // Asetukset
    timeLimit = 0;
    queueLimit = 0;
    arrivalRate = 0.0;
    departureRate = 0.0;

    // Random
    generator = std::default_random_engine(std::time(nullptr));

    // Statistiikat
    landingsRequested = 0;
    landingsGranted = 0;
    landingsQueued = 0;
    landingsRefused = 0;

    takeoffsRequested = 0;
    takeoffsGranted = 0;
    takeoffsQueued = 0;
    takeoffsRefused = 0;

    landingWait = 0;
    takeoffWait = 0;
    idleTime = 0;
}

void Variation_0::requestParams()
{
    std::string inputString;
    std::stringstream ss;

    std::cout << "Up to what number of planes can be waiting to land or take off at any time?" << std::endl;

    while (true)
    {
        std::getline(std::cin, inputString);

        ss.clear();
        ss.str(inputString);

        // Syöte ei ole kokonaisluku tai se on pienempi kuin 1
        if (!(ss >> queueLimit) || queueLimit < 1)
        {
            std::cout << std::endl;
            std::cout << "Invalid selection, please pick integer greater than 0" << std::endl;
        }
        else
        {
            break;
        }
    }

    std::cout << "How many units of time will the simulation run?" << std::endl;

    while (true)
    {
        std::getline(std::cin, inputString);

        ss.clear();
        ss.str(inputString);

        // Syöte ei ole kokonaisluku tai se on pienempi kuin 1
        if (!(ss >> timeLimit) || timeLimit < 1)
        {
            std::cout << std::endl;
            std::cout << "Invalid selection, please pick integer greater than 0" << std::endl;
        }
        else
        {
            break;
        }
    }

    std::cout << "Expected number of arrivals per time unit?" << std::endl;

    while (true)
    {
        std::getline(std::cin, inputString);

        ss.clear();
        ss.str(inputString);

        // Syöte ei ole realiluku tai se on pienempi kuin 0
        if (!(ss >> arrivalRate) || arrivalRate < 0)
        {
            std::cout << std::endl;
            std::cout << "Invalid selection, please pick positive real number" << std::endl;
        }
        else
        {
            break;
        }
    }

    std::cout << "Expected number of departures per time unit?" << std::endl;

    while (true)
    {
        std::getline(std::cin, inputString);

        ss.clear();
        ss.str(inputString);

        // Syöte ei ole realiluku tai se on pienempi kuin 0
        if (!(ss >> departureRate) || departureRate < 0)
        {
            std::cout << std::endl;
            std::cout << "Invalid selection, please pick positive real number" << std::endl;
        }
        else
        {
            break;
        }
    }
}

void Variation_0::processArrival(Runway &activeRunway, Extended_queue &activeQueue)
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
    else
    {
        landingsRefused++;
        std::cout << "Plane number " << flightNumber << " directed to another airport." << std::endl;
    }
}

void Variation_0::processDeparture(Runway &activeRunway, Extended_queue &activeQueue)
{
    Plane departingPlane(flightNumber, currentTime);

    if (activeRunway.getStatus() == Runway_activity::idle)
    {
        takeoffsGranted++;
        activeRunway.setStatus(Runway_activity::takeoff);
        std::cout << "Plane number " << flightNumber << " took off immediately." << std::endl;
    }
    else if (activeQueue.size() < queueLimit)
    {
        takeoffsQueued++;
        activeQueue.append(departingPlane);
        std::cout << "Plane number " << flightNumber << " ready to take off." << std::endl;
    }
    else
    {
        takeoffsRefused++;
        std::cout << "Plane number " << flightNumber << " told to try to takeoff again later." << std::endl;
    }
}

void Variation_0::processQueue(Runway &activeRunway, Extended_queue &activeQueue, Runway_activity activity)
{
    if (activeRunway.getStatus() == Runway_activity::idle && !activeQueue.empty())
    {
        // Kone jonosta
        Plane activePlane;
        activeQueue.serve_and_retrieve(activePlane);

        if (activity == Runway_activity::landing)
        {
            // Statistiikkaa
            int waited = currentTime - activePlane.getCreationTime();
            landingWait += waited;
            landingsGranted++;

            // Kiitoradan tila ja tulostus
            activeRunway.setStatus(Runway_activity::landing);
            std::cout << "Plane number " << activePlane.getFlightNumber() << " landed after " << waited << " time unit" << (waited == 1 ? "" : "s") << " in the landing queue." << std::endl;
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

void Variation_0::printStatistics()
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
        std::cout << "Total number of planes left in landing queue:        " << landingQueue.size() << std::endl;
        std::cout << "Total number of planes left in takeoff queue:        " << takeoffQueue.size() << std::endl;
        std::cout << "Percentage of time airport idle:                     " << 100.0 * (( float ) idleTime) / (( float ) timeLimit) << "%" << std::endl;
        std::cout << "Average wait in landing queue:                       " << (( float ) landingWait) / (( float ) landingsGranted) << " time units" << std::endl;
        std::cout << "Average wait in takeoff queue:                       " << (( float ) takeoffWait) / (( float ) takeoffsGranted) << " time units" << std::endl;
        std::cout << "Average observed rate of planes wanting to land:     " << (( float ) landingsRequested) / (( float ) timeLimit) << " per time units" << std::endl;
        std::cout << "Average observed rate of planes wanting to take off: " << (( float ) takeoffsRequested) / (( float ) timeLimit) << " per time units" << std::endl;
}
