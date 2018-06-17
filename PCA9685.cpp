#include "PCA9685.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>


PCA9685::PCA9685(int pcaAdress)
{
	fd=wiringPiI2CSetup(pcaAdress);
	reset();
	setPWMFreq(50);

}
PCA9685::~PCA9685()
{

}

void PCA9685::reset()
{
	wiringPiI2CWriteReg8(fd, MODE1, 0x00); //Normal mode
	wiringPiI2CWriteReg8(fd, MODE2, 0x04); //totem pole
}

void PCA9685::setPWMFreq(int frequency)
{
	uint8_t prescale_val = (CLOCK_FREQ / (4096 * frequency*0.95))  - 1;
	wiringPiI2CWriteReg8(fd, MODE1, 0x10); //sleep
	wiringPiI2CWriteReg8(fd, PRE_SCALE, prescale_val); // multiplyer for PWM frequency
	wiringPiI2CWriteReg8(fd, MODE1, 0x00); //restart
	wiringPiI2CWriteReg8(fd, MODE2, 0x04); //totem pole (default)
}

void PCA9685::setPWM(uint8_t led, int on_value, int off_value)
{
	wiringPiI2CWriteReg8(fd, LED0_ON_L + LED_MULTIPLYER * (led), on_value & 0xFF);
	wiringPiI2CWriteReg8(fd, LED0_ON_H + LED_MULTIPLYER * (led), on_value >> 8);
	wiringPiI2CWriteReg8(fd, LED0_OFF_L + LED_MULTIPLYER * (led), off_value & 0xFF);
	wiringPiI2CWriteReg8(fd, LED0_OFF_H + LED_MULTIPLYER * (led), off_value >> 8);
}

int PCA9685::getPWM(uint8_t led)
{
	int ledval = 0;
	ledval = wiringPiI2CReadReg8(fd, LED0_OFF_H + LED_MULTIPLYER * (led-1));
	ledval = ledval & 0xf;
	ledval <<= 8;
	ledval += wiringPiI2CReadReg8(fd, LED0_OFF_L + LED_MULTIPLYER * (led-1));

	return ledval;
}

void PCA9685::setServo(uint8_t led, int angle)
{
	int pwm=angle*2+110;
	wiringPiI2CWriteReg8(fd, LED0_OFF_L + LED_MULTIPLYER * (led), pwm & 0xFF);
	wiringPiI2CWriteReg8(fd, LED0_OFF_H + LED_MULTIPLYER * (led), pwm >> 8);
}

void PCA9685::setOn_0(int led)
{
	wiringPiI2CWriteReg8(fd, LED0_ON_L + LED_MULTIPLYER * (led), 0);
	wiringPiI2CWriteReg8(fd, LED0_ON_H + LED_MULTIPLYER * (led), 0);
} 
/*
4096/20
ca

*/
