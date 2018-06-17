#include <thread>
#include <iostream>

#include "hexapod.h"
#include "leg.h"
#include "PCA9685.h"
#include "joystick.h"
#include "setup.h"
#include "network.h"

//#define PCA9685_0_ADDRESS 0x04

Hexapod::Hexapod()
{

	m_mode=START_MODE; //mode par défaut
    //init
    initPoint[0].set_XYZ(LEG_0_START_X, LEG_0_START_Y, LEG_0_START_Z);
    initPoint[1].set_XYZ(LEG_1_START_X, LEG_1_START_Y, LEG_1_START_Z);
    initPoint[2].set_XYZ(LEG_2_START_X, LEG_2_START_Y, LEG_2_START_Z);
    initPoint[3].set_XYZ(LEG_3_START_X, LEG_3_START_Y, LEG_3_START_Z);
    initPoint[4].set_XYZ(LEG_4_START_X, LEG_4_START_Y, LEG_4_START_Z);
    initPoint[5].set_XYZ(LEG_5_START_X, LEG_5_START_Y, LEG_5_START_Z);

    //create legs
    leg[0]=new Leg(O_LENGTH_0, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[0], O_ANGLE_0);
    leg[1]=new Leg(O_LENGTH_1, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[1], O_ANGLE_1);
    leg[2]=new Leg(O_LENGTH_2, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[2], O_ANGLE_2);
    leg[3]=new Leg(O_LENGTH_3, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[3], O_ANGLE_3);
    leg[4]=new Leg(O_LENGTH_4, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[4], O_ANGLE_4);
    leg[5]=new Leg(O_LENGTH_5, A_LENGTH, B_LENGTH, C_LENGTH, initPoint[5], O_ANGLE_5);


    //initialisation i2c, création des objets PCA
    PCA_0=new PCA9685(PCA9685_0_ADDRESS);
    PCA_1=new PCA9685(PCA9685_1_ADDRESS);

    for(int j=0; j<6; j++) updateLegPos(leg[j], j); //update Servos Angles in Degrees for each legs
    
    //delay(1000);

    //lancer camera

    //lancer thread network

    //lancer fonction de loop en thread principal
    //moveMainLoop();
}

Hexapod::~Hexapod()
{
    for(int i=0; i<6; i++)
    {
        delete leg[i];
    }
    delete PCA_0;
    delete PCA_1;
}



/**************

  DEPLACEMENTS

**************/

int Hexapod::updateLegPos(Leg* leg, int n) //n numero de la patte OK
{
	switch(n)
	{
		case 0: //PCA_0
			actualizePos(leg->get_Ad()+OFFSET_0_A, PIN_L0_SERVO_A, PCA9685_0);
			actualizePos(leg->get_Bd()+OFFSET_0_B, PIN_L0_SERVO_B, PCA9685_0);
			actualizePos(leg->get_Cd()+OFFSET_0_C, PIN_L0_SERVO_C, PCA9685_0);
		break;

		case 1://PCA_1
			actualizePos(leg->get_Ad()+OFFSET_1_A, PIN_L1_SERVO_A, PCA9685_1);
			actualizePos(leg->get_Bd()+OFFSET_1_B, PIN_L1_SERVO_B, PCA9685_1);
			actualizePos(leg->get_Cd()+OFFSET_1_C, PIN_L1_SERVO_C, PCA9685_1);
		break;

		case 2://PCA_1
			actualizePos(leg->get_Ad()+OFFSET_2_A, PIN_L2_SERVO_A, PCA9685_1);
			actualizePos(leg->get_Bd()+OFFSET_2_B, PIN_L2_SERVO_B, PCA9685_1);
			actualizePos(leg->get_Cd()+OFFSET_2_C, PIN_L2_SERVO_C, PCA9685_1);
		break;

		case 3://PCA_0
			actualizePos(leg->get_Ad()+OFFSET_3_A, PIN_L3_SERVO_A, PCA9685_0);
			actualizePos(leg->get_Bd()+OFFSET_3_B, PIN_L3_SERVO_B, PCA9685_0);
			actualizePos(leg->get_Cd()+OFFSET_3_C, PIN_L3_SERVO_C, PCA9685_0);
		break;

		case 4://PCA_0
			actualizePos(leg->get_Ad()+OFFSET_4_A, PIN_L4_SERVO_A, PCA9685_0);
			actualizePos(leg->get_Bd()+OFFSET_4_B, PIN_L4_SERVO_B, PCA9685_0);
			actualizePos(leg->get_Cd()+OFFSET_4_C, PIN_L4_SERVO_C, PCA9685_0);
		break;

		case 5://PCA_1
			actualizePos(leg->get_Ad()+OFFSET_5_A, PIN_L5_SERVO_A, PCA9685_1);
			actualizePos(leg->get_Bd()+OFFSET_5_B, PIN_L5_SERVO_B, PCA9685_1);
			actualizePos(leg->get_Cd()+OFFSET_5_C, PIN_L5_SERVO_C, PCA9685_1);
		break;
	}

	return 0;
}

