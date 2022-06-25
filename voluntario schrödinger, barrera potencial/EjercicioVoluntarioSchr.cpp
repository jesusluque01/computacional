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


double CalcSigma (double vector[100], double promedio);


int main (void)
{
    int N, nciclos, j,l,m, pasos, nd, o, contador, mt, q, ContEsperado;
    double lambda, k,s, V[2000], amplitud, norma2, norma2total, probabilidad, probanterior, XI, coefTr;
    double mediaTotProb, probmedia,Tr[100], TrTOT, probabilidades[100], errorTr, errorProb;
    double esperadoX, esperadoP, esperadoEcin, esperadoEpot, esperadoETOT;
    complex<double> Fi[2000],i,alfa[2000], Xi[2000];
   complex<double> b, beta[2000], momento, energiacin;
    ofstream fichero1, ficheronorma, esperadoXP, fichesperadoEnergia;
    string nombrefich1;
    bool maximo;
    

     srand(time(NULL));
     nombrefich1="coeficienteTransmision.dat";
    fichero1.open(nombrefich1.c_str());
    ficheronorma.open("norma.dat");
    esperadoXP.open("valorEsperadoXP.dat");
    fichesperadoEnergia.open("ValorEsperadoEnergias.dat");

    if(fichero1.is_open())
    cout<<"legolego";

    
        //valores iniciales
    TrTOT=0.0;
    mediaTotProb=0.0;
    mt=0;
    N=2000;
    nciclos=N/8;
    k=2.0*PI*(nciclos*1.0)/(N*1.0);
    s=1.0/(4.0*k*k);
    lambda=0.5;
    i=complex<double>(0.0,1.0);
    cout<<i;
    pasos=-1;
    norma2total=0.0;
    pasos=1; //inicializo a 1 ya que al menos habrá una iteración
    probmedia=0.0;
    maximo=false;
    probabilidad=0.0;
    probanterior=-2.0; //le damos un valor menor que 0 para que no haya error en la primera iteracion

       

    //establezco el potencial, alfa y la funcionde onda inicial
    for(j=0;j<N;j++)
    {
     if (((j>(2*N/5)) && (j<(3*N/5))) )
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


//calculamos la norma
    
    for(l=0;l<N;l++)
    {
        norma2=norm(Fi[l]);
        norma2total=norma2total+norma2;
    }
    

     //algoritmo para encontrar nd
    do
    {
        
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
       
        
    }

    for (j=N*4/5;j<N;j++)
    {
        
        
        norma2=norm(Fi[j]);
         probabilidad=probabilidad+norma2;   
         //es una probabilidad sobre la funcion de onda sin normalizar, pero como solo buscamos
         //encontramor cuando aparece un máximo local nos da igual que no esté dividida por dicho factor
         
    }
    
    ficheronorma<<probabilidad<<endl;
    //comprobamos si es máximo local
    if ((probabilidad>=probanterior))// || (probabilidad<0.15)) //si es mayor que el valor anterior está creciendo. 
    {                                                        //la segunda condición la usamos para no caer en pequeñas
       //fluctuaciones, aunque solo la usamos para lambdas no muy elevados, ya que si no entramos en un ciclo infinito
        //el valor de 0.15 tomado como mínimo es una probabilidad sin normalizar, luego realmente no es un valor tan alto
        probanterior=probabilidad;                              
        probabilidad=0.0;
    }

//cuando pase a ser menor que el anterior es que ha llegado a un maximo local
    else
    {
        maximo=true;
        nd=pasos;
        probabilidad=0.0;
    }
   
    pasos=pasos+1;

    } while (maximo==false);

    cout<<nd<<endl;
    

     
        //genero la función de onda
        for (j=0;j<N;j++)
        {
            Fi[j]=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0))*exp(k*j*1.0*i);
        }


