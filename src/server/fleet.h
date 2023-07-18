#include "vessel.h"
#define ARRAYLIMIT_FLEET_VESSELSAMOUNT 16

struct Fleet
{
    Vessel vessels[ARRAYLIMIT_FLEET_VESSELSAMOUNT];
    int fleetsSize;
    Fleet* GetFleet(int);
    bool AddFleet();
    bool RemFleet(int);
};
