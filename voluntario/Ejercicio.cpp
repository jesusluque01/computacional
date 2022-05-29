#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>


using namespace std;
//para incluir string debe estar antes using namespace
#include <string>
//cabeceras de las funciones
float CalcMn (int S[][200], int Z);
float CalcE (int S[][200], int Z);
float CalcFi (int S[][200], int Z, int posicion);
float CalcSigma (float vector[10000], float promedio);
float CalcSigMatriz (float vector[128][10000], float promedio, int p);
float CalcSigmaVec2 (float vector[10000], float promedio);


int main (void)
{
    int i,j,n,m,Z,l,o,q,k,PASOS, posicion, contador, otrocontador, temp;
    float T,p,deltaE, XI;
    float Mn[10000], MnTOT, Energia[10000], Emed,E2med, ETOT, Cn[10000], CnTOT,FiTOT[128];
    float ErMn, ErEnergia, ErFi[128], ErCn, ErEner2, Fi;
    //float FunCo[40][10000];
     
    int  S[200][200];
    ofstream ficheroMag,ficheroEner, ficheroCalor, ficheroCorrel[10];
    string nombrefich1, nombre2, nombre3, nombre4[10];


    nombrefich1="MagnetizacionN16.dat";
    nombre2="EnergiaN16.dat";
    nombre3="CalorEspecificoN16.dat";
    for (k=0;k<10;k++)
    {
        nombre4[k]='a'+k;
    }
    
    ficheroMag.open(nombrefich1.c_str());
    ficheroEner.open(nombre2.c_str());
    ficheroCalor.open(nombre3.c_str());
    for (i=0;i<10;i++)
    {
        ficheroCorrel[i].open(nombre4[i].c_str());
    }
    


    //establecemos el rango de la matriz, la temperatura, el nº de
    //pasos montecarlo 
    Z=16;
    T=1.5;
    PASOS=1E6;
    
    //realizamos todo el proceso para temperaturas entre 1.5 y 3.5
    //pasos de 2/9 en la temperatura
    for (temp=0; temp<10; temp++)
    {
        //actualizamos la temperatura
        T=T+0.22222222*temp;
            //inicializo los valores promedio a calcular

    MnTOT=0.0;
    ETOT=0.0;
    CnTOT=0.0;
    Emed=0.0;
    E2med=0.0; //energia al cuadrado
    for (i=0;i<Z;i++)
    {
      FiTOT[i]=0.0;  
    }
    contador=0;
    otrocontador=0;
     srand(time(NULL));
 
    
    
        //inicializo a una configuración ordenada
        for (i=0;i<Z;i++)
        {
            for (j=0;j<Z;j++)
            S[i][j]=1;
        }
    
     
        

    for (q=0;q<PASOS;q++)
    {
        //algoritmo
        for (o=0;o<(Z*Z);o++)
    {
        
        n=rand()%Z;
        m=rand()%Z;
       
    //calculamos p considerando las condiciones periódicas
      if (n!=0 && n!=(Z-1) && m!=0 && m!=(Z-1))
      {
          deltaE=2*S[n][m]*(S[n+1][m]+S[n-1][m]+S[n][m+1]+S[n][m-1]);
      }
        
     else
     {
        deltaE=2*S[n][m]*(S[(n+1)%Z][m]+S[(n-1+Z)%Z][m]+S[n][(m+1)%Z]+S[n][(m-1+Z)%Z]);
     }
         

        p=exp(-deltaE/T);
        if (p>1)
        {
            p=1.0;
        }

        XI=rand()/(RAND_MAX*1.0);
        if(XI<p)
        {
            S[n][m]=-S[n][m];
        }
    

    }
   
    

    if (contador==99)
    {
        //calculamos los parámetros de interés una vez cada 100 pasos
     Mn[otrocontador]=CalcMn(S,Z);    
     Energia[otrocontador]=CalcE(S,Z);
     Cn[otrocontador]=Energia[otrocontador]*Energia[otrocontador];
     
     for(l=0;l<Z;l++)
     {
         
        
            //FunCo[l][otrocontador]=CalcFi(S,Z,l);
            Fi=CalcFi(S,Z,l);
            FiTOT[l]=FiTOT[l]+Fi;
         
         
         
     }
     
    //actualizo el valor de los promedios
    MnTOT=MnTOT+Mn[otrocontador];
    Emed=Emed+Energia[otrocontador];
    E2med=E2med+Cn[otrocontador];
    
    //devuelvo el valor del contador a 0 (pongo -1 ya que inmediatanmente después va a subir a 0)
    contador=-1;
    otrocontador=otrocontador+1;
    } 

    contador=contador+1;     
   
    }
    
    //Calculamos las medias
    Emed=Emed/(PASOS/100);
    MnTOT=MnTOT/(PASOS/100);
    ETOT=Emed/(2*Z*Z);
    E2med=E2med/(PASOS/100);
    CnTOT=(E2med-Emed*Emed)/(Z*Z*T);
    for (k=0;k<Z;k++)
    {
        FiTOT[k]=FiTOT[k]/(Z*Z*(PASOS/100));
    }
    
    //calculamos los errores
    ErMn=sqrt(CalcSigma(Mn,MnTOT)/10000);
    ErEnergia=sqrt(CalcSigma(Energia,ETOT)/10000)/(2*Z*Z);
    ErEner2=sqrt(CalcSigmaVec2(Energia,E2med)/10000);
    //ErCn=sqrt(ErEner2*ErEner2+4*ErEnergia*ErEnergia)/(Z*Z*T);
    
    ficheroMag<<T<<"   "<<MnTOT<<"   "<<ErMn<<endl;
    ficheroEner<<T<<"   "<<ETOT<<"   "<<ErEnergia<<endl;
    ficheroCalor<<T<<"   "<<CnTOT<<endl;
    
    for (j=0;j<Z;j++)
    {
        ficheroCorrel[temp]<<j<<"   "<<FiTOT[j]<<endl;
        //ErFi[j]=sqrt(CalcSigMatriz(FunCo,FiTOT[j],j)/10000)/(Z*Z);
        //ficheroCorrel[temp]<<ErFi[j]<<"   ";
        //ficheroCorrel[temp]<<endl;
    }
    

    }


    
   
    ficheroMag.close();
    ficheroEner.close();
    ficheroCalor.close();
    for (j=0;j<10;j++)
    {
        ficheroCorrel[j].close();
    }
    
    return 0;
}


