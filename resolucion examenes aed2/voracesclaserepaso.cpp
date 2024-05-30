#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#define TAM 12
#define PRESUPUESTO 30

using namespace std;

int sol[TAM];
bool solucion(int gastado) {
    return gastado >= PRESUPUESTO;
}
int seleccionar(vector<int>& precio,int i) {
    return precio[i];
}
bool factible(int x, int gastado) {
    return x + gastado <= PRESUPUESTO;
}
void instertar(int* gastado, int x,int i) {
  sol[i]=1;
    *gastado +=x;
}
void voraz(vector<int>& precio) {
    int gastado = 0;
    int i = 0;
    for(int i = 0; i < TAM; i++) {
        sol[i] = 0;
    }
    sort(precio.begin(), precio.end(), greater<int>()); // ordenar de mayor a menor
    
    while(!solucion(gastado)&& i < TAM) {
        int x = seleccionar(precio,i);
        if(factible(x, gastado)) {
            instertar(&gastado,x,i);

        }
        i++;
    }
}

int main() {
    int preciosArray[] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10, 12, 6};
    vector<int> precio(preciosArray, preciosArray + TAM);

    voraz(precio);

    cout << "Los precios de los productos comprados son: " << endl;
    for(int i = 0; i < TAM; i++) {
        if(sol[i] == 1) {
            cout << "Producto " << i << ": ";
            cout << precio[i] << " "<<endl;;
        }
    }
    cout << endl;

    return 0;
}
