#pragma once

#define ARMAMENTSLIMIT 8
#define ARMAMENTSLOTLIMIT 8
#include <vector>

struct VesselType
{
    int ID;
    

    // --------------------------------------------------
    // |            +++ CHARACTERISTICS +++             |
    // --------------------------------------------------

    /// @brief maximum amount of direct hits this vessel can handle
    int HITS;

    /// @brief maximum distance, this vessel can reach per step
    double SPEED;
    
    /// @brief maximum angle this vessel can turn per step
    double TURNS;

    /// @brief amount of damage, this vessel can absorb via shields
    int SHIELDS;

    /// @brief YES YES!!!!
    // TODO ARMOUR;

    /// @brief amount of ordnance, this vessel can take down via turrets
    int TURRETS;


    // --------------------------------------------------
    // |               +++ ASSEMBLES +++                |
    // --------------------------------------------------

    /// @brief list of armament slots and their options as ids
    std::vector<std::vector<int>> ARMAMENTS;



    // --------------------------------------------------
    // |              +++ CLIENT-ONLY +++               |
    // --------------------------------------------------

    const char* NAME;
    const char* IMAGE_PATH;

};
