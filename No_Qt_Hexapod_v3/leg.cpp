#include "leg.h"
#include <wiringPi.h>

using namespace std;

Leg::Leg()
{

}

Leg::Leg(float o, float a, float b, float c, Point init, float Od)
{
  m_Ol=o;
  m_Al=a;
  m_Bl=b;
  m_Cl=c;

  m_Od=Od;
  m_Or=m_Od*PI/180;

  m_point_A.x=m_Ol*cos(m_Or);
  m_point_A.y=m_Ol*sin(m_Or);
  m_point_A.z=0;

  m_actual=init;
  setPosition(m_actual);
}

Leg::~Leg()
{
    setLengh(1,1,1,1);
    setOd(0);
}

void Leg::setOd(float Od)
{
  m_Od=Od;
  m_point_A.x=m_Ol*cos(m_Or);
  m_point_A.y=m_Ol*sin(m_Or);
  m_point_A.z=0;

  return;
}

void Leg::calcAnglesServos(Point target) //Point target //m_actual
{
    //transposition des positions
    m_actual=target;

    float e, mu, U, V, xA, yA, l;

    //calc position of A point in x/z plan
    xA=m_point_A.x;
    yA=m_point_A.y;

    //calc length leg on x/y plan with pythagore
    l=sqrt((m_actual.x-xA)*(m_actual.x-xA)+(m_actual.y-yA)*(m_actual.y-yA));

    //A angle in x/y plan
    m_Ar=acos((m_actual.x-xA)/l);

    //calc of the [BD] length in local u/v plan
    e=sqrt((l-m_Al)*(l-m_Al)+m_actual.z*m_actual.z); //Y?? vérif!!! modif à Z, à tester!!!!!

    //angle of (vBD) in u/v plan
    mu=acos((l-m_Al)/e);

    //intermediate values for last angles calc
    U=(m_Bl*m_Bl+e*e-m_Cl*m_Cl)/(2*e);
    V=e-U;

    //final angles calc
    m_Br=acos(U/m_Bl)-mu;
    m_Cr=acos(V/m_Cl)+mu;

    //conversion of attributes in degrees (modif en divisions d'angles PCA9685 soit ~200)
    m_Ad=m_Ar*180/PI;
    m_Bd=m_Br*180/PI;
    m_Cd=m_Cr*180/PI;


    return;
}

void Leg::setLengh(float o, float a, float b, float c)
{
    m_Ol=o;
    m_Al=a;
    m_Bl=b;
    m_Cl=c;

    return;
}

void Leg::calcLegStepAccelerate(Point P_b, int div, float h)
{
    m_start=m_actual;
    m_end=P_b;
    m_div=div; //peut-être à mettre au constructeur et généraliser le tout avec un #define

    m_lX=m_end.x-m_start.x;
    m_lY=m_end.y-m_start.y;
    m_lZ=sqrt((m_lX)*(m_lX)+(m_lY)*(m_lY)); //longeur diagonale

    //coef parabole
    m_const_step1=-4*h/(m_lZ*m_lZ); //ax^2
    m_const_step2=4*h/m_lZ; //bx

    //coef K for X
    m_coef_K_X=(m_lX/2)*cbrt((2.0/m_div));
    //coef K for Y
    m_coef_K_Y=(m_lY/2)*cbrt((2.0/m_div));
    //coef K for Z
    m_coef_K_Z=(m_lZ/2)*cbrt((2.0/m_div));

    return;
}

Point Leg::moveLegStepAccelerate(int n) //gérer les arrondis
{
    float p;
    //X
    m_actual.x=m_coef_K_X*cbrt(n-m_div/2)+m_lX/2 + m_start.x;
    //Y
    m_actual.y=m_coef_K_Y*cbrt(n-m_div/2)+m_lY/2 + m_start.y;
    //Z
    p=m_coef_K_Z*cbrt(n-m_div/2)+m_lZ/2;
    m_actual.z=m_const_step1*p*p+m_const_step2*p;

    if(n==m_div) //round
    {
        m_actual.z=round_f5(m_actual.z);
    }

    return m_actual;
}

void Leg::calcLegStepRegular(Point P_b, int div, float h)
{
    m_start=m_actual;
    m_end=P_b;
    m_div=div; //peut-être à mettre au constructeur et généraliser le tout avec un #define

    m_lX=m_end.x-m_start.x;
    m_lY=m_end.y-m_start.y;
    m_lZ=sqrt((m_lX)*(m_lX)+(m_lY)*(m_lY)); //longeur diagonale

    //coef parabole
    m_const_step1=-4*h/(m_lZ*m_lZ);
    m_const_step2=4*h/m_lZ;

    //coefs for X
    m_const_step1X_regular=m_lX*m_lX/(2*m_div);
    m_const_step2X_regular=m_lX*m_lX/4;
    m_const_step3X_regular=m_lX/2;

    //coefs for Y
    m_const_step1Y_regular=m_lY*m_lY/(2*m_div);
    m_const_step2Y_regular=m_lY*m_lY/4;
    m_const_step3Y_regular=m_lY/2;

    //coefs for Z
    m_const_step1Z_regular=m_lZ*m_lZ/(2*m_div);
    m_const_step2Z_regular=m_lZ*m_lZ/4;
    m_const_step3Z_regular=m_lZ/2;

    calcAnglesServos(m_actual);

    return;
}

