#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

///////// VARIABLES GLOBALES ///////

int n;
int m;
int reciente;
int voa;
int *soa;
int nivel;
int **matriz;

///////// FUNCIONES ////////////

void leerMatriz(){ // n = tareas, m = maquinas
    int i, j; // i = filas, j = columnas
    for (i = 0; i < n; i++){ // recorre filas
        for (j = 0; j < n; j++){ // recorre columnas
            cin >> matriz[i][j]; // lee la distancia desde la subpoblacion i a la subpoblacion j
        }
    }
}

int solucion(int *s){ // s = solucion
    int suma=0; // suma = suma de las distancias de la solucion
    for (int i=0;i<m;i++){ // recorre las subpoblaciones de la solucion
        for(int j=0;j<m;j++){ // recorre las subpoblaciones de la solucion
            suma+=matriz[s[i]-1][s[j]-1]; // suma la distancia desde la subpoblacion i a la subpoblacion j
        }
    }
    return suma; // devuelve la suma de las distancias de la solucion
}

bool criterio(int cont){ // cont = contador
    bool c=false; // c = criterio
    if (cont<=m&&nivel<m){ // si el contador es menor o igual que el numero de subpoblaciones y el nivel es menor que el numero de subpoblaciones
        c=true; // el criterio es verdadero
        if(cont==m){ // si el contador es igual al numero de subpoblaciones
            c=false; // el criterio es falso
        } 
    }
    return c; // devuelve el criterio
}

void generar(int &cont, int *s){ //generar arbol combinatorio
    if(s[nivel-1]==0) { //el primer hermano
        if (nivel==1){ //primer nivel
            s[nivel-1]=1; //>>1 
            cont++;
        }
        else { //nivel>1
            s[nivel-1]=s[nivel-2]+1; // siguiente al padre
            cont++;
        }
    }
    else { //hermano mayor a 1
        s[nivel-1]++;
    }
    
}

bool mas_hermanos(int *s){ // s = solucion
    return (s[nivel-1] < n-(m-nivel)); // devuelve si el hermano es menor que el numero de subpoblaciones total menos el numero de subpoblaciones a escoger menos el nivel
}

void retroceder(int &cont, int *s){ // cont = contador, s = solucion
    cont--; // decrementa el contador
    s[nivel-1]=0; // pone el hermano a 0
    nivel--; // decrementa el nivel
}

bool hay_solucion(int cont){ // cont = contador
    return (cont == m); // devuelve si el contador es igual al numero de subpoblaciones a escoger
}

void Backtracking(){ // Funcion Backtracking
    reciente=0; // reciente = solucion mas reciente
    int *s; // s = solucion
    s=(int *)malloc(m*sizeof(int)); // reservamos memoria para la solucion e inicializamos a 0
    for(int i=0;i<m;i++) s[i]=0; 
    nivel=1; // nivel = nivel del arbol
    int cont=0; // cont = contador de subpoblaciones
    voa=-1; // voa = valor optimo actual
    soa=(int *)malloc(m*sizeof(int)); // soa = solucion optima actual
    while (nivel > 0){ // mientras el nivel sea mayor que 0
        generar(cont, s); // genera el arbol combinatorio
        if (hay_solucion(cont)){ // si hay solucion
            reciente=solucion(s); // calcula la solucion actual
            if (reciente>voa){ // si la solucion actual es mejor que la solucion optima actual
                voa=reciente; // actualiza la solucion optima actual
                for (int i=0;i<m;i++){ // recorre las subpoblaciones de la solucion
                    soa[i]=s[i]; // actualiza la solucion optima actual
                }
            }
        }
        if (criterio(cont)) // si el criterio es verdadero
        {
            nivel++; // incrementa el nivel
        }
        else{
            while (!mas_hermanos(s) && nivel > 0){ // mientras no haya mas hermanos y el nivel sea mayor que 0
                retroceder(cont, s); // retrocede
            }
        }    
    }
    cout << voa << endl; // imprime la solucion optima actual
    free(s); // libera memoria de la solucion
    free(soa); // libera memoria de la solucion optima actual
}

///////// MAIN ////////////

int main(){
    int num_veces;
    cin >> num_veces;
    for (int i = 0; i < num_veces; i++){
        cin >> n >> m;
        matriz = (int **)malloc(n * sizeof(int *));
        for (int j = 0; j < n; j++){
            matriz[j] = (int *)malloc(n * sizeof(int));
        }
        leerMatriz();
        Backtracking();
        free(matriz);
    }
    return 0;
}