int Hexapod::actualizePos(int angleDegree, int pinNum, int pcaNum) //OK
{

    if((pcaNum==0 && (pinNum==7 || pinNum==10 || pinNum==13 )) || (pcaNum==1 && (pinNum==8 || pinNum==5 || pinNum== 2 )))
    {
        cout<<"Value: "<<pcaNum<<"."<<pinNum<<" :"<<endl;
        cout<<angleDegree<<endl;
    }

    if((pcaNum==0 && (pinNum==6 || pinNum==9 || pinNum==12 )) || pcaNum==1 && ((pinNum==7 || pinNum==4 || pinNum== 1 )))
    {
        cout<<"Value: "<<pcaNum<<"."<<pinNum<<" :"<<endl;
        cout<<angleDegree<<endl;
    }


    if((pcaNum==0 && (pinNum==8 || pinNum==11 || pinNum==14 )) || pcaNum==1 && ((pinNum==9 || pinNum==6 || pinNum== 3 )))
    {
        cout<<"Value: "<<pcaNum<<"."<<pinNum<<" :"<<endl;
        cout<<angleDegree<<endl;
    }

	
	if(pcaNum==PCA9685_0)
	{
        //cout<<"PCA0"<<endl;
        PCA_0->setServo(pinNum, angleDegree);
	}
	if(pcaNum==PCA9685_1)
	{
        //cout<<"PCA1"<<endl;
        PCA_1->setServo(pinNum, angleDegree);
	}

	return 0;
}


int Hexapod::moveMainLoop()
{

    int n=4; //nombre de découpe de la courbe
    float h=2; //hauteur des pas

	m_numStep=0; //numero de pas, pair ou impair?
    Joystick J1, J2;

    J1.angle=90*PI/180;
    J1.speed=1;


    while(1) //thread et mutex pour plus tard. Plus de réactivité, possibilité de stopper le mouvement en cours, etc...
	{
        chooseDirection(J1, J2);

        //calcLegStepRegular ou calcLegMove
		for(int i=0; i<6; i++)
		{
            if(m_numStep%2==0) //Even step
			{
                if(i%2==0) leg[i]->SA_calcStep(legTarget[i], n, h); //even leg
                else leg[i]->calcLegMove(legTarget[i], n); //odd leg
			}
			else //Odd step
			{
                if(i%2==1) leg[i]->SA_calcStep(legTarget[i], n, h); //odd
                else leg[i]->calcLegMove(legTarget[i], n); //even
            }
		}

        for(int i=1; i<=n; i++) //boucle for: n cycles, each points of the step
        {
            //move
            for(int j=0; j<6; j++) //move the 6 legs
            {
                if(m_numStep%2==0) //even
                {
                    if(j%2==0) leg[j]->SA_moveStep(i); //even
                    else leg[j]->moveLegMove(i); //odd
                }
                else
                {
                    if(j%2==1)	leg[j]->SA_moveStep(i); //odd
                    else leg[j]->moveLegMove(i); //even
                }
            }

            for(int j=0; j<6; j++) updateLegPos(leg[j], j); //update Servos position in Degrees fr each legs
            //delay(500); //delai entre chaque mouvements
        }

		m_numStep++;
	}
}


