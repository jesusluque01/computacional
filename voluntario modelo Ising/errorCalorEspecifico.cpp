#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

int main ()
{
    int k,N,j;
    double T,energia, energia2, Cv[10000], CvTOT,sigma;
    ofstream gaussiana;
    string nombre;
    std:: default_random_engine generator;
    std:: default_random_engine generator2;
    std :: normal_distribution<double> distribution (-0.9753,4.9849); //se indica primero el valor medio y luego su varianza
    std :: normal_distribution<double> laotra (2494,1550.91);
    nombre="gaussianaCv.dat";
    gaussiana.open(nombre.c_str());
    N=64;
    T=1.5;
    CvTOT=0.0;
    for (k=0;k<10000;k++)
    {
        energia=distribution(generator);
        energia2=laotra(generator2);
        Cv[k]=(energia*energia-energia2)/(N*N*T);
        CvTOT=CvTOT+Cv[k];
    }
    CvTOT=CvTOT/10000.0;

     sigma=0.0;
    for (j=0;j<10000;j++)
    {
       sigma=sigma+(Cv[j]-CvTOT)*(Cv[j]-CvTOT); 
    }
    sigma =sqrt(sigma)/10000.0;
    cout<<CvTOT<<"; "<<sigma;
    gaussiana.close();
    return 0;
}