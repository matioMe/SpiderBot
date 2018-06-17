#ifndef PCA9685_H
#define PCA9685_H

#include <wiringPi.h>
#include <iostream>

#define MODE1 0x00			//Mode  register  1
#define MODE2 0x01			//Mode  register  2
//#define SUBADR1 0x02		//I2C-bus subaddress 1
//#define SUBADR2 0x03		//I2C-bus subaddress 2
//#define SUBADR3 0x04		//I2C-bus subaddress 3
//#define ALLCALLADR 0x05     //LED All Call I2C-bus address
#define LED0 0x6			//LED0 start register
#define LED0_ON_L 0x6		//LED0 output and brightness control byte 0
#define LED0_ON_H 0x7		//LED0 output and brightness control byte 1
#define LED0_OFF_L 0x8		//LED0 output and brightness control byte 2
#define LED0_OFF_H 0x9		//LED0 output and brightness control byte 3
#define LED_MULTIPLYER 4	// For the other 15 channels
//#define ALLLED_ON_L 0xFA    //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
//#define ALLLED_ON_H 0xFB	//load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
//#define ALLLED_OFF_L 0xFC	//load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
//#define ALLLED_OFF_H 0xFD	//load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE		//prescaler for output frequency
#define CLOCK_FREQ 25000000.0 //25MHz default osc clock

class PCA9685
{
public:
    PCA9685(int pcaAdress);
	~PCA9685();

	void setPWMFreq(int frequency);
	void setPWM(uint8_t led, int on_value, int off_value);
	int getPWM(uint8_t led);
	void setServo(uint8_t servo, int angle);

private:
	//I2C *i2c;
	int fd;
	void reset(void);
	void setOn_0(int led);
};

#endif // PCA9685_H
