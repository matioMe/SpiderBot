#ifndef CONST_H
#define CONST_H

#define LEGS_3      0
#define RASPBERRY_PI_3  1

//starting const
#define START_MODE    0


//legs lengh & angle
#define A_LENGTH 3.5
#define B_LENGTH 4.7
#define C_LENGTH 6.7


//leg0
#define O_LENGTH_0 8

//leg1
#define O_LENGTH_1 8

//leg2
#define O_LENGTH_2 4.7

//leg3 OK
#define O_LENGTH_3 4.7

//leg4 OK
#define O_LENGTH_4 8

//leg5 OK
#define O_LENGTH_5 8

//O angle OK
#define O_ANGLE_0 125
#define O_ANGLE_1 55
#define O_ANGLE_2 0
#define O_ANGLE_3 180
#define O_ANGLE_4 235
#define O_ANGLE_5 305

//offsets
#define OFFSET_0_A 5   //Epaule B0S6
#define OFFSET_0_B 5   //Coude  B0S7
#define OFFSET_0_C 0   //Poignet B0S8

#define OFFSET_1_A 10   //Epaule B1S1
#define OFFSET_1_B -15   //Coude B1S2
#define OFFSET_1_C -3   //Poignet B1S3

#define OFFSET_2_A 0  //Epaule B1S4
#define OFFSET_2_B -5   //Coude B1S5
#define OFFSET_2_C 20   //Poignet B1S6

#define OFFSET_3_A 5   //Epaule B0S9
#define OFFSET_3_B 8   //Coude B0S10
#define OFFSET_3_C 8   //Poignet B0S11

#define OFFSET_4_A 15   //Epaule B0S12
#define OFFSET_4_B 10   //Coude B0S13
#define OFFSET_4_C 15   //Poignet B0S14

#define OFFSET_5_A 15   //Epaule B1S7
#define OFFSET_5_B -15   //Coude B1S8
#define OFFSET_5_C -8   //Poignet B1S9

//starting position
//0
#define Z_LEVEL -11

#define LEG_0_START_X -9
#define LEG_0_START_Y 11
#define LEG_0_START_Z Z_LEVEL
//5
#define LEG_1_START_X 9 //9
#define LEG_1_START_Y 11 //11
#define LEG_1_START_Z Z_LEVEL
//2
#define LEG_2_START_X 11
#define LEG_2_START_Y 0
#define LEG_2_START_Z Z_LEVEL
//3
#define LEG_3_START_X -11
#define LEG_3_START_Y 0
#define LEG_3_START_Z Z_LEVEL
//4
#define LEG_4_START_X -9
#define LEG_4_START_Y -11
#define LEG_4_START_Z Z_LEVEL
//1
#define LEG_5_START_X 9
#define LEG_5_START_Y -11
#define LEG_5_START_Z Z_LEVEL



//PCA
#define PCA9685_0_ADDRESS 0x42
#define PCA9685_1_ADDRESS 0x41

#define PWM_FREQ 50

#define PCA9685_0 0
#define PCA9685_1 1

//adresse premier registre off PWM
#define PIN_L0_SERVO_A 8
#define PIN_L0_SERVO_B 7
#define PIN_L0_SERVO_C 6

#define PIN_L1_SERVO_A 9
#define PIN_L1_SERVO_B 8
#define PIN_L1_SERVO_C 7

#define PIN_L2_SERVO_A 6
#define PIN_L2_SERVO_B 5
#define PIN_L2_SERVO_C 4

#define PIN_L3_SERVO_A 11
#define PIN_L3_SERVO_B 10
#define PIN_L3_SERVO_C 9

#define PIN_L4_SERVO_A 14
#define PIN_L4_SERVO_B 13
#define PIN_L4_SERVO_C 12

#define PIN_L5_SERVO_A 3
#define PIN_L5_SERVO_B 2
#define PIN_L5_SERVO_C 1


//directions
//J1
#define J1_SPEED_MIN      0
#define J1_SPEED_MAX      1
#define LEFT_MIN       0
#define LEFT_MAX       0
#define ROTATION_MAX   20
#define LENGH_STEP_MAX 2
#define J1_SPEED_MIN   0

//J2
#define J2_SPEED_MIN  100
#define ROTATION_MIN  0
#define RIGHT_MIN     0
#define RIGHT_MAX     0


#endif // CONST_H

/*

MAPPING:

           0:              1:

            \0.6         /1.7
             \0.7       /1.8
              \0.8_____/1.9
         0.9\  |      |  /1.4
         0.10\ |      | /1.5
   3:     0.11\|      |/1.6      2:
               |      |
               |      |
               |______|
          0.14/        \1.3
         0.13/          \1.2
        0.12/            \1.1

          4:                5:

epaule: 0.8         1.9
        0.11        1.6
        0.14        1.3


*/