//evolucionamos el sistema nd pasos y cada nd pasos calculamos el coeficiente
    for (o=0; o<nd; o++)
    {
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
       
        
    }
    
    }


    for (m=0;m<N;m++)
    {
         norma2=norm(Fi[m]);
        
        norma2total=norma2total+norma2;
    }

    probabilidad=0.0;
     for (j=N*4/5;j<N;j++)
    {  
        norma2=norm(Fi[j]);
         probabilidad=probabilidad+norma2;     
    }

     probabilidad=probabilidad/norma2total;
     
     for (q=0;q<50;q++)
     {
         mt=0;
         for(pasos=0;pasos<1000;pasos++)
         {
                 XI=rand()/(RAND_MAX*1.0);

         if (XI<probabilidad)
            {
                mt=mt+1;
            }
        
         }
         Tr[q]=mt*1.0/1000.0;
    cout<<Tr[q];
     }
     
    

    cout<<endl;

  

    for (j=0;j<50;j++)
    {
        TrTOT=TrTOT+Tr[j];
    }
    TrTOT=TrTOT/50.0;
    errorTr=sqrt(CalcSigma(Tr,TrTOT)/50.0);
    
    fichero1<<lambda<<"   "<<TrTOT<<"   "<<2*errorTr<<"   "<<probabilidad<<endl;



//calculamos los valores esperados en cada instante, volvemos al punto inicial
 //genero la función de onda
        for (j=0;j<N;j++)
        {
            Fi[j]=exp(-8.0*(4.0*j-N*1.0)*(4.0*j-N*1.0)/(N*N*1.0))*exp(k*j*1.0*i);
        }

    for (ContEsperado=0;ContEsperado<6000;ContEsperado++)
    {
        //inicializamos los valores esparados a 0
        esperadoX=0.0;
        esperadoP=0.0;
        esperadoEcin=0.0;
        esperadoEpot=0.0;
        esperadoETOT=0.0;


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

    
    for(m=0;m<N;m++)
    {
        Fi[m]=Xi[m]-Fi[m];
       
        
    }

    //valor esperado de x en t=ContEsperado+1 ya que 
    //la función de onda ya ha sido actualizada
    for (m=0;m<N;m++)
    {
        norma2=norm(Fi[m]);
        esperadoX=esperadoX+m*norma2/norma2total;
        esperadoEpot=esperadoEpot+V[m]*norma2/norma2total;

    }


    //calculamos el primer término del valor medio del momento y la energía 
    //cinética a parte a través de la derivada numérica hacia delante
    momento=-0.5*i*conj(Fi[0])*(Fi[1]-Fi[0]);
    esperadoP=esperadoP+sqrt(norm(momento))/norma2total;

    energiacin=-1.0*conj(Fi[0])*(Fi[2]+Fi[0]-2.0*Fi[1]);
    esperadoEcin=esperadoEcin+sqrt(norm(energiacin))/norma2total;
    

    for (m=1;m<(N-1);m++)
    {
        momento=-0.5*i*conj(Fi[m])*(Fi[m+1]-Fi[m-1]);
        esperadoP=esperadoP+sqrt(norm(momento))/norma2total;

        energiacin=-1.0*conj(Fi[m])*(Fi[m+1]+Fi[m-1]-2.0*Fi[m]);
        esperadoEcin=esperadoEcin+sqrt(norm(energiacin))/norma2total;
    }

    //calculamos el último término del valor medio del momento y Ecin
    //derivada numérica hacia atrás y segunda derivada numérica hacia atrás
    momento=-0.5*i*conj(Fi[N])*(Fi[N]-Fi[N-1]);
    esperadoP=esperadoP+sqrt(norm(momento))/norma2total;

    energiacin=-1.0*conj(Fi[N])*(Fi[N]+Fi[N-2]-2.0*Fi[N-1]);
    esperadoEcin=esperadoEcin+sqrt(norm(energiacin))/norma2total;
    esperadoETOT=esperadoEcin+esperadoEpot;
    //sacamos a un fichero
    esperadoXP<<ContEsperado+1<<"   "<<esperadoX<<"    "<<esperadoP<<endl;
    fichesperadoEnergia<<ContEsperado+1<<"   "<<esperadoEpot<<"    "<<esperadoEcin<<"  "<<esperadoETOT<<endl;


    }

        
    //cerramos los ficheros
    fichero1.close();
    ficheronorma.close();
    esperadoXP.close();
    fichesperadoEnergia.close();

    return 0;
}


double CalcSigma (double vector[100], double promedio)
{
    int j;
    double sigma;

    sigma=0.0;
    for (j=0;j<50;j++)
    {
       sigma=sigma+(vector[j]-promedio)*(vector[j]-promedio); 
    }
    
    return sigma/50;
}