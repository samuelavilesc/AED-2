#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#define TAM 12
#define C 250

using namespace std;

int sol[TAM];
bool solucion(int metido) {
    return metido >= C;
}
int seleccionar(vector<int>& moneda,int i) {
    return moneda[i];
}

void instertar(int* metido, int x,int i) {
  sol[i]=1;
    *metido +=x;
}
int voraz(vector<int>& moneda) {
    int metido = 0;
    int i = 0;
    int cota=C/4;
    for(int i = 0; i < TAM; i++) {
        sol[i] = 0;
    }
    vector<int> moneda2=moneda;
    sort(moneda2.begin(), moneda2.end()); // ordenar de menor a mayor
    sort(moneda.begin(), moneda.end(), greater<int>()); // ordenar de mayor a menor
    
    while(!solucion(metido)&& i < TAM) {
        int x;
        if(metido>=cota){
            x = seleccionar(moneda2,i);
        }else{
            x = seleccionar(moneda,i);
        }
        instertar(&metido,x,i);
        i++;
    }
    if(metido<C){
        return 0;
    }
    return metido;
}

int main() {
    int monedasArray[] = {5, 20, 20, 100, 200, 50, 10,20 , 50, 100, 200, 50};
    vector<int> moneda(monedasArray, monedasArray + TAM);

    int metido = voraz(moneda);
    if(metido==0){
        cout << "No se puede comprar" << endl;
        return 0;
    }else{

    cout << "El total de monedas metidas es: " << metido << endl;

    cout << endl;
    }
    return 0;
}
