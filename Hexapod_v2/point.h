#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point
{
public:
    Point();
    Point(float X, float Y, float Z);
    void copy(Point P);
    float get_X();
    float get_Y();
    float get_Z();
    void set_X(float X);
    void set_Y(float Y);
    void set_Z(float Z);
    void set_XYZ(float X, float Y, float Z);
    ~Point();

private:
    float  x, y, z;
};

#endif //POINT_H
