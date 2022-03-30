#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//para incluir string debe estar antes using namespace
#include <string>

 void reescalar (float m[9], float r[9][2], float v[9][2]);
void aceleracion (float m[9],float r[9][2],float a[9][2]);
void lecturadatos (float m[9],float r[9][2],float v[9][2]);



#define G 6.67e-11
#define MS 1.989e30
#define C 1.49e11




int main (void)
{
    ofstream fichero1, fichero2, fichero3;
    ifstream datos;
    double t, Tmax, h;
    int n,i,j,k,l,d,f, contador;
    int n,i,j,k,l,d,f;
    float a[9][2], v[9][2], r[9][2], anuevo[9][2], w[9][2];
    float m[9], T[9];
    float E, modulo, modV;
    string nombrefich1, nombrefich2, nombrefich3;
    bool periodo, encontrado[9], semiT[9];


    //establezco los nombres de los ficheros en los que mostraremos los resultados
    nombrefich1="datos.txt";
    nombrefich2="energia.txt";
    nombrefich3="periodos.txt";
    fichero1.open(nombrefich1.c_str());
    fichero2.open(nombrefich2.c_str());
    fichero3.open(nombrefich3.c_str());


    //establezco el tiempo límite y el paso
    Tmax=1500;
    Tmax=10000;
    h=0.01;
    t=0.0;

    //leemos los valores iniciales, los reescalamos 
    //y obtenemos la acel inicial
    lecturadatos (m,r,v);
    reescalar (m,r,v);
    aceleracion (m,r,a);
    cout<< r[3][1]<< v[1][1];

    
    //Inicializo las variables necesarias para calcular los periodos
    periodo=false;
    for (n=0;n<9;n++)
    {
        T[n]=0.0;
        semiT[n]=false;
        encontrado[n]=false;
    }
    //inicializo el contador para mostrar datos
    contador=0;
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
   
    //actualizamos la velocidad
    for (j=0;j<9;j++)
    {
         v[j][0]=w[j][0]+h*0.5*a[j][0];
         v[j][1]=w[j][1]+h*0.5*a[j][1];
    }

    //calculamos la energía
    E=0;
    for (f=1; f<9; f++)
    {   
        modulo=sqrt((r[0][0]-r[f][0])*(r[0][0]-r[f][0])+(r[0][1]-r[f][1])*(r[0][1]-r[f][1]));
        modV=sqrt((v[f][0])*v[f][0])+(v[f][1])*(v[f][1]);
        E=E+(m[0]*m[f]/modulo+0.5*m[f]*modV*modV);
    }
    //pasamos los resultados a un fichero una vez caca X iteraciones
    if (contador==50)
    {
        for (l=0;l<9;l++)
    {
        E=(m[0]*m[f]/modulo+0.5*m[f]*modV*modV);
    }
    //pasamos los resultados a un fichero
    for (l=0;l<9;l++)
     {
         fichero1 << r[l][0]<<", "<<r[l][1]<<endl;
         
     }
    
        

        fichero1<<endl;
        contador=0;
    }
    //sacamos la energia
    fichero2 << E <<" "<< t <<endl;
    //Calculamos el periodo
    //comprobamos que no se tenga ya el valor de los periodos
    if (periodo==false)
    {
        /*Buscamos obtener todos los periodos por lo que utilizamos un for
        para trabajar con todos uno a uno. Buscamos comprobar que el planeta en cuestión
        no haya vuelto a cruzar al eje x positivo, para lo cual comprobamos cuando cruza
        al eje x en la parte negativa, añadiendo que ha pasado una iteración mientras esto no ocurra.
        Luego reptimos el proceso una vez cruza la parte negativa hasta que vuelve a cruzar pero por 
        la positiva */
        for (k=1;k<9;k++)
            {
                if ((r[k][1]>0.0) && (semiT[k]==false))
                {
                T[k]=T[k]+1.0;
                
                }

                else if (((r[k][1]<0.0) && (encontrado[k]==false)))
                {
                T[k]=T[k]+1.0;
                semiT[k]=true;
                }

                else if ((r[k][1]>0.0) && (semiT[k]==true))
                {
                encontrado[k]=true;
                }

            }

            if (encontrado[5]==true && encontrado[6]==true && encontrado[7]==true && encontrado[8]==true && encontrado[9]==true)
            {
                periodo=true;
            }
    }
    

    t=t+h;
    contador=contador+1;
        
    } while (t<=Tmax);

    for (d=0;d<9;d++)
    {
        fichero3 << T[d]*h*sqrt(C*C*C/(G*MS))/(3600*24)<<endl;
    }
    cout << T[3]*h*sqrt(C*C*C/(G*MS))/(3600*24);
    fichero1.close();
    fichero2.close();
    fichero3.close();
    cin>>n;





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
       sumax=sumax-m[j]*(r[i][0]-r[j][0])*(pow(modu,-3));
       sumay=sumay-m[j]*(r[i][1]-r[j][1])*(pow(modu,-3));
       }
       else 
       {
           sumax=sumax;
           sumay=sumay;
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
 void reescalar (float m[9], float r[9][2], float v [9][2])
 {
     int i, j, k;

     

     for (j=0; j<9; j++)
     {
         for (i=0; i<=1; i++)
         {
             r[j][i]=r[j][i]/C;
             v[j][i]=v[j][i]*sqrt(C/(G*MS));
         }
     }

    for (k=0; k<9; k++)
    {
        m[k]=m[k]/MS;
    }

     return;
 }


 

 