/*



   0\           /1
	 \  _____  /
	  \|     |/
       |	 |
3_____ |  O  |_____2
	   |     |
	   |     |
	  /|_____|\
	 /		   \
  4 /           \5


-Each odd legs steps together whereas each even legs moves at the same time.
-After each cycle, odds and evens rules switch. 

*/


int Hexapod::chooseDirection(Joystick J1, Joystick J2) //OK!
{
	float vectorLengh_J1;
    //float vectorLengh_J2;
	Point decalage;

	//init
	decalage.set_XYZ(0,0,0);

	if(m_mode==0) //Si mode est déplacement
	{
        if(J1.speed >= J1_SPEED_MIN && J1.speed <= J1_SPEED_MAX) //deplacement en parallèle
		{
            vectorLengh_J1=J1.speed*LENGH_STEP_MAX; //calc de la longueur du pas

			decalage.x=vectorLengh_J1*cos(J1.angle);
            decalage.y=vectorLengh_J1*sin(J1.angle);
			m_target.set_XYZ(J1.speed*LENGH_STEP_MAX+decalage.x, J1.speed*LENGH_STEP_MAX+decalage.y, 0); //cible du centre du robot
		}
        else
		{
			vectorLengh_J1=0;
			m_target.set_XYZ(0, 0, 0);
		}

		for(int i=0; i<6; i++) //mise à jour des positions des targets. Peut être pas la meilleure méthode. C'est le plus compliqué
		{
            if(m_numStep%2==0) //Even step
			{
                if(i%2==0) //num de patte paire
					legTarget[i].set_XYZ(
                        initPoint[i].x+decalage.x,
                        initPoint[i].y+decalage.y,
                        initPoint[i].z);

				else
					legTarget[i].set_XYZ(
                        initPoint[i].x-decalage.x,
                        initPoint[i].y-decalage.y,
                        initPoint[i].z);
			}
			else //Odd step
			{
                if(i%2==0) //num patte paire
					legTarget[i].set_XYZ(
                        initPoint[i].x-decalage.x,
                        initPoint[i].y-decalage.y,
                        initPoint[i].z);

				else
					legTarget[i].set_XYZ(
                        initPoint[i].x+decalage.x,
                        initPoint[i].y+decalage.y,
                        initPoint[i].z);
			} 
		}
	}
	return 0;
}


/*



int Hexapod::moveMainLoop()
{

    int n=4; //nombre de découpe de la courbe
    float h=2; //hauteur des pas

    m_numStep=0; //numero de pas, pair ou impair?
    Point pointTarget[6]={0};
    Joystick J1, J2;

    J1.angle=90*PI/180;
    J1.speed=1;


    while(1) //thread et mutex pour plus tard. Plus de réactivité, possibilité de stopper le mouvement en cours, etc...
    {

        //MQ récupération des datas des sticks + à mettre dans les méthodes de la classe
        chooseDirection(J1, J2, pointTarget);

        //calcLegStepRegular ou calcLegMove
        for(int i=0; i<6; i++)
        {
            if(m_numStep%2==0) //Even step
            {
                if(i%2==0) leg[i]->calcLegStepRegular(legTarget[i], n, h); //even
                else leg[i]->calcLegMove(legTarget[i], n); //odd
            }
            else //Odd step
            {
                if(i%2==1) leg[i]->calcLegStepRegular(legTarget[i], n, h); //odd
                else leg[i]->calcLegMove(legTarget[i], n); //even
            }
        }

        //calc positions & move
        for(int i=0; i<n+1; i++) //boucle for: n cycles, each points of the step
        {
            for(int j=0; j<6; j++) //move the 6 legs
            {
                if(!m_numStep%2) //even
                {
                    if(i%2==0) leg[j]->moveLegStepRegular(i); //even
                    else leg[j]->moveLegMove(i); //odd
                }
                else
                {
                    if(i%2==1)	leg[j]->moveLegStepRegular(i); //odd
                    else leg[j]->moveLegMove(i); //even
                }
            }

            for(int j=0; j<6; j++) updateLegPos(leg[j], j); //update Servos Angles in Degrees fr each legs
            //delay(500); //delai entre chaque mouvements
        }
        m_numStep++;
    }
}




*/
