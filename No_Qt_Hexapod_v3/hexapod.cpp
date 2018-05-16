#include "hexapod.h"
#include "leg.h"
#include "pas.h"
#include "const.h"
#include <wiringPi.h>

Hexapod::Hexapod()
{
    Point initPoint[6];

    //init
    initPoint[0].set_XYZ(LEG_0_START_X, LEG_0_START_Y, LEG_0_START_Z);
    initPoint[1].set_XYZ(LEG_1_START_X, LEG_1_START_Y, LEG_1_START_Z);
    initPoint[2].set_XYZ(LEG_2_START_X, LEG_2_START_Y, LEG_2_START_Z);
    initPoint[3].set_XYZ(LEG_3_START_X, LEG_3_START_Y, LEG_3_START_Z);
    initPoint[4].set_XYZ(LEG_4_START_X, LEG_4_START_Y, LEG_4_START_Z);
    initPoint[5].set_XYZ(LEG_5_START_X, LEG_5_START_Y, LEG_5_START_Z);

    //create legs
    leg[0]=new Leg(O_LENGTH_0, A_LENGTH_0, B_LENGTH_0, C_LENGTH_0, initPoint[0], O_ANGLE_0);
    leg[1]=new Leg(O_LENGTH_1, A_LENGTH_1, B_LENGTH_1, C_LENGTH_1, initPoint[1], O_ANGLE_1);
    leg[2]=new Leg(O_LENGTH_2, A_LENGTH_2, B_LENGTH_2, C_LENGTH_2, initPoint[2], O_ANGLE_2);
    leg[3]=new Leg(O_LENGTH_3, A_LENGTH_3, B_LENGTH_3, C_LENGTH_3, initPoint[3], O_ANGLE_3);
    leg[4]=new Leg(O_LENGTH_4, A_LENGTH_4, B_LENGTH_4, C_LENGTH_4, initPoint[4], O_ANGLE_4);
    leg[5]=new Leg(O_LENGTH_5, A_LENGTH_5, B_LENGTH_5, C_LENGTH_5, initPoint[5], O_ANGLE_5);


    //offsets in tabs
    offsetServo[0]=OFFSET_0_A;
    offsetServo[1]=OFFSET_0_B;
    offsetServo[2]=OFFSET_0_C;

    offsetServo[3]=OFFSET_1_A;
    offsetServo[4]=OFFSET_1_B;
    offsetServo[5]=OFFSET_1_C;
    
    offsetServo[6]=OFFSET_2_A;
    offsetServo[7]=OFFSET_2_B;
    offsetServo[8]=OFFSET_2_C;
    
    offsetServo[9]=OFFSET_3_A;
    offsetServo[10]=OFFSET_3_B;
    offsetServo[11]=OFFSET_3_C;
    
    offsetServo[12]=OFFSET_4_A;
    offsetServo[13]=OFFSET_4_B;
    offsetServo[14]=OFFSET_4_C;
    
    offsetServo[15]=OFFSET_5_A;
    offsetServo[16]=OFFSET_5_B;
    offsetServo[17]=OFFSET_5_C;
    

    //lancer thread Camera
    system("pwd");

    //initialisation i2c
    initServos90(PCA9685_0_Adress); //device 0x04
    initServos90(PCA9685_1_Adress); //device 0x08

    //lancer thread de loop controle
    loopMouvements();
}



Hexapod::~Hexapod()
{
    for(int i=0; i<6; i++)
    {
        delete leg[i];
    }
}


/**************

  PCA DEVICE

**************/

int Hexapod::initI2C_PCA9685(int deviceAdress)
{
	int error;

	error=wiringPiSetup();
	error=wiringPiI2CSetup(0x42);
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x10))<0) return error; //MODE1
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x01, 0x04))<0) return error; //MODE 2
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0xFE, 0x87))<0) return error;  //PRESCALE (50Hz)
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x00))<0) return error; //MODE1


	return 0;
}

int Hexapod::initServos90(int deviceAdress)
{
	int error=0;
	int servoPWM[9]={0};
	if((error=initI2C_PCA9685(int deviceAdress))<0) return error;

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(deviceAdress, 6+i*4, 0x00))<0) return error;
		if((error=wiringPiI2CWriteReg8(deviceAdress, 7+i*4, 0x00))<0) return error;
		if((error=wiringPiI2CWriteReg8(deviceAdress, 8+i*4, 0x33))<0) return error;
		if((error=wiringPiI2CWriteReg8(deviceAdress, 9+i*4, 0x01))<0) return error;
	}

	return 0;
}



