//
// Problema de la mochila
// (Knapsack problem)
//

#include <iostream>

using namespace std;

void imprimir_tabla(int N, int M, int** tabla)
{
    for (int i = 0; i <= M; i++)
    {
        if (i > 0)
            cout << (i) << " ";
        else
            cout << "     ";
    }
    cout << endl;

    for (int i = 0; i <= N; i++)
    {
        if (i > 0)
            cout << "o" << (i) << " ";
        else
            cout << "   ";

        for (int j = 0; j <= M; j++)
        {
            cout << tabla[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int reconstruir_solucion(int N, int M, int pesos[], int** tabla)
{
  // Implementar despues del algoritmo de programación dinámica
  //recorrer la tabla y quedarse con el maximo
  return tabla[N][M];
}

void mochila(int N, int pesos[], int beneficios[], int capacidad)
{

    int **tabla;
    tabla = new int*[N + 1];
    for(int i = 0; i < N + 1; i++) {
        tabla[i] = new int[capacidad + 1];
    }


    for(int i=0; i<N + 1;i++){
        tabla[i][0]=0;
    }
    
    for(int j=0; j<capacidad+1;j++){
        tabla[0][j]=0;
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=capacidad;j++){
            int peso_restante = j-pesos[i-1];
            if(peso_restante>=0){
                //beneficios[i-1] para poder ver el objeto actual dado que estamos empezando los bucles en 1
                //para que corresponda con la indexacion de la tabla
                int tomar_objeto=beneficios[i-1]+tabla[i-1][peso_restante];
                int no_tomar_objeto = tabla[i-1][j];
                tabla[i][j]=max(tomar_objeto,no_tomar_objeto);
            }else{
                tabla[i][j]=tabla[i-1][j];
            }
        }
    }
    // Implementar
    
    int resultado = -1;
      
    imprimir_tabla(N, capacidad, tabla);
    resultado = reconstruir_solucion(N, capacidad, pesos, tabla);

    cout << "Solución: " << resultado << endl;

    for (int i = 0; i < N + 1; i++) {
        delete[] tabla[i];
    }
    delete[] tabla;

}

int main(int argc, char *argv[])
{
    int N = 3;
    int pesos[] = {2, 3, 4};
    int beneficios[] = {1, 2, 5};
    int capacidad = 6;

    //int N = 3;
    //int pesos[] = {2, 3, 6};
    //int beneficios[] = {1, 2, 5};
    //int capacidad = 8;

    mochila(N, pesos, beneficios, capacidad);

    return 0;
}
