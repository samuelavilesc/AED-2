#include <iostream>
#include <list>

using namespace std;
int A;                      //Representa el numero de alumnos
list <int> parejas;         //Lista para guardar las parejas que vayan realizando

/*Funcion para selecionar la mejor pareja disponible.
Calculamos todos los beneficios y escogemos el mas alto*/
int Selecionar(int i, int** amistad, int** trabajo, int disponibles[], bool libres[]){
        for(int j=0; j<A; j++){
            if(libres[j] == false){
                disponibles[j] = -1;
            }
            else{
                disponibles[j] = (amistad[i][j]+amistad[j][i])*(trabajo[i][j]+trabajo[j][i]);
            }
        }
    int max =-1;
    int aux =-1;
    for(int i=0; i<A; i++){
        if(disponibles[i]>aux){
            aux = disponibles[i];
            max = i;
        }
    }
    return max;
}

//Funcion para insertar en la lista que representa nuestra solucion.
void Insertar(int i, int j){
    parejas.push_back(i);   
    parejas.push_back(j);
}

//Funcion para conocer si hemos alcanzado la solucion.
bool Solucion(int parejas){
    int total = A/2;
    return parejas<total;
}

//Funcion que representa el algoritmo de Avanze Rapido o voraz
int voraz(int** amistad, int** trabajo, int disponibles[], bool libres[]){
    int valor = 0, aux = 0, i = 0, j = 0;                   //Variables para representar el beneficio total, y las parejas.
    int parejas1 = 0;
    while(Solucion(parejas1)){
        aux = Selecionar(i, amistad, trabajo, disponibles, libres);
        libres[i] = false;
        libres[aux] = false;
        Insertar(i, aux);
        valor = valor + disponibles[aux];
        parejas1++;
        do{
        i++;
        }while(libres[i]!=true);
    }
    if(A%2 == 1){                           //Comprobacion por si ha quedado un alumno sin pareja.
        while(libres[j] != true){
            j++; 
        }
        parejas.push_back(j);
    }
    return valor;
}

//Main donde se incializan todos las tablas y la lista que usamos. Y desde donde se llama al algoritmo.
int main(){
    int num_casos = 0;
    cin >> num_casos;
    for(int i=0; i < num_casos; i++){
        cin >> A;
        int **amistad=new int*[A];
        int **trabajo=new int*[A];
        int valor = 0;
        parejas.clear();
        bool libres[A];             //Tabla para que alumnos aun se encuentran libres.
        int disponibles[A];         //Tabla auxiliar usasda en Selecionar.
        for(int i=0; i<A; i++){
            disponibles[i] = 0;
        }
        for(int i=0; i<A; i++){
            libres[i] = true;
        }
        for (int i = 0; i < A; ++i)
        {
        amistad[i] = new int[A];
        trabajo[i] = new int[A];
        }
        for(int i=0; i < A; i++){
            for(int j=0; j < A; j++){
                if(i==j){
                    amistad[i][j] = 0;
                }
                else{
                     cin >> amistad[i][j];
                }
            }
        }
         for(int i=0; i < A; i++){
            for(int j=0; j < A; j++){
                if(i==j){
                    trabajo[i][j] = 0;
                }
                else{
                     cin >> trabajo[i][j];
                }
            }
         }
        valor = voraz(amistad, trabajo, disponibles, libres);
        cout << valor << endl;
        list<int>::iterator it = parejas.begin();
        while( it != parejas.end() )
        {
            cout << *it << " ";                                                         
            it++;
        }
        cout<<endl;
        for (int i = 0; i < A; ++i) {               //Como la matriz principal se encuentra en memoria dinamica es necesalio liberarla.
            delete[] amistad[i];
        }
        for (int i = 0; i < A; ++i) {
            delete[] trabajo[i];
        }
        delete[] amistad;
        delete[] trabajo;
    }
}