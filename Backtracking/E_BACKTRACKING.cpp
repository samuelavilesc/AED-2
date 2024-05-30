#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
  
bool Solucion(int nivel,int m)
{
    if(nivel==m-1)
    {
        return true;
    }
    return false;
}

void generar(int nivel,int solucion[],int n)
{   
    solucion[nivel]=solucion[nivel]+1;
    for (int i=0; i < nivel  ; i++)
    {
        if (solucion[nivel] == solucion[i] || solucion[nivel] < solucion[i] )
        {
            solucion[nivel]=solucion[nivel]+1;
            i--;
        }
        if(solucion[nivel]==n)
        {
            return;
        }
    }
}

int resultado(int solucion[],int m,int **ciudades,int n)
{   int sol=0;
    for(int i=0; i<m;i++)
    {
       for(int j=0;j<m;j++)
       {
           if(solucion[i]!=solucion[j] && solucion[i]<=n &&  solucion[j]<=n ){
                sol=sol+ciudades[solucion[i]-1][solucion[j]-1];
           }
       } 
    }
    return sol;
}

bool masHermanos(int solucion[],int nivel,int n,int m)
{   
    int i = (m-nivel)-1;
    return (solucion[nivel] < n-i);
}

int retroceder(int solucion[],int nivel)
{
    solucion[nivel]=0;
    nivel--;
    return nivel;
}

int backtracking(int **ciudades,int solucion[],int m,int n)
{
    int nivel=0;
    int max=-1;
    //std::vector<std::vector<int>> combinacionesExploradas;
    do{
        generar(nivel,solucion,n);
        if(Solucion(nivel,m)==true)
        {   
            if(resultado(solucion,m,ciudades,n)>max)
            {
                max=resultado(solucion,m,ciudades,n);
            }
        }
        if (nivel<m-1)
        {
            nivel=nivel+1;
        }
        else
        {
            while(!masHermanos(solucion,nivel,n,m) && nivel > -1)
            {
                nivel = retroceder(solucion,nivel);
            }
        }
    } while (nivel!=-1);
    return max;
}

int main()
{

  int num_casos=0;
  int n=0;
  int m=0;
  cin>>num_casos;
  for(int h=0; h<num_casos;h++){
    cin>>n;
    cin>>m;
    int **ciudades=new int*[n];
    for (int i = 0; i < n; ++i)
    {
    ciudades[i] = new int[n];
    }
    int solucion[m];
    for(int i=0; i<m;i++)
    {
        solucion[i]=0;
    }
    for(int i = 0 ; i<n; i++)
    {
        for(int j = 0 ; j<n; j++)
        {
         cin>>ciudades[i][j];
        }
    }
    cout<<backtracking(ciudades,solucion,m,n)<<endl;
  }
}