#include "hexapod.h"
#include "const.h"

hexapod::hexapod()
{
    Point initPoint[6];

    initPoint[0].set_XYZ(LEG_0_START_X, LEG_0_START_Y, LEG_0_START_Z);
    initPoint[1].set_XYZ(LEG_1_START_X, LEG_1_START_Y, LEG_1_START_Z);
    initPoint[2].set_XYZ(LEG_2_START_X, LEG_2_START_Y, LEG_2_START_Z);
    initPoint[3].set_XYZ(LEG_3_START_X, LEG_3_START_Y, LEG_3_START_Z);
    initPoint[4].set_XYZ(LEG_4_START_X, LEG_4_START_Y, LEG_4_START_Z);
    initPoint[5].set_XYZ(LEG_5_START_X, LEG_5_START_Y, LEG_5_START_Z);

    leg[0]=new Leg(O_LENGTH_0, A_LENGTH_0, B_LENGTH_0, C_LENGTH_0, initPoint[0], O_ANGLE_0);
    leg[1]=new Leg(O_LENGTH_1, A_LENGTH_1, B_LENGTH_1, C_LENGTH_1, initPoint[1], O_ANGLE_1);
    leg[2]=new Leg(O_LENGTH_2, A_LENGTH_2, B_LENGTH_2, C_LENGTH_2, initPoint[2], O_ANGLE_2);
    leg[3]=new Leg(O_LENGTH_3, A_LENGTH_3, B_LENGTH_3, C_LENGTH_3, initPoint[3], O_ANGLE_3);
    leg[4]=new Leg(O_LENGTH_4, A_LENGTH_4, B_LENGTH_4, C_LENGTH_4, initPoint[4], O_ANGLE_4);
    leg[5]=new Leg(O_LENGTH_5, A_LENGTH_5, B_LENGTH_5, C_LENGTH_5, initPoint[5], O_ANGLE_5);
}


hexapod::~hexapod()
{
    for(int i=0; i<5; i++)
    {
        delete leg[i];
    }
}
