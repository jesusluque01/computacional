#include <iostream>
#include <cmath>
#include <fstream>
#include<stdlib.h>
#include<time.h>


using namespace std;
//para incluir string debe estar antes using namespace
#include <string>
int main (void)
{
    
    float T,p,deltaE, XI;
    int i,j,n,m,Z,l,o,q,k; 
    int  S[200][200];
    ofstream fichero1, fichero4;
    string nombrefich1;
    bool ordenada;

    nombrefich1="ising_data.dat";
    fichero1.open(nombrefich1.c_str());
    //establecemos el rango de la matriz, la temperatura y si queremos una configuración
    //inicial ordenada o no
    Z=64;
    T=0.2;
    ordenada=true;

    if (ordenada==true)
    {
        //inicializo a una configuración ordenada
        for (i=0;i<Z;i++)
        {
            for (j=0;j<Z;j++)
            S[i][j]=1;
        }
    }
    
     
    else 
    {
        for (i=0;i<Z;i++)
     {
         for (j=0;j<Z;j++)
         {
             k=rand()%2;
            if (k==0)
                S[i][j]=-1;
            else
                S[i][j]=k;
         }
         
     }
    }
     
     //paso la matriz al fichero
    for (l=0;l<Z;l++)
     {
         for(j=0;j<Z;j++)
         {
             if (j!=(Z-1))
             fichero1 << S[l][j]<<", ";
             else
              fichero1 << S[l][j]<<endl;
         }
         
         
         
     }

        fichero1<<endl;
         srand(time(NULL));



    for (q=0;q<200;q++)
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
        deltaE=2*S[n][m]*(S[(n+1)%Z][m]+S[(n-1)%Z][m]+S[n][(m+1)%Z]+S[n][(m-1)%Z]);
     }
         

        p=exp(-deltaE/T);
        if (p>1)
        {
            p=1.0;
        }

        XI=(rand()%Z)/(Z*1.0);
        if(XI<p)
        {
            S[n][m]=-S[n][m];
        }
    

    }
   
    //paso la matriz al fichero
    for (l=0;l<Z;l++)
     {
         for(j=0;j<Z;j++)
         {
             if (j!=(Z-1))
             fichero1 << S[l][j]<<", ";
             else
              fichero1 << S[l][j]<<endl;
         }
         
         
         
     }

        fichero1<<endl;
        
    }
    

    
    cout<< XI;
    fichero1.close();
    return 0;
}