float CalcMn (int S[][200], int Z)
{
    int i, j;
    float Mn;
     //calculo Mn
    Mn=0.0;
    for (i=0;i<Z;i++)
    {
        for (j=0;j<Z;j++)
        {
            Mn=Mn+S[i][j];
        }
    }
    Mn=abs(Mn)/(Z*Z);

    return Mn;
}

float CalcE (int S[][200], int Z)
{
    int n, m;
    float E;

    E=0.0;

    for (n=0;n<Z;n++)
    {
        for (m=0;m<Z;m++)
        {
             if (n!=0 && n!=(Z-1) && m!=0 && m!=(Z-1))
            {
                E=E+S[n][m]*(S[n+1][m]+S[n-1][m]+S[n][m+1]+S[n][m-1]);
            }
        
            else
            {
                E=E+S[n][m]*(S[(n+1)%Z][m]+S[(n-1+Z)%Z][m]+S[n][(m+1)%Z]+S[n][(m-1+Z)%Z]);
            }
            
        }
    }
    E=-0.5*E;

    return E;
}

float CalcFi (int S[][200], int Z, int posicion)
{
     int i, j;
    float Fi;
     //calculo Fi
    Fi=0.0;
    for (i=0;i<Z;i++)
    {
        for (j=0;j<Z;j++)
        {
            Fi=Fi+S[i][j]*S[i+posicion][j];
        }
    }

    return Fi;
}

float CalcSigma (float vector[10000], float promedio)
{
    int j;
    float sigma;

    sigma=0.0;
    for (j=0;j<10000;j++)
    {
       sigma=sigma+(vector[j]-promedio)*(vector[j]-promedio); 
    }
    
    return sigma/10000;
}

// para poder calcular las cosas sin que pete, como este error suda lo comento
/*
float CalcSigMatriz (float vector[128][10000], float promedio, int p)
{
     int j;
    float sigma;

    sigma=0.0;
    for (j=0;j<10000;j++)
    {
       sigma=sigma+(vector[p][j]-promedio)*(vector[p][j]-promedio); 
    }
    
    return sigma/10000;
}
*/

float CalcSigmaVec2 (float vector[10000], float promedio)
{
    int j;
    float sigma;

    sigma=0.0;
    for (j=0;j<10000;j++)
    {
       sigma=sigma+(vector[j]*vector[j]-promedio)*(vector[j]*vector[j]-promedio); 
    }
    
    return sigma/10000;
}