#include <iostream>

using namespace std;
int m;
int nCadaTalla[6];

int tallaToInt(string t) {
    if(t == "XS") return 0;
    else if(t == "S") return 1;
    else if(t == "M") return 2;
    else if(t == "L") return 3;
    else if(t == "XL") return 4;
    else return 5;
}
void Generar(int nivel, int s[]){
    s[nivel] = s[nivel] + 1;
}

bool Solucion(int nivel, int s[], string tallas[][2]){
    int nTalla1 = tallaToInt(tallas[nivel][0]);
    int nTalla2 = tallaToInt(tallas[nivel][1]);
    //Si estamos en el ultimo voluntario y la talla asiganada esta entre las que le valen
    // hay disponibles devolvemos true
    return (nivel == (m-1) && ((s[nivel] == nTalla1 && nCadaTalla[nTalla1] > 0)
                      || (s[nivel] == nTalla2 && nCadaTalla[nTalla2] > 0)));
}

bool Criterio(int nivel, int s[], string tallas[][2]){
    int nTalla1 = tallaToInt(tallas[nivel][0]);
    int nTalla2 = tallaToInt(tallas[nivel][1]);
   return nivel < (m-1) && ((s[nivel] == nTalla1 && nCadaTalla[nTalla1] > 0)
                      || (s[nivel] == nTalla2 && nCadaTalla[nTalla2] > 0));
}

bool MasHermanos(int nivel, int s[]){
    return (s[nivel]<5);
}
int Retroceder(int nivel, int s[]){
    s[nivel] = -1;
    nivel--;
    if(nivel !=-1) nCadaTalla[s[nivel]] = nCadaTalla[s[nivel]] +1;
    return nivel;
}


bool Backtracking (string tallas[][2]){
    int nivel= 0;
    int s[m];
    //Inicializamos la tupla solucion
    for(int i = 0; i<m; i++){
        s[i] = -1;
    }
    bool fin = false;
    do{
        Generar (nivel, s);
        if (Solucion (nivel, s, tallas)){
            fin= true;
        }
        else if(Criterio (nivel, s, tallas)){
            nCadaTalla[s[nivel]] =nCadaTalla[s[nivel]] -1;
            nivel++;
        }
        else {
              while (!MasHermanos(nivel, s) && (nivel>-1)){
                    nivel = Retroceder (nivel, s);
              }
        }
    } while (!fin && nivel != -1);
    return fin;
}

int main (void) {
    int ncasos;
    int N;
    cin >> ncasos;
    for(int i=0; i<ncasos;i++){
        cin >> N; //N Camisetas
        cin >> m;//M voluntarios
        // Crear la matriz de tallas
        string tallas[m][2];
        for(int i = 0; i < m; i++){
            for(int j = 0; j < 2; j++){
                cin >> tallas[i][j];
            }
        }

        for(int j =0; j<6;j++){
            nCadaTalla[j] = N/6;
        }
            bool result = Backtracking(tallas);
            if(result) cout << "YES" <<endl;
            else cout << "NO"<< endl;
        }
}


