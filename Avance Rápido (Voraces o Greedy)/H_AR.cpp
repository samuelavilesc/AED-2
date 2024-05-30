#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITO 10000

vector<int> ordenTareas(int n, int m, int **matriz){
    vector<int> v;
    vector<int> tareas;
	for (int i = 0; i < n; i++) {
        int min = matriz[i][0];
        for (int j = 1; j < m; j++) {
            if (matriz[i][j] < min) {
                min = matriz[i][j];
            }
        }
        v.push_back(min);
    }
    int i =0;
    while (i<n) {
        // Encontrar el mínimo
        int min_valor = v[0];
        int min_indice = 0;
        for (int i = 1; i < (int)v.size(); i++) {
            if (v[i] < min_valor) {
                min_valor = v[i];
                min_indice = i;
            }
        }

        // Añadir el índice del mínimo al vector de índices
        tareas.insert(tareas.begin(),min_indice);

        // Descartar esa posicion poniendola a INFINITO
        v[min_indice]=INFINITO;
        i++;
    }
    return tareas;

}

int seleccionar(int **matriz, int n, int m, int tAcum[], vector<int> orden){
    int mq = 0;
    int min = INFINITO;
    int i = orden.back();
    for (int j = 0; j < m; j++) {
        //Buscamos el valor minimo en la tupla solucion como si sumasemos el tiempo de la tarea a los
        //tiempos en las maquinas actuales y elegimos el minimo
        if (tAcum[j] + matriz[i][j] < min) {
            min =  tAcum[j] + matriz[i][j];
            mq=j;
        }
    }
    return mq;

}
 int progTareas(int n, int m, int **matriz, vector<int>& tareas, vector<int>& maquinas){
        //S = vacio
        int tAcumulados[m];
        for(int i = 0; i < m; i++) {
            tAcumulados[i] = 0;
        }

        int mq;
        vector<int> orden = ordenTareas(n, m, matriz);

        //solucion() = true si ya hemos seleccionado una tarea en cada maquina
        while((int)tareas.size() < n){
            mq = seleccionar(matriz, n, m, tAcumulados, orden);
            //Factible es siempre true. Insertamos
            int t = orden.back();
            tareas.push_back(t);
            maquinas.push_back(mq);
            tAcumulados[mq] = tAcumulados[mq] + matriz[t][mq];
            orden.pop_back();
        }

    //objetivo(s)
     int suma = tAcumulados[0];
     for (int i = 1; i < m; i++) {
         if (suma < tAcumulados[i]) {
             suma = tAcumulados[i];
         }
     }
     return suma;
 }

void muestraPorPantalla(vector<int> v) {
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i]+1;
        if (i != (int)v.size() - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

int main (void) {
    int P;//Número de casos a evaluar
    int n;
    int m;

    cin >> P;
    for(int i=0; i<P;i++){
        cin >> n >> m;

        // Crear la matriz de tiempos
        int **tiempos = new int*[n];
        for(int i = 0; i < n; i++) {
            tiempos[i] = new int[m];
        }

        int x;
        for(int i=0; i < n; i++){
            for(int j=0; j<m; j++){
                cin >> x;
                tiempos[i][j] = x;
            }
        }
        vector<int> tareas;
        vector<int> maquinas;
        int sol = progTareas(n, m, tiempos, tareas, maquinas);
        cout << sol << endl;
        muestraPorPantalla(tareas);
        muestraPorPantalla(maquinas);

        // Liberar la memoria
        for(int i = 0; i < n; i++) {
            delete[] tiempos[i];
        }
        delete[] tiempos;
        }
}
