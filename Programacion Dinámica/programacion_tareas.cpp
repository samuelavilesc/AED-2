// Programación de tareas
// (Weighted Interval Scheduling)
//
// Problema:
//      Dadas n tareas, cada una con un tiempo de inicio, tiempo de finalización y un beneficio asociado,
//      se desea determinar el beneficio máximo que se puede obtener al realizar un subconjunto de estas tareas
//      en un tiempo máximo de tal forma que no se superpongan en el tiempo.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Intervalo {
    int comienzo;
    int fin;
    int beneficio;
};

bool compararIntervalos(const Intervalo& a, const Intervalo& b) {
    return a.fin < b.fin;
}

int ultimaTareaCompatible(const std::vector<Intervalo>& intervalos, int actual) {
    for (int i = actual - 1; i >= 0; i--) {
        if (intervalos[i].fin <= intervalos[actual].comienzo) {
            return i;
        }
    }
    return -1;
}

void imprimirSolucion(const std::vector<Intervalo>& intervalos, const std::vector<int>& tabla) {
}


int programacionTareasOptima(const std::vector<Intervalo>& intervalos) {
    int n = intervalos.size();
    std::vector<int> tabla(n);
    tabla[0]=intervalos[0].beneficio;
    for(int i =1;i<n;i++){
        int beneficioTarea=intervalos[i].beneficio;
        int ultimaCompatible=ultimaTareaCompatible(intervalos,i);
        tabla[i]=max(beneficioTarea+tabla[ultimaCompatible],tabla[i-1]);

    }
  return tabla[n-1];
}

int main() {
    std::vector<Intervalo> intervalos = {
        {1, 4, 13},
        {3, 5, 5},
        {0, 6, 7},
        {5, 8, 1}
    };

    std::sort(intervalos.begin(), intervalos.end(), compararIntervalos);

    int beneficio = programacionTareasOptima(intervalos);
    std::cout << "Beneficio máximo: " << beneficio << std::endl;

    return 0;
}
