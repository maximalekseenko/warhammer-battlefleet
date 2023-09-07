#pragma once


enum FireArc
{
    PROW        = 0b1000,
    PORT        = 0b0100,
    BACK        = 0b0010,
    STARBOARD   = 0b0001,
    DORSAL      = 0b1101,
    ALLAROUND   = 0b1111
};

struct Armament
{
    double RANGE;
    int FIREPOWER;
    FireArc FIREARC; 
};
