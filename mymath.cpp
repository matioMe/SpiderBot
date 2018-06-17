#include "mymath.h"


float round_f(float nb, float nb_dec)
{
    float coef;
    float nbFinal;

    coef=pow(10.0, nb_dec);

    nb=nb*coef;
    nbFinal=floor(nb);

    if(nb+0.5>=nbFinal+1) nbFinal=nbFinal+1;

    nbFinal=nbFinal/coef;

    return nbFinal;
}


float round_f5(float nb)
{
    float nbFinal=nb;

    nb=nb*10000;
    nbFinal=floor(nb);

    if(nb+0.5>=nbFinal+1) nbFinal=nbFinal+1;

    nbFinal=nbFinal/10000;

    return nbFinal;
}
