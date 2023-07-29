#pragma once

#define TURNSTEPSLIMIT 8

#include "armament.h"
#include "vesseltype.h"
#include <cmath>

struct VesselState
{
    double position[2];
    double rotation;
};


struct Vessel
{
    // +++ CONSTRUCTION +++
    VesselType* vesselType;
    // Armament vesselType;
    

    // +++ INSTANCE VARIABLES +++
    VesselState CurrentState;
    VesselState TrurnStates[TURNSTEPSLIMIT];
    
};
