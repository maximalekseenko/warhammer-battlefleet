#pragma once

#include "../objects/vessel.h"

bool SetStates(Vessel* __vessel, double x, double y, int __steps=3);
bool GetNextState(VesselState* __vesselState, double x, double y, int __steps=3);
// bool SetState(VesselState* __vessel, double x, double y, int __steps);



double getOX();
double getOY();