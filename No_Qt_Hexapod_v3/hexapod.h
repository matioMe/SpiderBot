#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "leg.h"
#include "network.h"

class Hexapod: public Network
{
public:
    Hexapod();
    Hexapod(char opt);
    ~Hexapod();
    int initPosition(int deviceAdress);
    int updateAnglesDegree(int deviceAdress, float angle[9]);
    int loopMouvements();

private:
    Leg* leg[6];
    int angle[18];
    int offsetServo[18];
    int m_numStep;
    Point m_target; //position visée à la fin du prochain pas
    float m_angleTarget; //orientation visé à la fin du prochain pas 
    int m_mode; //mode de fonctionnement
m_anglem_angle

    int initI2C_PCA9685();
};

#endif // HEXAPOD_H
