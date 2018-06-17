#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "leg.h"
#include "joystick.h"
#include "PCA9685.h"
#include "setup.h"
#include "network.h"
#include <thread>
#include <mutex>

class Hexapod : public thread
{
public:
    Hexapod();
    ~Hexapod();

private:
    Leg* leg[6];
    Point initPoint[6];
    PCA9685 *PCA_0;
    PCA9685 *PCA_1;

    int angle[18];
    int offsetServo[18];
    int m_numStep;
    Point m_target;
    Point legTarget[6]; //position visée à la fin du prochain pas

    float m_angleTarget; //orientation visé à la fin du prochain pas, J2, rotation sur place
    int m_mode; //mode de fonctionnement


    int loopMouvements();
    int updateLegPos(Leg* leg, int n);
    int chooseDirection(Joystick J1, Joystick J2);
    int actualizePos(int angleDegree, int pinNum, int pcaNum);
    int moveMainLoop();


};

#endif // HEXAPOD_H
