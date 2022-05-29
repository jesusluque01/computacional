#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <complex>

#define G 6.67e-11
#define Mt 5.9536e24
#define Ml 0.07349e24
#define Dtl 3.844e8

using namespace std;
//para incluir string debe estar antes using namespace
#include <string>

int main (void)
{
float kr1, kr2,kr3, kr4;
float kfi1, kfi2, kfi3, kfi4;
float kpr1, kpr2, kpr3, kpr4;
float kpfi1, kpfi2, kpfi3, kpfi4;
float h, r, fi, Pr, Pfi, delta, t, mu, omega, rprima1;
float rprima2, rprima3, rprima;
int i,j,k;
ofstream fichero;

string nombrefich1;
    


     nombrefich1="cosas.dat";
    fichero.open(nombrefich1.c_str());

    //establecemos las condiciones iniciales
    t=0.0;
    h=1.0;
    r=6.37816e6/Dtl;
    fi=0.0;
    Pr=11.19e3*cos(0.254)/Dtl;
    Pfi=r*11.19e3*sin(0.254)/Dtl;
    omega=2.6617e-6;
    mu=Ml/Mt;
    delta=G*Mt/pow(Dtl,3);


    fichero<<r*cos(fi)<<", "<<r*sin(fi)<<endl;
    fichero<<0.0<<", "<<0.0<<endl;
    fichero<<cos(omega*t)<<", "<<sin(omega*t)<<endl,
    fichero<<endl;
    i=0;

    for(j=0; j<250000; j++)
    {
        //como puede haber dependencias cruzadas calculamos primero los k1
    //luego los k2, etc...
    rprima=sqrt(1+r*r-2*r*cos(fi-omega*t));
    kr1=h*Pr;
    kfi1=h*Pfi/(r*r);
    kpr1=Pfi*Pfi/pow(r,3)-delta*(1.0/(r*r)+mu*(r-cos(fi-omega*t))/pow(rprima,3));
    kpfi1=-h*delta*mu*r/pow(rprima1,3)*sin(fi-omega*t);

    rprima1=sqrt(1+(r+kr1/2)*(r+kr1/2)-2*(r+kr1/2)*cos(fi+kfi1/2-omega*(t+h/2)));
    kr2=h*(Pr+kpr1/2);
    kfi2=h*(Pfi+kpfi1/2)/((r+kr1/2)*(r+kr1/2));
    kpr2=h*(Pfi+kpfi1/2)*(Pfi+kpfi1/2)/pow(r+kr1/2,3)-delta*(1.0/((r+kr1/2)*(r+kr1/2))+mu*((r+kr1/2)-cos(fi+kfi1/2-omega*(t+h/2)))/pow(rprima1,3));
    kpfi2=-h*delta*mu*(r+kr1/2)/pow(rprima1,3)*sin(fi+kfi1/2-omega*(t+h/2));

    rprima2=sqrt(1+(r+kr2/2)*(r+kr2/2)-2*(r+kr2/2)*cos(fi+kfi2/2-omega*(t+h/2)));
    kr3=h*(Pr+kpr2/2);
    kfi3=h*(Pfi+kpfi2/2)/((r+kr2/2)*(r+kr2/2));
    kpr3=h*(Pfi+kpfi2/2)*(Pfi+kpfi2/2)/pow(r+kr2/2,3)-delta*(1.0/((r+kr2/2)*(r+kr2/2))+mu*((r+kr2/2)-cos(fi+kfi2/2-omega*(t+h/2)))/pow(rprima2,3));
    kpfi3=-h*delta*mu*(r+kr2/2)/pow(rprima2,3)*sin(fi+kfi2/2-omega*(t+h/2));

    rprima3=sqrt(1+(r+kr3)*(r+kr3)-2*(r+kr3)*cos(fi+kfi3-omega*(t+h)));
    kr4=h*(Pr+kpr3);
    kfi4=h*(Pfi+kpfi3)/((r+kr3)*(r+kr3));
    kpr4=h*(Pfi+kpfi3)*(Pfi+kpfi3)/pow(r+kr3,3)-delta*(1.0/((r+kr3)*(r+kr3))+mu*((r+kr3)-cos(fi+kfi3-omega*(t+h)))/pow(rprima3,3));
    kpfi4=-h*delta*mu*(r+kr3)/pow(rprima3,3)*sin(fi+kfi3-omega*(t+h));

    //conocidas las k actualizo los parámetros
    r=r+1.0/6.0*(kr1+2*kr2+2*kr3+kr4);
    fi=fi+1.0/6.0*(kfi1+2*kfi2+2*kfi3+kfi4);
    Pr=Pr+1.0/6.0*(kpr1+2*kpr2+2*kpr3+kpr4);
    Pfi=Pfi+1.0/6.0*(kpfi1+2*kpfi2+2*kpfi3+kpfi4);
    t=t+h;

    //sacamos al fichero una vez cada 500 pasos
    if (i==500)
    {
        fichero<<r*cos(fi)<<", "<<r*sin(fi)<<endl;
    fichero<<0.0<<", "<<0.0<<endl;
    fichero<<cos(omega*t)<<", "<<sin(omega*t)<<endl,
    fichero<<endl;
    i=0;

    }
    i=i+1;

    }
    






    fichero.close();
    return 0;
}