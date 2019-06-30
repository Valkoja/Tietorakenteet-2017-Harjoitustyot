#include "main.h"

Runway::Runway()
{
    currentStatus = Runway_activity::idle;
}

void Runway::setStatus(Runway_activity newStatus)
{
    currentStatus = newStatus;
}

Runway_activity Runway::getStatus()
{
    return currentStatus;
}
