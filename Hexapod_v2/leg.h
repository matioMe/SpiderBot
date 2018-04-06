#ifndef LEG_H
#define LEG_H

#include <iostream>
#include <math.h>
#include "point.h"

#define PI 3.14159265358979

using namespace std;

class Leg
{
public:
    Leg();
    Leg(float o, float a, float b, float c, Point init, float Od);
    ~Leg();
    void setPosition(Point target);
    void setLengh(float o, float a, float b, float c);
    void setOd(float Od);
    void printData();
    void calcLegStep(Point P_a, Point P_b, int div, float h);
    void calcLegMove(Point P_a, Point P_b, int div);
    Point moveLegStep(int n);
    Point moveLegMove(int n);
    void printActual();
    float getActual_X();
    float getActual_Y();
    float getActual_Z();

    float get_Ol();
    float get_Al();
    float get_Bl();
    float get_Cl();

    float get_Or();
    float get_Ar();
    float get_Br();
    float get_Cr();

    float get_Od();
    float get_Ad();
    float get_Bd();
    float get_Cd();

    float get_As();
    float get_Bs();
    float get_Cs();

    float get_const_a();
    float get_const_b();
    float get_const_c();
    float get_const_d();
    float get_const_e();
    float get_const_f();
    float get_const_g();

private:
    float m_Ol, m_Al, m_Bl, m_Cl; //longueurs
    float m_Or, m_Ar, m_Br, m_Cr; //angles absolus par plans en radians
    float m_Od, m_Ad, m_Bd, m_Cd;  //angles absolus en degrés
    float m_const_step1, m_const_step2, m_const_coef_K; //constantes fonctions déplacement step
    float m_const_move1, m_const_move2; //coef fonction move
    float m_lX, m_lY, m_lZ; //longueur du pas sur le plan X/Y
    float m_coef_K_X, m_coef_K_Y, m_coef_K_Z;
    float m_div; //nb de div

    Point m_point_A; //point A utile à plusieurs endroits dans le code et fixe après construction
    Point m_start; //origine déplacement
    Point m_end; //arrivée
    Point m_actual; //position actuelle

};

#endif //C_ONFILE_H


/*


         z  ^
            |
            |
            |  ^ y
            | /
            |/_________> x



*/