/**************

  DEPLACEMENTS

**************/


int Hexapod::updateLegPos(Leg* leg, int n) //n numero de la patte
{
	int servo[3];

	switch(n)
	{
		case 0:
			actualizePos(leg.get_Ad()+OFFSET_0_A, REG_L_0_SERVO_A, PCA9685_0_Adress);
			actualizePos(leg.get_Bd(), , );//MQ NUMERO DE REGISTRE EN FONCTION DU CABLAGE + NUM DE DEVICE PCA9685 + AJOUTER OFFSETS!!
			actualizePos(leg.get_Cd(), , );
		break;

		case 1:
			actualizePos(leg.get_Ad(), , );
			actualizePos(leg.get_Bd(), , );
			actualizePos(leg.get_Cd(), , );
		break;

		case 2:
			actualizePos(leg.get_Ad(), , );
			actualizePos(leg.get_Bd(), , );
			actualizePos(leg.get_Cd(), , );
		break;

		case 3:
			actualizePos(leg.get_Ad(), , );
			actualizePos(leg.get_Bd(), , );
			actualizePos(leg.get_Cd(), , );
		break;

		case 4:
			actualizePos(leg.get_Ad(), , );
			actualizePos(leg.get_Bd(), , );
			actualizePos(leg.get_Cd(), , );
		break;

		case 5:
			actualizePos(leg.get_Ad(), , );
			actualizePos(leg.get_Bd(), , );
			actualizePos(leg.get_Cd(), , );
		break;
	}

	return 0;
}

int Hexapod::actualizePos(int angle, int numRegLow, int deviceId)
{
	int valRegLow, valRegHigh;

	angle=angle*205/180+205;

	//conv 2 hexa
	valRegLow=angle%(16*16);
	valRegHigh=(angle-valRegLow)/(16*16);

	if(wiringPiI2CWriteReg8(deviceId, numRegLow, valRegLow)<0)
	{
		cout<<"Error during writing in register " << numRegLow << " of device " << deviceAdress << "." << endl;
	}
	if(wiringPiI2CWriteReg8(deviceId, numRegLow+1, valRegHigh)<0)
	{
		cout<<"Error during writing in register " << numRegLow+1 << " of device " << deviceAdress << "." << endl;
	}

	return 0;
}

int Hexapod::loopMouvements() //inclure dans classe leg
{

	int n=15; //nombre de découpe de la courbe
	float h=2; //hauteur des pas
	m_numStep=0; //numero de pas, pair ou impair?
	Point pointTarget[6];
	Joystick J1, J2;

	while(1) //thread et mutex pour plus tard. Plus de réactivité, possibilité de stopper le mouvement en cours.
	{
		//choix direction (hardcore: détecter et mettre à jour pointTarget[])
		
		//MQ récupération des datas des sticks + mode à mettre dans les méthodes de la classe


		chooseDirection(J1, J2, pointTarget[]);

		/***********************

			CALCUL DES PAS

		************************/

		//calcLegStepRegular ou calcLegMove
		for(int i=0; i<6; i++)
		{
			if(!m_numStep%2) //Even step 
			{
				if(!i%2) leg[i].calcLegStepRegular(pointTarget[i], n, h); //even
				else leg[i].calcLegMove(pointTarget[i], n); //odd
			}
			else //Odd step
			{
				if(i%2) leg[i].calcLegStepRegular(pointTarget[i], n, h); //odd
				else leg[i].calcLegMove(pointTarget[i], n); //even
			}
		}

		for(int i=0; i<n+1; i++) //boucle for: n cycles, each points of the step
		{
			/*************************

			  CALCUL POSITION N POINT

			**************************/

			for(int j=0; j<6; j++) //move the 6 legs
			{
				if(!m_numStep%2) //even
				{
					if(!i%2) leg[i].moveLegStepRegular(); //even
					else leg[i].moveLegMove(); //odd
				}

				else
				{
					if(i%2)	leg[i].moveLegStepRegular(n); //odd
					else leg[i].moveLegMove(n); //even
				}
			}

			/***********************

			    UPDATE POSIIONS

			************************/
			
			for(int j=0; j<6; j++) updateLegPos(leg[j], j); //update Servos Angles in Degrees fr each legs
		}
		m_numStep++;
	}
}


