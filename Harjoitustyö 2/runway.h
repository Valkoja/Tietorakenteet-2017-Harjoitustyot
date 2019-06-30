#pragma once

class Runway
{
    public:
        Runway();
        void setStatus(Runway_activity newStatus);
        Runway_activity getStatus();

    private:
        Runway_activity currentStatus;
};
