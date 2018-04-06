#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "leg.h"
class hexapod
{
public:
    hexapod();
    ~hexapod();

private:
    Leg* leg[6]; //
};

#endif // HEXAPOD_H
