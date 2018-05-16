#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

/*
#include "const.h"
#include "point.h"
#include "leg.h"
#include "hexapod.h"
#include "xml.h"
*/
//g++ -Wall -lwiringPi camera.cpp hexapod.cpp leg.cpp main.cpp mymath.cpp network.cpp point.cpp -o hexapod.app


//tests:
//g++ -Wall -lwiringPi main.cpp -o test.app

using namespace std;

int initI2C_PCA9685(int deviceAdress);
void printError(int error);

//int main(int argc, char *argv[])
int main()
{
	wiringPiSetup();
	wiringPiI2CSetup(0x42);

	for(int i=0; i<65; i++)
	{
		cout<<"num: "<<i<<endl;
		initI2C_PCA9685(i);
	}
	//initI2C_PCA9685(0x04);
	
    return 0;
}

void printError(int error)
{
	cout<<"error"<<error<<endl;
}

int initI2C_PCA9685(int deviceAdress)
{
	int error;

	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x10))<0) cout<<error<<endl; //MODE1

	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x01, 0x04))<0) cout<<error<<endl; //MODE 2
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0xFE, 0x87))<0) cout<<error<<endl;  //PRESCALE (50Hz)
	delay(20);
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x00))<0) cout<<error<<endl; //MODE1
	delay(100);
	cout<<error<<endl;

	return 0;
}

/*
 * OFFSETS
 * LOOP DEPL
 * ORDRE APPEL FCTS
*/

/* I2C wiringPi:
 *
 * wiringPiSetup();
 *
 * int wiringPiI2CSetup (int devId);
 *
 * int wiringPiI2CWriteReg8(int fd, int reg, int data);
 */
