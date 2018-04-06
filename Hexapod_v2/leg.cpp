#include "leg.h"

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

  m_point_A.set_XYZ(m_Ol*cos(m_Or), m_Ol*sin(m_Or), 0);

  setPosition(init);
}

Leg::~Leg()
{
    setLengh(1,1,1,1);
    setOd(0);
}

void Leg::setOd(float Od)
{
  m_Od=Od;
  m_point_A.set_XYZ(m_Ol*cos(m_Or), m_Ol*sin(m_Or), 0);

  return;
}

void Leg::setPosition(Point target) //Point target //m_actual
{
    //transposition des positions
    m_actual.copy(target);

    float e, U, X, Y, xA, yA, l;

    //calc position of A point in x/z plan
    xA=m_point_A.get_X();
    yA=m_point_A.get_Y();

    //calc length leg on x/y plan with pythagore
    l=sqrt((m_actual.get_X()-xA)*(m_actual.get_X()-xA)+(m_actual.get_Y()-yA)*(m_actual.get_Y()-yA));

    //A angle in x/y plan
    m_Ar=acos((m_actual.get_X()-xA)/l);

    //calc of the [BD] length in local u/v plan
    e=sqrt((l-m_Al)*(l-m_Al)+m_actual.get_Y()*m_actual.get_Y());

    //angle of [BD] in u/v plan
    U=acos((l-m_Al)/e);

    //intermediate values for last angles calc
    Y=(m_Cl*m_Cl+e*e-m_Bl*m_Bl)/(2*e);
    X=e-Y;

    //final angles calc
    m_Br=acos(X/m_Bl)+U;
    m_Cr=acos(X/m_Cl)-U;

    //conversion of attributes in degrees
    m_Ad=m_Ar*180/PI;
    m_Bd=m_Br*180/PI;
    m_Cd=m_Cr*180/PI;

    /* à supprimer
    //calc angles servos
    m_As=m_Ar+m_Or;
    m_Bs=m_Br+PI/4;
    m_Cs=m_Br+m_Cr-PI/2;
    */

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

void Leg::calcLegStep(Point P_a, Point P_b, int div, float h)
{
    m_start.copy(P_a);
    m_end.copy(P_b);
    m_div=div; //peut-être à mettre au constructeur et généraliser le tout avec un #define

    m_lX=m_end.get_X()-m_start.get_X();
    m_lY=m_end.get_Y()-m_start.get_Y();
    m_lZ=sqrt((m_lX)*(m_lX)+(m_lY)*(m_lY));

    //coef parabole
    m_const_step1=-4*h/(m_lZ*m_lZ);
    m_const_step2=4*h/m_lZ;

    //coef K for X
    m_coef_K_X=(m_lX/2)*cbrt((2.0/m_div));
    //coef K for Y
    m_coef_K_Y=(m_lY/2)*cbrt((2.0/m_div));
    //coef K for Z
    m_coef_K_Z=(m_lZ/2)*cbrt((2.0/m_div));

    return;
}

void Leg::calcLegMove(Point P_a, Point P_b, int div)
{
    //div X, Y
    float xA, xB, yA, yB;

    xA=P_a.get_X();
    yA=P_b.get_Y();
    xB=P_a.get_X();
    yB=P_b.get_Y();

    m_start=P_a;
    m_end=P_b;
    m_lZ=sqrt((xB-xA)*(xB-xA)+(yB-yA)*(yB-yA));
    m_div=div;
    m_const_move1=(xB-xA)/m_div; //X
    m_const_move2=(yB-yA)/m_div; //Y

    return;
}

Point Leg::moveLegStep(int n) //gérer les arrondis
{
    float p;
    //X
    m_actual.set_X(m_coef_K_X*cbrt(n-m_div/2)+m_lX/2 + m_start.get_X());
    //Y
    m_actual.set_Y(m_coef_K_Y*cbrt(n-m_div/2)+m_lY/2 + m_start.get_Y());
    //Z
    p=m_coef_K_Z*cbrt(n-m_div/2)+m_lZ/2;
    m_actual.set_Z(m_const_step1*p*p+m_const_step2*p);

    //ajouter mouvement avec raspberry.cpp ?
    return m_actual;
}

Point Leg::moveLegMove(int n)
{
    return m_actual;
}

void Leg::printData()
{
    cout << "length of Legs:" <<  endl << "m_Ol: " << m_Ol << endl << "m_Al: " << m_Al << endl << "m_Bl: " << m_Bl << endl << "m_Cl: " << m_Cl << endl << endl; //longueurs
    cout << "absolute angles in rad:" << endl <<  "m_Or: " << m_Or << endl <<  "m_Ar: " << m_Ar << endl << "m_Br: " << m_Br << endl << "m_Cr: " << m_Cr << endl << endl; //angles abs degré
    cout << "absolute angles in degree:" <<  endl << "m_Od: " << m_Od << endl << "m_Ad: " << m_Ad << endl << "m_Bd: " << m_Bd << endl << "m_Cd: " << m_Cd << endl << endl; //angles abs degré
    cout << "point D position:" << endl << "X: " << m_actual.get_X() << endl << "Y: " << m_actual.get_Y() << endl << "Z: " << m_actual.get_Z() << endl << endl;//position

    return;
}

void Leg::printActual()
{
    cout << "X: " << m_actual.get_X() << endl << "Y: " << m_actual.get_Y() << endl << "Z: " << m_actual.get_Z() << endl << endl;//position

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

//angles rad
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
    return m_actual.get_X();
}
float Leg::getActual_Y()
{
    return m_actual.get_Y();
}
float Leg::getActual_Z()
{
    return m_actual.get_Z();
}





