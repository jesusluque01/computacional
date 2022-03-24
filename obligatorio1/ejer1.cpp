#include <iostream>
#include <cmath>
#include <fstream>
void aceleracion (float m[9], float r[9][2], float a[9][2]);
void lecturadatos (float m[9],float r[9][2],float v[9][2]);


#define h 0.1
using namespace std;
int main (void)
{
    ofstream fichero;
    ifstream datos;
    double t;
    int n;
    float a[9][2], v[9][2], r[9][2];
    float m[9];

    lecturadatos (m,r,v);
    cout << m[4];
    cout << r[2][1];
    cout << v[3][1];
    cin >> n;



    return 0;
}

void aceleracion (float m[9], float r[9][2], float a[9][2])
{
 float sumax,sumay, modu;
 int i, j;

 // calculo la aceleración
 for (i=0; i<9; i++)
  sumax=0.0;
  sumay=0.0;
    for (j=0; j<9; j++)
    {
       if (j!=i)
       /*calculo el módulo de la diferencia de posiciones
       denominador de la expresión*/
       modu=sqrt((r[i][0]-r[j][0])*(r[i][0]-r[j][0])+(r[i][1]-r[j][1])*(r[i][1]-r[j][1]));
       sumax=sumax-m[j]*(r[i][0]-r[j][0])/(pow(modu,3));
       sumay=sumay-m[j]*(r[i][1]-r[j][1])/(pow(modu,3));

    }
  a[i][0]=sumax;
  a[i][1]=sumay;
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
    while (!datos.eof() && k<9)
    {
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
        l++;
    }


    datos.close();
    return;
}
