#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

struct Point
{
    float  x, y, z;
    void set_XYZ(float X, float Y, float Z)
    {
        x=X;
        y=Y;
        z=Z;
    }
};


#endif //POINT_H
