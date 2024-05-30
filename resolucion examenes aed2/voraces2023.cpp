#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int D = 21; // Presupuesto disponible
int sol[4]; // Arreglo para almacenar la solución

bool solucion(int gastado) {
    return gastado >= D;
}
bool factible(int x, int gastado) {
    return x + gastado <= D;
}
int seleccionar(std::vector<int>& precio,int i) {
    return precio[i];
}
void instertar(int* gastado, int x,int i,int precio) {
 // Intentar agregar hasta 3 unidades de la prenda actual sin exceder el presupuesto
        if ((precio * 3 + *gastado) <= D) {
            *gastado += precio * 3;
            sol[i] = 3;
        } else if (precio * 2 + *gastado <= D) {
            *gastado += precio * 2;
            sol[i] = 2;
        } else if (precio + *gastado <= D) {
            *gastado += precio;
            sol[i] = 1;
        }
}
int voraces(vector<int>precios){
    int gastado = 0;
    int i = 0;
    for(int i = 0; i < precios.size(); i++) {
        sol[i] = 0;
    }
    sort(precios.begin(), precios.end(), greater<int>()); // ordenar de mayor a menor
    
    while(!solucion(gastado)&& i < precios.size()) {
        int x = seleccionar(precios,i);
        if(factible(x, gastado)) {
            instertar(&gastado,x,i,precios[i]);

        }
        i++;
    }
    return gastado;
}

int main() {
    // Ejemplo de uso del algoritmo
    int preciosArray[]={1,4,9,7};
    std::vector<int> precios(preciosArray, preciosArray+4); // Precios de las prendas
    vector<int> preciosOrdenados = precios;
    sort(preciosOrdenados.begin(), preciosOrdenados.end(), greater<int>()); // ordenar de mayor a menor
    int gastado =voraces(precios);
    // Mostrar la solución
    std::cout << "Gasto total: " << gastado << std::endl;
    std::cout << "Prendas seleccionadas: ";
    for (size_t i = 0; i < precios.size(); ++i) {
        if (sol[i] > 0) {
            std::cout << sol[i] << " unidad(es) de prenda con precio " << preciosOrdenados[i] << ", ";
        }
    }
    std::cout << std::endl;
    return 0;
}