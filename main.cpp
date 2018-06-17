#include <iostream>

#include "hexapod.h"

//#include "xml.h"


//g++ -Wall -lwiringPi camera.cpp hexapod.cpp leg.cpp main.cpp mymath.cpp network.cpp pca9685.cpp -o hexapod.app


//TESTS:
/*
    test1:
    g++ -Wall -lwiringPi main.cpp -o test.app
    test2:
    g++ -Wall -lwiringPi main.cpp leg.cpp pca9685.cpp mymath.cpp -o test.app
    test 3:
    g++ -Wall -lwiringPi hexapod.cpp leg.cpp main.cpp mymath.cpp pca9685.cpp -o hexapod.app
    test 4:
    g++ -Wall -lwiringPi -lsfml-network hexapod.cpp leg.cpp network.cpp main.cpp mymath.cpp pca9685.cpp -o hexapod.app
*/

//sudo i2cdetect -y 1

using namespace std;

int main(int argc, char *argv[])
{
	Hexapod();

	return 0;
}
