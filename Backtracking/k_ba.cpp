#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;
/*
Los comentarios, al igual que el algoritmo voraz, son del experimento para los tiempos de ejecución, el resto corresponde al código utilizado para la
aceptación en mooshak
*/
void generar(int nivel, int sol[], int pesos[], int& equipo1, int& equipo2, int& c1, int& c2){
    if(sol[nivel]!= 1){
        sol[nivel]++;              //si el nivel no es 1, aumentamos el valor
        if(sol[nivel]==0){  //si es 0, genera en equipo1
            equipo1+=pesos[nivel];
            c1++;
        }
        else{             //si es 1, genera en equipo2 y resta en equipo1
            equipo2+=pesos[nivel];
            c2++;
            equipo1-=pesos[nivel];
            c1--;
        }
    }
}
int solucion(int nivel, int participantes, int c1, int c2){   //criterio para establecer que sea solucion, n nodos visitados y equipos parejos
    return (nivel == participantes -1) && (abs(c1-c2)<=1);
}
bool criterio(int nivel, int participantes, int c1, int c2){  //criterio para avanzar por esa rama, en cualquier nodo que no sea solución se estudia si los
                                                                //equipos cumplen la restriccion
    if ((nivel >= participantes-1) || (c1>participantes/2+1) || (c2>participantes/2+1)){
        return false;
    }
    else{
        return true;
    }
}
bool mas_hermanos(int nivel, int sol[]){ //si en ese momento no se ha avanzado a nivel = 1, hay más hermanos de ese nodo por evaluar
    return sol[nivel] < 1;
}

void retroceder(int& nivel, int sol[], int pesos[], int& equipo1, int& equipo2, int& c1, int& c2){
    if(sol[nivel]==1){
        equipo2 -= pesos[nivel];                //retrocede y elimina los cambios en ese nivel, retrocede de 1 en 1
        c2--;                                   //si nivel = 1, eliminamos cambios del equipo2, restamos peso y decrementamos
    }
    else{
        equipo1 -= pesos[nivel];                //si es 0, restamos peso y decrementamos del equipo1
        c1--;
    }
    sol[nivel] = -1;                           //establecemos el nivel a no explorado y retrocedemos el nivel en 1
    nivel--;
}
void backtracking(int pesos[], int participantes){
    int nivel = 0;  //nivel inicial
    int sol[participantes]; //vector solucion
    int equipo1 = 0;
    int equipo1_fin = 0;          //valor sobreescrito
    int c1 = 0;
    int equipo2 = 0;
    int equipo2_fin = 0;         //valor sobreescrito
    int c2 = 0;
    for (int i = 0; i<participantes; i++){
        sol[i] = -1; //valor no escogido, inicialización del vector de eleccion de miembros
    }
    int voa = 450*31;  //valor optimo actual (peso máximo de 450 por 31 miembros imposibles de asignar según restricciones del problema (infinito))
    while(nivel!=-1 && sol[0]!=1){    //si quitamos sol[0]=1 trabajamos sin poda extra, no eliminamos la mitad del vector solución
        generar(nivel, sol, pesos, equipo1, equipo2, c1, c2);                        //generamos el nivel
        if (solucion(nivel,participantes,c1, c2) && (abs(equipo1-equipo2)<voa)){     //si es solución y es mejor que voa anterior, se sobreescribe
            voa = abs(equipo1-equipo2);
            equipo1_fin = equipo1;               //guardamos en equipo1_fin y equipo2_fin los valores por si no volvemos a encontrar otra solućión mejor
            equipo2_fin = equipo2;
        }
        else if (criterio(nivel,participantes,c1,c2)){            //si se cumple el criterio sseguimos avanzando
            nivel++;
        }
        else while(!mas_hermanos(nivel,sol) && nivel > -1){          //si no tiene más hermanos, retrocedemos y eliminamos lo calculado
            retroceder(nivel,sol,pesos,equipo1,equipo2,c1,c2);
        }
    }

    if(equipo2_fin < equipo1_fin){
        cout << equipo2_fin << " " << equipo1_fin << endl;  //imrprimimos equipo1_fin y equipo2_fin, primero el menor de ellos
    }
    else{
        cout << equipo1_fin << " " << equipo2_fin << endl;
    }

}
/*
int *creaArray(int i){           //función para crear un array random de pesos (para experimento)
    srand(time(NULL));
    int *lista = new int[i];
    for (int j = 0; j< i; j++){
        lista[j] = rand() %450 +1;
    }
    return lista;
}
*/
/*
void Experimento(int a, int b, int salto, int num_repeticiones) {                            //función experimento para los tiempos de ejecución
    for(int i = a; i<b; i+=salto) {
        double tiempo_total = 0;                                                            //aquí creamos array dinámico, se debe eliminar del heap
        for (int j = 0; j < num_repeticiones; j++) {                                        //para no solapar el mismo array en varias ejecuciones,
            int* entrada = creaArray(i);                                                    //para esto también tenemos el sleep
            struct timeval ti, tf;
            gettimeofday(&ti,NULL);
            backtracking(entrada,i);
            gettimeofday(&tf,NULL);
            double tiempo = (tf.tv_sec-ti.tv_sec)*1000 + (tf.tv_usec-ti.tv_usec)/1000.0;
            tiempo_total += tiempo;
            delete[] entrada;
            sleep(1);
        }
        double tiempo_promedio = tiempo_total / num_repeticiones;
        cout << "Tiempo promedio: " << tiempo_promedio << " ms" << endl;
        cout << "N: " << i << endl;
    }
}
*/
int main(){
    //Experimento(1,30,1,2);
    int casos, participantes;
    cin >> casos;                              //leo casos de realización de backtracking
    for (int i = 0; i < casos; i++){           //bucle en función de casos
        cin >> participantes;                   //leo participantes (mñaximo 30)
        int pesos[participantes];               //creo array en pila (es posible debido al bajo tamaño (máximo 30)
        for (int j= 0; j<participantes; j++){
            cin >> pesos[j];                      //inserto datos de entrada (pesos) en array creado
        }
        backtracking(pesos,participantes);         //inicio de backtracking
    }
}