Point Leg::moveLegStepRegular(int n) //gérer les arrondis
{
    float p;
    if(n<m_div/2)
    {
        m_actual.x=-sqrt(-m_const_step1X_regular*n+m_const_step2X_regular)+m_const_step3X_regular + m_start.x;
        m_actual.y=-sqrt(-m_const_step1Y_regular*n+m_const_step2Y_regular)+m_const_step3Y_regular+ m_start.y;
        p=(-sqrt(-m_const_step1Z_regular*n+m_const_step2Z_regular)+m_const_step3Z_regular);

    }
    else
    {
        m_actual.x=sqrt(m_const_step1X_regular*n-m_const_step2X_regular)+m_const_step3X_regular+ m_start.x;
        m_actual.y=sqrt(m_const_step1Y_regular*n-m_const_step2Y_regular)+m_const_step3Y_regular+ m_start.y;
        p=(sqrt(m_const_step1Z_regular*n-m_const_step2Z_regular)+m_const_step3Z_regular);
    }


    m_actual.z=m_const_step1*p*p+m_const_step2*p;

    if(n==m_div) //round
    {
        m_actual.z=round_f5(m_actual.z);
    }

    calcAnglesServos(m_actual);

    return m_actual;
}


void Leg::calcLegMove(Point P_b, int div)
{
    //transfert of values
    m_start=m_actual;
    m_end=P_b;
    m_div=div;

    //coef calc of move
    m_const_move1=(m_end.x-m_start.x)/m_div;
    m_const_move2=(m_end.y-m_start.y)/m_div;

    //copy of Z position (still the same here)
    m_actual.z=m_start.z;

    return;
}

Point Leg::moveLegMove(int n)
{
    m_actual.x=m_start.x + n*m_const_move1;
    m_actual.y=m_start.y + n*m_const_move2;

    if(n==m_div) //round
    {
        m_actual.z=round_f5(m_actual.z);
    }

    calcAnglesServos(m_actual); //ZE MODIF

    return m_actual;
}

void Leg::printData()
{
    cout << "length of Legs:" <<  endl << "m_Ol: " << m_Ol << endl << "m_Al: " << m_Al << endl << "m_Bl: " << m_Bl << endl << "m_Cl: " << m_Cl << endl << endl; //longueurs
    cout << "absolute angles in rad:" << endl <<  "m_Or: " << m_Or << endl <<  "m_Ar: " << m_Ar << endl << "m_Br: " << m_Br << endl << "m_Cr: " << m_Cr << endl << endl; //angles abs degré
    cout << "absolute angles in degree:" <<  endl << "m_Od: " << m_Od << endl << "m_Ad: " << m_Ad << endl << "m_Bd: " << m_Bd << endl << "m_Cd: " << m_Cd << endl << endl; //angles abs degré
    cout << "point D position:" << endl << "X: " << m_actual.x << endl << "Y: " << m_actual.y << endl << "Z: " << m_actual.z << endl << endl;//position

    return;
}

void Leg::printActual()
{
    cout << "X: " << m_actual.x << endl << "Y: " << m_actual.y << endl << "Z: " << m_actual.z << endl << endl;//position

}

//gets
//length
float Leg::get_Ol()
{
    return m_Ol;
}

float Leg::get_Al()
{
    return m_Al;
}

float Leg::get_Bl()
{
    return m_Bl;
}

float Leg::get_Cl()
{
    return m_Cl;
}

//angles radP_a
float Leg::get_Or()
{
    return m_Or;
}

float Leg::get_Ar()
{
    return m_Ar;
}

float Leg::get_Br()
{
    return m_Br;
}

float Leg::get_Cr()
{
    return m_Cr;
}

//angles degrees
float Leg::get_Od()
{
    return m_Od;
}

float Leg::get_Ad()
{
    return m_Ad;
}

float Leg::get_Bd()
{
    return m_Bd;
}

float Leg::get_Cd()
{
    return m_Cd;
}

float Leg::getActual_X()
{
    return m_actual.x;
}
float Leg::getActual_Y()
{
    return m_actual.y;
}
float Leg::getActual_Z()
{
    return m_actual.z;
}

void Leg::setActual(Point P)
{
    m_actual=P;
    setPosition(P);

    return;
}



