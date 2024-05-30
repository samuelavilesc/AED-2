#include <iostream>
#include <algorithm>
#define N 12
#define presupuesto 1
using namespace std;
int gastado;
int P[N]={1,2,4,8,16,32,7,8,9,10,12,6}; //precios
void Generar(int nivel, int s[N]){
    s[nivel]++;
    if(s[nivel]!=0){
        gastado+=P[nivel];
    }

}
bool Solucion(int nivel, int s[N]){
    return (gastado<=presupuesto)&&(nivel==N-1);
}
bool Criterio(int nivel, int s[N]){
    return gastado<=presupuesto &&nivel<N-1;
}
bool masHermanos(int nivel, int s[N]){
    return s[nivel]<3;
}
void Retroceder(int &nivel, int s[N]){
    gastado-=s[nivel]*P[nivel];
    s[nivel]=-1;
    nivel--;
}
void backtracking(){
    int s[N];
    for(int i = 0; i < N; i++){
        s[i] = -1;
    }
    int voa=0;
    int soa[N];
    gastado=0;
    int nivel=0;
    while(nivel!=0 || voa!=presupuesto ){
        Generar(nivel,s);
        if(Solucion(nivel,s)&&gastado>voa){
            voa=gastado;
            for(int i=0;i<N;i++){
                soa[i]=s[i]; //soa=s
            }
        }
        if(Criterio(nivel,s)){
            nivel++;
        }
        else{
            while(!masHermanos(nivel,s)&&nivel>0){
                Retroceder(nivel,s);
            }
        }
    }
    cout << "Los precios de los productos comprados son: " << voa <<endl;
    for(int i = 0; i < N; i++) {
        if(soa[i] > 0) {
            cout << "Producto " << i << ": ";
            cout << P[i] << " euros, "<<soa[i]<<" unidades."<<endl;;
        }
    }
    cout << endl;


}

int main(){
    
    backtracking();
    
    return 0;
}