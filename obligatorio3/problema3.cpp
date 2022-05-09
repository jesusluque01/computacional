#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <complex>

#define PI 3.14159

using namespace std;
//para incluir string debe estar antes using namespace
#include <string>

int main (void)
{
    int N, nciclos, j,l,m, pasos;
    double lambda, k,s, V[1000], amplitud, norma2, norma2total;
    complex<double> Fi[1000],i,alfa[1000], Xi[1000];
   complex<double> b, beta[1000];
    ofstream fichero1, ficheronorma;
    string nombrefich1;
    


     nombrefich1="cosas.dat";
    fichero1.open(nombrefich1.c_str());
    ficheronorma.open("norma.dat");
    if(fichero1.is_open())
    cout<<"legolego";

    //valores iniciales
    N=200;
    nciclos=N/8;
    k=2.0*PI*(nciclos*1.0)/(N*1.0);
    s=1.0/(4.0*k*k);
    lambda=1.0;
    i=complex<double>(0.0,1.0);
    cout<<i;
    pasos=-1;
    norma2total=0.0;

    //establezco el potencial, alfa y la funcionde onda inicial
    for(j=0;j<N;j++)
    {
     if ((j>(2*N/5)) && (j<(3*N/5)))
     V[j]=lambda*k*k;
     else
     V[j]=0.0;


     Fi[j]=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0))*exp(k*j*1.0*i);


    }

    Fi[0]=0.0+0.0i;
    Fi[N-1]=0.0+0.0i;

    alfa[N-2]=0.0;
    for (j=(N-3);j>=0;j--)
    {
        alfa[j]=-1.0/(-2.0+2.0*i/s-V[j+1]+1.0*alfa[j+1]);
        
    }



    //paso la función de onda al fichero
     if(fichero1.is_open())
    cout<<"legolego";
    for(l=0;l<N;l++)
    {
        norma2=norm(Fi[l]);
        fichero1<<l<<", " << norma2<<", "<<V[l] <<endl;
        norma2total=norma2total+norma2;
    }
    fichero1<<endl;
    ficheronorma<<pasos<<", "<<norma2total/22.1157<<endl;


    //algoritmo
    for(pasos=0;pasos<1000;pasos++)
    {
        //un for o un algo (CUAL ES LA CONDICION??)
    //calculo beta
    beta[N-2]=0.0;
    for(j=(N-3);j>=0;j--)
    {
        b=4.0*i*Fi[j+1]/s;
        beta[j]=(b-beta[j+1])/(-2.0+2.0*i/s-V[j+1]+1.0*alfa[j+1]);
    }

   Xi[0]=0.0+0.0i;

    for (l=1;l<N;l++)
    {
        Xi[l]=alfa[l-1]*Xi[l-1]+beta[l-1];
    }

    norma2total=0.0;
    for(m=0;m<N;m++)
    {
        Fi[m]=Xi[m]-Fi[m];
        norma2=norm(Fi[m]);
        fichero1<<m<<", "<<norma2<<", "<<V[m]<<endl;
        norma2total=norma2total+norma2;
    }
    fichero1<<endl;
    ficheronorma<<pasos<<", "<<norma2total/22.1557<<endl;

    }
    

    fichero1.close();

    return 0;
}
