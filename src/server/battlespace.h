#include "fleet.h"
#define ARRAYLIMIT_BATTLESPACE_FLEETAMOUNT 8
#define ARRAYLIMIT_BATTLESPACE_VESSELAMOUNT 128


struct Battlespace
{
    int size[2];

    Fleet fleets[ARRAYLIMIT_BATTLESPACE_FLEETAMOUNT];
    int fleetsSize;
    Fleet* GetFleet(int);
    bool AddFleet();
    bool RemFleet(int);
};
