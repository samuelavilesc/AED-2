#include<iostream>

using namespace std;
#define TAM 12    
#define K 525  
int precios[TAM]={5,5,20,50,100,200,100,20,50,10,20,100}; //valor objetos
int utilidad[TAM]={1,3,20,50,100,5,10,20,50,10,20,100}; //utilidad objetos
int uact;
int pact;

void Generar(int nivel, int s[TAM]){
    s[nivel]++;
    if(s[nivel]==1){
        pact+=precios[nivel];//-s[nivel]+1; aqui habria que descomentar para hacerlo bien pero no se porque no funciona
        uact+=utilidad[nivel];
    }
    if(s[nivel]==2){
        pact=pact+(precios[nivel]-1);
        uact+=utilidad[nivel];
    }
    if(s[nivel]==3){
        pact=pact+(precios[nivel]-2);
        uact+=utilidad[nivel];
    }
}
bool Solucion(int nivel, int s[TAM]){
    return (pact<=K)&&(nivel==TAM-1);
}
bool Criterio(int nivel, int s[TAM]){
    return pact<=K && nivel<TAM-1;
}
bool masHermanos(int nivel, int s[TAM]){
    return s[nivel]<3;
}
void Retroceder(int &nivel, int s[TAM]){
    pact=pact-(3*precios[nivel]-3);
    pact-=utilidad[nivel]*3;
    s[nivel]=-1;
    nivel--;
}

void backtracking(){
    int uoa=0; //-infinito
    int soa[TAM];
    int s[TAM];
    int poa=0;
    int nivel=1;
    uact=0;
    pact=0;
    for(int i = 0; i < TAM; i++){
        s[i] = -1;
    }
    while(nivel!=0){
        Generar(nivel,s);
        if(Solucion(nivel,s)&&uact>uoa){
            uoa=uact;
            poa=pact;
            for(int i=0;i<TAM;i++){
                soa[i]=s[i];
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
    cout<<"Utilidad: "<<uoa<<endl;
    cout<<"Precio: "<<poa<<endl;
    cout<<endl;
}
int main (){

    backtracking();
    return 0;
}