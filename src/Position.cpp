/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#include "config.h"
#include "Position.h"

Position::Position()
: _x(0), _y(0), _z(0)
{
    //
}

Position::Position(float x, float y, float z)
: _x(x), _y(y), _z(z)
{
    //
}

Position::Position(const Position& q)
: _x(q._x), _y(q._y), _z(q._z)
{
    //
}

Position::~Position()
{
    //
}

float
Position::getX()
{
    return _x;
}

float
Position::getY()
{
    return _y;
}

float
Position::getZ()
{
    return _z;
}
