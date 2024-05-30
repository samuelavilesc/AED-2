#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#define TAM 5
#define M 10

using namespace std;

int sol[TAM];

int seleccionar(vector<int>& tarea,int i) {
    return tarea[i];
}
int factible(int x,int conv[3]) {
    if(conv[0]+x<=M) {
        return 0;
    }
    if (conv[1]+x<=M) {
        return 1;
    }
    if (conv[2]+x<=M) {
        return 2;
    }
    return -1;
    
}
void instertar(int conv[3], int x,int i) {
    int p = factible(x,conv);
    sol[i]=p;
    conv[p] +=x;
}
void voraz(vector<int>& precio) {
    int conv[3]={0,0,0};
    int i = 0;
    bool solucion=true;
    for(int i = 0; i < TAM; i++) {
        sol[i] = -1;
    }
    sort(precio.begin(), precio.end(), greater<int>()); // ordenar de mayor a menor
    
    while(solucion&& i != TAM+1) {
        int x = seleccionar(precio,i);
        if(0<=factible(x,conv)<=2) {
            instertar(conv,x,i);

        }else{
            solucion=false;
        }
        i++;
    }
    if (!solucion){
        cout<<"No se ha podido encontrar una solucion"<<endl;
    }
    cout << "Array de soluciones: " << endl;
    for(int i = 0; i < TAM; i++) {
        cout << sol[i] << " ";
    }
    cout << endl;
    cout << "Array de convocatorias: " << endl;
    for(int i = 0; i < 3; i++) {
        cout << conv[i] << " ";
    }
    cout << endl;
}

int main() {
    int tareasArray[] = {5, 3, 1, 3, 4};
    vector<int> tareas(tareasArray, tareasArray + TAM);

    voraz(tareas);



    return 0;
}
