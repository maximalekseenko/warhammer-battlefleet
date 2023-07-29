#pragma once


#include "../objects/vesseltype.h"
#include <cmath>


// +++ IMPERIAL::VESSELTYPE::ESCORT +++
VesselType ImperialVesselTypeEscort
{
    .ID = 0x000,
    .NAME = "Escort",
    .IMAGE_PATH = "gothicescort.png",
    .HITS = 1,
    .SPEED = 30,
    .TURNS = M_PI / 6,
    .SHIELDS = 2,
    // .ARMOUR = 5+,
    .TURRETS = 1,
};


// +++ IMPERIAL::VESSELTYPE::CRUISER +++
VesselType ImperialVesselTypeCruiser
{
    .ID = 0x001,
    .NAME = "Cruilser",
    .IMAGE_PATH = "gothiccruiser.png",
    .HITS = 8,
    .SPEED = 20,
    .TURNS = M_PI / 12,
    .SHIELDS = 2,
    // .ARMOUR = 6+ front/5+,
    .TURRETS = 2,
};

// +++ IMPERIAL::VESSELTYPE::BATTLECRUISER +++
VesselType ImperialVesselTypeBattleCruiser
{
    .ID = 0x002,
    .NAME = "Battlecruiser",
    .IMAGE_PATH = "gothiccruiser.png",
    .HITS = 8,
    .SPEED = 20,
    .TURNS = M_PI / 12,
    .SHIELDS = 2,
    // .ARMOUR = 6+ front/5+,
    .TURRETS = 2,
};


// +++ IMPERIAL::VESSELTYPE::BATTLESHIP +++
VesselType ImperialVesselTypeBattleShip
{
    .ID = 0x003,
    .NAME = "Battleship",
    .IMAGE_PATH = "gothicbattleship.png",
    .HITS = 12,
    .SPEED = 20,
    .TURNS = M_PI / 12,
    .SHIELDS = 4,
    // .ARMOUR = 6+ front/5+,
    .TURRETS = 4,
};