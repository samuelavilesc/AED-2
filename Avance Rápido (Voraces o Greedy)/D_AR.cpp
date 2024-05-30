#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct beneficio_tiempo
{
    int tiempo;
    int beneficio;
};

bool ordenar(const beneficio_tiempo& p1, const beneficio_tiempo& p2) {
    return p1.beneficio > p2.beneficio;
}

int voraces(int tamano,beneficio_tiempo a[],int num_aviones)
{   
    int salida[tamano];
    bool salidaBool[tamano];
    for(int i = 0; i<tamano; i++)
    {
        salidaBool[i]=false;
        salida[i]=0;
    }
    for (int i = 0; i < num_aviones; i++) {
        int posicion = a[i].tiempo-1;
        if ( posicion >= tamano )
        {
            posicion=tamano-1;
        }
        bool encontrado=false;
        while(posicion>=0 && !encontrado)
        {
            
            if(!salidaBool[posicion])
            {   
                salidaBool[posicion]=true;
                salida[posicion]=a[i].beneficio;
                encontrado=true;
            }
            else
            {
                posicion--;
            }
        }
    }
    int suma=0;
    for(int i = 0; i<tamano;i++)
    {
        suma=suma+salida[i];
    }
    return suma;
}

int main()
{
  int num_casos=0;
  int tamano=0;
  int num_aviones=0;

  cin>>num_casos;
  for(int i = 0 ; i < num_casos; i++)
  { 
    cin>>tamano;
    cin>>num_aviones;
    int beneficios[num_aviones];
    int tiempo[num_aviones];
    beneficio_tiempo a[num_aviones];
    for(int j = 0; j < num_aviones; j++)
    {   
        int x;
        cin>>x;
        tiempo[j]=x;
    }
    for(int j = 0; j < num_aviones; j++)
    {
        int x;
        cin>>x;
        beneficios[j]=x;
    }
    for(int i = 0 ; i< num_aviones;i++)
    {
        beneficio_tiempo ej;
        ej.tiempo=tiempo[i];
        ej.beneficio=beneficios[i];
        a[i]=ej;
    }
    std::sort(a, a+num_aviones, ordenar);
    cout<<voraces(tamano,a,num_aviones)<<endl;
   
  }  
}