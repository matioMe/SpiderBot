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

int main(int argc, char *argv[])
{
	int error=0;
	int adress1=0x06;//00
	int adress2=0x04;//O4
	int adress1FirstReg=10;
	int adress2FirstReg=34;
	
	initI2C_PCA9685(adress1);
	initI2C_PCA9685(adress2);

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+i*4, 0x00))<0) printError(error);
		else cout<< "adress1" << endl;
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+2+i*4, 0x33))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+3+i*4, 0x01))<0) printError(error);
	}

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+i*4, 0x00))<0) printError(error);
		else cout<< "adress2" << endl;
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+2+i*4, 0x33))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+3+i*4, 0x01))<0) printError(error);
	}
	delay(1000);

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+2+i*4, 0xCD))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+3+i*4, 0x00))<0) printError(error);
	}

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+2+i*4, 0xCD))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+3+i*4, 0x00))<0) printError(error);
	}
	delay(5000);

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+2+i*4, 0x33))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress1, adress1FirstReg+3+i*4, 0x01))<0) printError(error);
	}

	for(int i=0; i<9; i++)
	{
		//update servos angles
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+1+i*4, 0x00))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+2+i*4, 0x33))<0) printError(error);
		if((error=wiringPiI2CWriteReg8(adress2, adress2FirstReg+3+i*4, 0x01))<0) printError(error);
	}
	delay(1000);

    return 0;
}

void printError(int error)
{
	cout<<"error"<<error<<endl;
}

int initI2C_PCA9685(int deviceAdress)
{
	int error;

	error=wiringPiSetup();
	error=wiringPiI2CSetup(0x42);
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x10))<0) ; //MODE1
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x01, 0x04))<0) ; //MODE 2
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0xFE, 0x87))<0) ;  //PRESCALE (50Hz)
	delay(20);
	if((error=wiringPiI2CWriteReg8(deviceAdress, 0x00, 0x00))<0) ; //MODE1
	delay(100);

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

