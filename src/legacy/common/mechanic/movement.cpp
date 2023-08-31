#include "movement.h"
#include <cmath>
#include <iostream>

double oX = 0;
double oY = 0;
double getOX(){return oX;}
double getOY(){return oY;}

/** @brief Calculates center point and radius for path
 * 
 * @param __pointAX starting point X coordinate
 * @param __pointAY starting point Y coordinate
 * @param __pointBX ending point X coordinate
 * @param __pointBY ending point Y coordinate
 * @param __angle angle for tanget to circle at point A
 * @param __centerX return value, center point X coordinate
 * @param __centerY return value, center point Y coordinate
 * @param __radius return value, radius of circle
 */
void _GetPathCenterAndRadius(
    double __pointAX, double __pointAY,
    double __pointBX, double __pointBY,
    double __angle,

    double* __centerX, double* __centerY,
    double* __radius
)
{
    // !!! ALL CALCULATIONS DONE RELATIVE TO STARTING POINT !!!

    // relative target point (p, q) = (x1 - x2, y1 - y2)
    double _p = __pointBX - __pointAX;
    double _q = __pointBY - __pointAY;
    // find a and b for a line(ax + by = 0) that is perpendicular to vector from provided angle
    double _a = std::sin(__angle + M_PI_2);
    double _b = std::cos(__angle + M_PI_2);

    /*  find center point O(bt, -at), where
        t = (p^2 + q^2) / (2bp - 2aq)   note:formula came from fact, 
                                        that dist(O, B) == dist(O, A)
    */
    double _t = (_p * _p + _q * _q) / (2 * _b * _p - 2 * _a * _q);

    //
    *__centerX = (_b * _t) + __pointAX;
    *__centerY = (-_a * _t) + __pointAY;
    *__radius = std::hypot((_b * _t), (-_a * _t));
}



bool _SetState(VesselState* __vesselStateFrom, VesselState* __vesselStateTo, double __targetX, double __targetY, int __steps)
{
    double _centerX, _centerY, _radius;
    _GetPathCenterAndRadius(
        __vesselStateFrom->position[0],
        __vesselStateFrom->position[1],
        targetX,
        targetY,
        __vesselStateFrom->rotation,
        &_centerX,
        &_centerY,
        &_radius
    );

    // find path angle and distance
    // get angle from center to start_point(A) and end_point(B)
    double _angA = std::atan2( 0 - _oX,  0 - _oY);
    double _angB = std::atan2(_p - _oX, _q - _oY);

    // get angle
    double _d_angAB = std::fmod(_angA - _angB, 2*M_PI);

    // fix angle for clockwise movement
    // if ((_angB < 0) == (_b < 0))
    //     _d_angAB = _d_angAB - M_2_PI;

    // get path distance
    double _path_distance = std::abs(_d_angAB * _radius);
    // ^^^ ALL CALCULATIONS DONE RELATIVE TO STARTING POINT ^^^

    // actual center
    double _path_centerX = _oX + __vesselStateFrom->position[0];
    double _path_centerY = _oY + __vesselStateFrom->position[1];

    double _turn_angle = _angA + _d_angAB / __steps;

    if (__steps == 3)
    {
        oX = _path_centerX;
        oY = _path_centerY;
        std::cout << "------" << std::endl;
        std::cout << "a: " << _a << std::endl;
        std::cout << "_angA: " << _angA << std::endl;
        std::cout << "b: " << _b << std::endl;
        std::cout << "_angB: " << _angB << std::endl;
        std::cout << "_Dang: " << _d_angAB << std::endl;
        std::cout << "_Tang: " << _turn_angle << std::endl;
        // std::cout << "_ang: " << std::atan2(-_oY, -_oX) + _d_angAB / __steps << std::endl;
        std::cout << "_AA: " << std::cos(_turn_angle) << std::endl;
        std::cout << "_rad: " << _radius << std::endl;
    }


    // __vesselStateTo->position[0] = _path_centerX + std::cos(_turn_angle) * _radius;
    // __vesselStateTo->position[1] = _path_centerY + std::sin(_turn_angle) * _radius;
    __vesselStateTo->position[0] = _path_centerX + std::cos(_turn_angle) * _radius;
    __vesselStateTo->position[1] = _path_centerY + std::sin(_turn_angle) * _radius;
    __vesselStateTo->rotation = __vesselStateFrom->rotation + _d_angAB / __steps;

    // // make path points by modifing _cur_angle (angle between center and vessel)
    // _angle_by_step = 
    // _distance_by_step = _path_distance / path_len
    // _vessel_angle = start_angle
    // _cur_angle = math.atan2(-_o[1], -_o[0])
    // _cur_point = (start_point[0], start_point[1])

    // path_points.clear()
    // for _i in range(path_len):

    //     # turn current point
    //     _cur_angle -= _angle_by_step
    //     _vessel_angle += _angle_by_step

    //     # move current point
    //     _cur_point = (
    //         path_center[0] + math.cos(_cur_angle) * _radius,
    //         path_center[1] + math.sin(_cur_angle) * _radius
    //     )

    //     # add to list
    //     path_points.append(((_cur_point[0], _cur_point[1]), _vessel_angle))

    // # check if points are valid
    // global path_legal
    // path_legal = True
    // if abs(_angle_by_step) > path_angle_max: path_legal = False
    // if _distance_by_step < path_distance_min: path_legal = False
    // if _distance_by_step > path_distance_max: path_legal = False

    return true;
}


bool SetStates(Vessel* __vessel, double __targetX, double __targetY, int __steps)
{
    __vessel->TurnStates[0] = __vessel->CurrentState;
    for (int _step = 0; _step < __steps; _step ++)
    {
        if (!_SetState(
                &__vessel->TurnStates[_step], 
                &__vessel->TurnStates[_step + 1], 
                __targetX, __targetY, 
                __steps - _step
                ))
            return false;
    }

    return true;
}