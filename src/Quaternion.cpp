/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 */

#include "config.h"
#include "Quaternion.h"

Quaternion::Quaternion()
: _x(0), _y(0), _z(0), _w(0)
{
    //
}

Quaternion::Quaternion(float x, float y, float z, float w)
: _x(x), _y(y), _z(z), _w(w)
{
    //
}

Quaternion::Quaternion(const Quaternion& q)
: _x(q._x), _y(q._y), _z(q._z), _w(q._w)
{
    //
}

Quaternion::~Quaternion()
{
    //
}

Quaternion Quaternion::diff(const Quaternion &a, const Quaternion &b)
{
    Quaternion inv = a;
    inv.inverse();
    return inv * b;
}

void Quaternion::inverse()
{
    Quaternion qu = (*this);
    qu.conjugate();
    (*this) = qu / Quaternion::dot((*this), (*this));
}


void Quaternion::conjugate()
{
    Quaternion qu;
    
    qu._x = -this->_x;
    qu._y = -this->_y;
    qu._z = -this->_z;
    qu._w = this->_w;

    (*this) = qu;
}

float Quaternion::dot(const Quaternion &q1, const Quaternion &q2)
{
    return q1._x*q2._x + q1._y*q2._y + q1._z*q2._z + q1._w*q2._w;
}


float
Quaternion::getW()
{
    return _w;
}

float
Quaternion::getX()
{
    return _x;
}

float
Quaternion::getY()
{
    return _y;
}

float
Quaternion::getZ()
{
    return _z;
}

Quaternion Quaternion::operator*(const Quaternion &q)
{
    Quaternion qu;
    qu._x = this->_w*q._x + this->_x*q._w + this->_y*q._z - this->_z*q._y;
    qu._y = this->_w*q._y + this->_y*q._w + this->_z*q._x - this->_x*q._z;
    qu._z = this->_w*q._z + this->_z*q._w + this->_x*q._y - this->_y*q._x;
    qu._w = this->_w*q._w - this->_x*q._x - this->_y*q._y - this->_z*q._z;
    return qu;
}

Quaternion Quaternion::operator/ (const float s)
{
    Quaternion qu = (*this);
    return Quaternion(qu._x / s, qu._y / s, qu._z / s, qu._w / s);
}

