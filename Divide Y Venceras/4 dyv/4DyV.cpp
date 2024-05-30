#include <iostream>
#include <math.h>
using namespace std;

class solucion{                                     //Clase para concretar los valores de la solucion
    public:
    int indice;
    int valor;
};

solucion solDirecta(int V[], int n, int inicio, int final){         //           
    solucion sol;
    sol.indice = inicio;
    sol.valor = 0;
    for(int i = inicio; i<final + 1; i++){
        sol.valor = sol.valor + V[i];
    }
    return sol;
}

solucion combinar(solucion sol1,solucion sol2, int V[], int n, int m){
    solucion max;
    if(sol1.valor >= sol2.valor){
        max = sol1;
    }
    else{
        max = sol2;
    }
    for(int i=0; i<n-1; i++){
        if(max.valor < solDirecta(V, n, sol1.indice + i, (m - 1) + i).valor){
                max = solDirecta(V,n, sol1.indice + i,(m - 1) + i);
        }
    }
    return max;
}

solucion divideVenceras(int V[], int n, int m, int inicio, int final){
    if(n <= m){
        return solDirecta(V, n, inicio, final);
    }
    if(n%2 == 0){
        return combinar(divideVenceras(V, n/2, m, inicio, (n/2) - 1), divideVenceras(V, n/2, m, inicio + n/2, n-1), V, n/2, m);
    }
    else{
        return combinar(divideVenceras(V, n/2, m, inicio, (n/2) - 1), divideVenceras(V, (n/2) - 1, m, inicio + n/2, n-1), V, n/2, m);
    }
}

int main()
{
    int n, m;                                                                                   // la n es igual a la longitud de la cadena en este caso de valores
    /*n=10, m=5;                                                                                // m es la longitud maxima de la cadena con el valor mas alto 
    char A[n] = {'a', 'a', 'a', 'b', 'b', 'b', 'f', 'z', 'a', 'z'};*/                           // inicio y final, son el primer valor y ultimo a tener en cuenta para el calculo del valor
                                                                                                // A es el array de characteres y V el array una vez transformado en valores
    n= rand()%100;
    m = rand()%50;
    cout<<"n = "<<n<<" m = "<<m<<endl;
    char leter[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char A[n];                    
    cout<<"A = ";
    for(int i=0; i<n; i++){
        char letra = leter[rand()%26];
        A[i] = letra;
        cout<<A[i]<<" ";
    }
    cout<<endl;
    
    int V[n-1];
    cout<<"V = ";
    for(int i=0; i<n-1; i++){
        V[i] = abs(A[i+1] - A[i]);
        cout<<V[i]<<" ";
    }
    cout<<endl;
    
    solucion sol = divideVenceras(V, n-1, m-1, 0, n-2);
    sol.indice = sol.indice + 1;
    cout<<"solucion: i = "<<sol.indice<< " v = "<<sol.valor;
    
    return 0;
} 