#include <iostream>
#include "const.h"
#include "point.h"
#include "leg.h"
#include "hexapod.h"
//#include "xml.h"

using namespace std;

int main(int argc, char *argv[])
{
    Point start(4, 0, 0);
    Point end(2, 2, 0);
    Leg test(1, 1, sqrt(2), sqrt(2), start, 0);
    XML myXml("testXML");
    int n=100, h=2;
    float tabPos[n*3];
    test.calcLegStep(start, end, n, h);

    //test.printActual();

    for(int i=0; i<n+1; i++)
    {
        cout<<i<< ":"<<endl;
        test.moveLegStep(i);
        test.printActual();

        //XML
        tabPos[i*3]=test.getActual_X();
        tabPos[i*3+1]=test.getActual_Y();
        tabPos[i*3+2]= test.getActual_Z();
    }
    myXml.generateFile(tabPos, 3);
    //test.printData();

    return 0;
}
