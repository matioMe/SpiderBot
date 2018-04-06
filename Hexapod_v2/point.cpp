#include "point.h"

Point::Point(float X, float Y, float Z)
{
    x=X;
    y=Y;
    z=Z;

}

Point::Point()
{
    x=0;
    y=0;
    z=0;
}

Point::~Point()
{

}

void Point::copy(Point P)
{
    x=P.x;
    y=P.y;
    z=P.z;

    return;
}

float Point::get_X()
{
    return x;
}

float Point::get_Y()
{
    return y;
}

float Point::get_Z()
{
    return z;
}

void Point::set_X(float X)
{
    x=X;
    return;
}

void Point::set_Y(float Y)
{
    y=Y;
    return;
}

void Point::set_Z(float Z)
{
    z=Z;
    return;
}


void Point::set_XYZ(float X, float Y, float Z)
{
    x=X;
    y=Y;
    z=Z;
}
