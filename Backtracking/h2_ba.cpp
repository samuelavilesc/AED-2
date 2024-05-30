#include <iostream>
#include <cmath>
using namespace std;
/////// VARIABLES GLOBALES ///////
int fi = 0; // fila factible
int fj = 0; // columna factible

/////// FUNCIONES ///////

void leerMatriz(int n, int m, int **matriz){ // n = tareas, m = maquinas, matriz = matriz de tiempos
    int i, j; // i = filas, j = columnas
    for (i = 0; i < n; i++){ // recorre filas
        for (j = 0; j < m; j++){ // recorre columnas
            cin >> matriz[i][j]; // lee el tiempo de la tarea i en la maquina j
        }
    }
}

void seleccion(int n, int m, int **matriz, int *TM){ // n = tareas, m = maquinas, matriz = matriz de tiempos, TM = tiempo de maquinas
    int min = pow(10,9); // min = tiempo minimo inicializado a un numero muy grande
    int i, j; // i = filas, j = columnas
    for (i = 0; i < n; i++){ // recorre filas
        for (j = 0; j < m; j++){ // recorre columnas
            if (matriz[i][j] != -1) { // si la tarea i en la maquina j no ha sido seleccionada
                if (matriz[i][j]+TM[j] < min){ // si el tiempo de la tarea i en la maquina j mas el tiempo de la maquina j es menor que el minimo
                    min = matriz[i][j]+TM[j]; // actualizamos el minimo
                    fi = i; // actualizamos la fila factible
                    fj = j; // actualizamos la columna factible
                }
            }
        }
    }
}

void insertar(int cont, int m, int **matriz, int *TM, int *sol_t, int *sol_m){ // cont = contador, m = maquinas, matriz = matriz de tiempos, TM = tiempo de maquinas, sol_t = solucion tareas, sol_m = solucion maquinas
    sol_t[cont] = fi; // insertamos la tarea en la solucion
    sol_m[cont] = fj; // insertamos la maquina en la solucion
    TM[fj] += matriz[fi][fj]; // actualizamos el tiempo de la maquina
    for (int j = 0; j < m; j++){ // recorremos las columnas de dicha tarea
        matriz[fi][j] = -1; // marcamos la tarea como seleccionada
    }
}

void voraz(int n, int m, int *sol_t, int *sol_m, int *TM) { // n = tareas, m = maquinas, sol_t = solucion tareas, sol_m = solucion maquinas, TM = tiempo de maquinas
    fi = 0; // fila factible
    fj = 0; // columna factible   
    for(int cont = 0; cont < n; cont++){ // recorremos las tareas
        seleccion(n,m,matriz,TM); // seleccionamos la tarea
        insertar(cont,m,matriz,TM,sol_t,sol_m); // insertamos la tarea en la solucion
    }
}

//Programa principal
int main(){
    int num_veces;
    cin >> num_veces;
    for (int i = 0; i < num_veces; i++){
        int n, m;
        cin >> n >> m;
        int **matriz; 
        matriz=(int **)malloc(n*sizeof(int *)); 
    	for(int i=0;i<n;i++){ 
        matriz[i]=(int *)malloc(m*sizeof(int)); 
   	 	}
    	leerMatriz(n,m,matriz); 
        int *TM;
        TM = (int *)malloc(m*sizeof(int));
        for (int i = 0; i < m; i++) TM[i] = 0;
        int *sol_t;
        sol_t = (int *)malloc(n*sizeof(int));
        int *sol_m;
        sol_m = (int *)malloc(n*sizeof(int));
        for (int i = 0; i < n; i++){
            sol_t[i] = 0;
            sol_m[i] = 0;
        }
        voraz(n,m,sol_t,sol_m,TM);
        for (int i = 0; i < n; i++) free(matriz[i]);
    	free(matriz); 
        cout << TM[fj] << endl;
        for (int i = 0; i < n; i++) cout << sol_t[i]+1 << " ";
        cout << endl;
        for (int i = 0; i < n; i++) cout << sol_m[i]+1 << " ";
        cout << endl;
    }
    return 0;
}