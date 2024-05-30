#include <iostream>

using namespace std;

#define FILAS 20
#define COLUMNAS 23

int C;                              //C variable que re presenta el numero de prendas.
int M;                              //M variable que representa  el presupuesto disponible.
int Entrada[FILAS][COLUMNAS];       /* Matriz obtenida de la entrada, con 2 filas mas para almacenar el valor de la prenda mas barata
                                    y el camino mas barato hasta una solucion.*/
                                    
                                    
//Funcion que permite avanzar y ademas actualiza la variable acumulativa(valor).                               
int Generar(int S[], int nivel, int gasto){
    S[nivel] = S[nivel] + 1;
    if(S[nivel] == 1){
        gasto = gasto + Entrada[nivel][1];          
    }
    else{
        gasto = gasto + Entrada[nivel][S[nivel]];
        gasto = gasto - Entrada[nivel][S[nivel]-1];
    }
    return gasto;
}

//Funcion que implementa la poda haciendo uso de la ultima columna de la matriz Entrada.
bool Criterio(int nivel, int gasto){
    if(nivel >= C-1 || gasto>M){
        return false;
    }
    if(Entrada[nivel+1][22]>(M-gasto)){
        return false;
    }
    return true;
}

//Funcion que devuelve si tenemos mas hermanos que podemos recorrer. 
bool MasHermanos(int S[], int nivel){
    return (S[nivel] < Entrada[nivel][0]);
}

//Funcion que nos permite retroceder y ademas tambien acumulativa la variable acumulativa.
int Retroceder(int S[], int nivel, int* gasto){
    *gasto = *gasto - Entrada[nivel][S[nivel]];
    S[nivel] = 0;
    nivel--;
    return nivel;
}

//Funcion que determina si nos escontramos en una solucion.
bool Solucion(int nivel, int gasto){
    if(nivel == C - 1 && gasto <= M){
        return true;
    }
    return false;
}

//Funcion que representa el algoritmo de BackTracking.
int BackTracking(){
    int max = -1;                   //Variable para guardar la solucion a cada caso.
    int nivel = 0;                  //Variable que reprenta el nivel en el que nos encontramos.
    int gasto = 0;                  //Variable acumulativa para conocer cuando dinero hemos gastado.
    int S[FILAS];                   //Matriz para representar la solucion.
    for(int i = 0; i<C; i++){       
        S[i] = 0;
    }
    if(M<Entrada[0][22]){           //Comprobacion para conocer directamente si no existe solucion.
        return max;
    }
    do{
        gasto = Generar(S, nivel, gasto);
        if(Solucion(nivel, gasto) && gasto > max){
            if(gasto == M){
                return gasto;
            }
            max = gasto;
        }
        else if(Criterio(nivel, gasto)){
            nivel = nivel + 1;
        }
        else{
            while(!MasHermanos(S, nivel)&&(nivel>-1)){
                nivel = Retroceder(S, nivel, &gasto);
            }
        }
    }
    while(nivel>-1);
    return max;
}

//Main donde se lee la entrada y se rellena la tabla o matriz.
int main (void) {
    int ncasos = 0;                 
    int K = 0;
    cin >> ncasos;
    for(int i=0; i<ncasos; i++){
        cin >> M; //M presupuesto
        cin >> C; //C prendas
        int min = 201;
        for(int i = 0; i<20; i++){
            for(int j = 0; j<23; j++){
                Entrada[i][j] = 0;
            }
        }
        for(int i = 0; i < C; i++){
            cin >> K;
            Entrada[i][0] = K;
            for(int j = 1; j <= K; j++){
                cin >> Entrada[i][j];
                if(Entrada[i][j] < min){
                    min = Entrada[i][j];
                }
            }
            Entrada[i][21] = min;
            min = 201;
        }
        int aux = 0;
        for(int i = C-1; i >= 0; i--){
            aux = aux + Entrada[i][21];
            Entrada[i][22] = aux;
        }
        /*for(int i=0; i<20; i++){
            cout<<endl;
            for(int j =0; j<23; j++){
                cout<<Entrada[i][j]<<" ";
            }
        }*/
        int max = BackTracking();
        if(max == -1){
            cout<<"no solution"<<endl;
        }
        else{
            cout<<max<<endl;
        }
    }
}