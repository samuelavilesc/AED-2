#include <iostream>
#include <algorithm>
#define N 12
#define C 525
using namespace std;
int metido;
int valor[N]={5,5,20,50,100,200,100,20,50,10,20,100}; //valor monedas
//ejercicio sin podas ni ostias, solo backtracking
void Generar(int nivel, int s[N]){
    s[nivel]++;
    if(s[nivel]>0){
        metido+=valor[nivel];
    }

}
bool Solucion(int nivel, int s[N]){
    return (metido>=C)&&(nivel==N-1);
}
bool Criterio(int nivel, int s[N],int voa){
    return metido<C && nivel<N-1;
}
bool masHermanos(int nivel, int s[N]){
    return s[nivel]<1;
}
void Retroceder(int &nivel, int s[N]){
    metido-=valor[nivel];
    s[nivel]=-1;
    nivel--;
}
int Valor(int s[N]){
    int suma=0;
    for(int i=0;i<N;i++){
        if(s[i]>0) suma+=valor[i];
    }
    return suma;
}
void backtracking(){
    int s[N];
    for(int i = 0; i < N; i++){
        s[i] = -1;
    }
    int voa=1000000; //infinito
    int soa[N];
    metido=0;
    int nivel=1;
    while(nivel!=0){
        Generar(nivel,s);
        if(Solucion(nivel,s)&&metido<voa ){
            voa=metido;
            for(int i=0;i<N;i++){
                soa[i]=s[i]; //soa=s
            }
        }
        if(Criterio(nivel,s,voa)){
            nivel++;
        }
        else{
            while(!masHermanos(nivel,s)&&nivel>0){
                Retroceder(nivel,s);
            }
        }
    }
    cout << "El total de las monedas metidas es: " << voa <<endl;
    for(int i = 0; i < N; i++) {
        if(soa[i] > 0) {
            cout << "Valor moneda " << i << ": ";
            cout << valor[i] << " ,"<<soa[i]<<" unidades."<<endl;;
        }
    }
    cout << endl;


}

int main(){
    
    backtracking();
    
    return 0;
}