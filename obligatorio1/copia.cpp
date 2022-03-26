#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//para incluir string debe estar antes using namespace
#include <string>

 void reescalar (double& Tmax, double& h,float m[9], float r[9][2]);
void aceleracion (float m[9],float r[9][2],float a[9][2]);
void lecturadatos (float m[9],float r[9][2],float v[9][2]);

void copiar (float a[9][2], string nombre);

#define G 4.0
#define MS 4.0
#define C 4.0




int main (void)
{
    ofstream fichero1, fichero2;
    ifstream datos;
    double t, Tmax, h;
    int n,i,j,l;
    float a[9][2], v[9][2], r[9][2], anuevo[9][2], w[9][2];
    float m[9];
    string nombrefich1, nombrefich2;


    //establezco los nombres de los ficheros en los que mostraremos los resultados
    nombrefich1="datos.txt";
    nombrefich2="energia.txt";
    fichero1.open(nombrefich1.c_str());
    fichero2.open(nombrefich2.c_str());


    //establezco el tiempo límite y el paso
    Tmax=8.0;
    h=1.0;
    t=0.0;

    //leemos los valores iniciales, los reescalamos 
    //y obtenemos la acel inicial
    lecturadatos (m,r,v);
    reescalar (Tmax,h,m,r);
    aceleracion (m,r,a);

    //Algoritmo de verlet
    
    
    do
    {
        for (i=0;i<9;i++)
    {
         //obtenemos la componente i,x e i,y de w
    w[i][0]=v[i][0]+0.5*h*a[i][0];
    w[i][1]=v[i][1]+0.5*h*a[i][1];
        //calculamos las nuevas posiciones
    r[i][0]=r[i][0]+h*w[i][0];
    r[i][1]=r[i][1]+h*w[i][1];
    }
       //actualizamos la aceleracion
    aceleracion (m,r,a);
    cout<< a[0][0]<<a[0][1];
    //actualizamos la velocidad
    for (j=0;j<9;j++)
    {
         v[j][0]=w[j][0]+h*0.5*a[j][0];
         v[j][1]=w[j][1]+h*0.5*a[j][0];
    }

    //pasamos los resultados a un fichero
    for (l=0;l<9;l++)
     {
         fichero1 << a[l][0]<<", "<<a[l][1]<<endl;
         fichero2 << v[l][0]<<", "<<v[l][1]<<endl;
     }
    
   


    t=t+h;
        
    } while (t<=Tmax);
    
    
    fichero1.close();
    fichero2.close();
    cin >> n;





    return 0;
}

void aceleracion (float m[9],float r[9][2],float a[9][2])
{
    float sumax,sumay, modu;
 int i, j;

 // calculo la aceleración
 for (i=0; i<9; i++)
 {
     sumax=0.0;
     sumay=0.0;
    for (j=0; j<9; j++)
    {
       if (j!=i)
       {
           /*calculo el módulo de la diferencia de posiciones
       denominador de la expresión*/
       modu=sqrt((r[i][0]-r[j][0])*(r[i][0]-r[j][0])+(r[i][1]-r[j][1])*(r[i][1]-r[j][1]));
       sumax=sumax-m[j]*(r[i][0]-r[j][0])/(pow(modu,3));
       sumay=sumay-m[j]*(r[i][1]-r[j][1])/(pow(modu,3));
       }
       

    }
        a[i][0]=sumax;
         a[i][1]=sumay;

 }
 return;
}

 //función para leer los valores iniciales
void lecturadatos (float m[9],float r[9][2],float v[9][2])
{
    ifstream datos;
    int k,l,n;
    k=0;
    l=0;
    n=0;
    datos.open("valoresiniciales.txt");
    // la estructura del fichero debe ser masa, posición x,y y velocidad x,y

    while (!datos.eof() && k<9)
    {
        /*leemos las masas mediante un bucle, comprobando que el
            fichero no acaba y que no se supera el límite del vector,aumentando en cada interación el valor
            del elemento del vector, siempre por debajo del tamaño de este*/
        datos >> m[k];
        k++;
    }
    while (!datos.eof() && l<9)
    {
        datos >> r[l][0];
        datos >> r[l][1];
        l++;
    }
    while (!datos.eof() && n<9)
    {
        datos >> v[n][0];
        datos >> v[n][1];
        n++;
    }

//añadir la lectura de la velocidad
    datos.close();
    return;
}


/* los cálculos que realizados se basan en expresiones
cuyas magnitudes están reescaladas*/
 void reescalar (double& Tmax, double& h, float m[9], float r[9][2])
 {
     int i, j, k;

     Tmax=Tmax*sqrt(G*MS/(C*C*C));
     h=h*sqrt(G*MS/(C*C*C));

     for (j=0; j<9; j++)
     {
         for (i=0; i<=1; i++)
         {
             r[j][i]=r[j][i]/C;
         }
     }

    for (k=0; k<9; k++)
    {
        m[k]=m[k]/MS;
    }

     return;
 }


 void copiar (float a[9][2], string nombre)
 {
     int i;
     ofstream fichero;

     

     

     
     
    return;
 }