/*



   1\           /2
	 \  _____  /
	  \|     |/
       |	 |
4_____ |  O  |_____3
	   |     |
	   |     |
	  /|_____|\
	 /		   \
  5 /           \6


-Each odd legs step together whereas each even leg move at the same time.
-After the first cycle, odds and even rules switch. 

*/


int chooseDirection(Joystick J1, Joystick J2, Point pointTarget[6])
{
	centerTarget=m_O;
	float vectorLengh_J1;
	float vectorLengh_J2;

	if(mode==0) //Si mode déplacement
	{
		if(J1.speed >= SPEED_MIN) //deplacement en paralèlle
		{
			vectorLengh_J1=J1.speed*LENGH_STEP_MAX/SPEED_MAX;

			m_Target.set_XYZ(vectorLengh_J1*cos(J1.angle), vectorLengh_J1*sin(J1.angle), 0);
		}

		if(J2.speed >= SPEED_MIN) //modification de l'angle d'orientation
		{
			if(J2.angle > LEFT_MIN && J2.angle < LEFT_MAX && J2.angle >= ROTATION_MIN) angleTarget=J2.speed+J2.speed*ROTATION_MAX/SPEED_MAX;
			if(J2.angle > RIGHT_MIN && J2.angle < RIGHT_MAX && J2.angle >= ROTATION_MIN) angleTarget=J2.speed-J2.speed*ROTATION_MAX/SPEED_MAX;
		}

		for(int i=0; i<6; i++) //mise à jour des positions des targets. Peut être pas la meilleure méthode. C'est le plus compliqué
		{
			if(!numStep%2) //Even step 
			{
				if()
			}
			else //Odd step
			{
				
			}
		}
	}
	return 0;
}
























































/*****************

	OLD TOOLS

*****************/


int Hexapod::updateAnglesDegree(int deviceAdress, float angle[9]) //inclure dans classe leg
{
	int error=0;
	int servoPWM[9]={0};

	for(int i=0; i<9; i++)
	{
		angle[i]=angle[i]+offsetServo[i];
	}

	if(deviceAdress==0x04)
	{
		for(int i=0; i<9; i++)
		{
			//conv degré pwm
			servoPWM[i]=floor(angle[i]*205/180)+205;
		
			//conv hexa
			firstReg=pwmValue%(16*16);
			secondReg=(pwmValue-firstReg)/(16*16);
		
			//update servos angles
			if((error=wiringPiI2CWriteReg8(0x04, 8+i*4, firstReg))<0) return error;
			if((error=wiringPiI2CWriteReg8(0x04, 9+i*4, secondReg))<0) return error;
		}
	}
	else //modif
	{
		for(int i=0; i<9; i++)
		{
			//conv degré pwm
			servoPWM[i]=floor(angle[i+9]*205/180)+205;
		
			//conv hexa
			firstReg=pwmValue%(16*16);
			secondReg=(pwmValue-firstReg)/(16*16);
		
			//update servos angles
			if((error=wiringPiI2CWriteReg8(0x04, 8+i*4, firstReg))<0) return error;
			if((error=wiringPiI2CWriteReg8(0x04, 9+i*4, secondReg))<0) return error;
		}
	}

	return 0;
}

//fast test
Hexapod::Hexapod(char opt)
{
	int adress1=0x00;
	int adress2=0x02;
	int adress1FirstReg=6;
	int adress2FirstReg=6;
	
	initI2C_PCA9685(0x00);
	initI2C_PCA9685(0x02);

	if(opt=='t')
	{
		for(int i=0; i<9; i++)
		{
			//update servos angles
			if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+i*4, 0x00))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+1+i*4, 0x00))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+2+i*4, 0x33))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+3+i*4, 0x01))<0) return error;
		}

		for(int i=0; i<9; i++)
		{
			//update servos angles
			if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+i*4, 0x00))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+1+i*4, 0x00))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+2+i*4, 0x33))<0) return error;
			if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+3+i*4, 0x01))<0) return error;
		}

		delay(1000);
	}
}