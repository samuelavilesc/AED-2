#include <iostream>
#include <vector>

using namespace std;

bool tieneSubconjuntoSuma(const vector<int>& conjunto, int N) {
    int n = conjunto.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(N + 1, false));

    // Caso base: Si la suma deseada es 0, siempre se puede obtener sumando ningún elemento.
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    // Caso base adicional: Si no quedan elementos por considerar y la suma deseada es mayor que 0, no se puede obtener.
    for (int j = 1; j <= N; ++j) {
        dp[0][j] = false;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= N; ++j) {
            bool cojo =  dp[i - 1][j - conjunto[i - 1]];
            bool noCojo = dp[i - 1][j] ;
                dp[i][j] = cojo||noCojo;
            
        }
    }

    return dp[n][N];
}

int main() {
    vector<int> conjunto = {2, 9, 11};
    int suma_deseada = 20;

    if (tieneSubconjuntoSuma(conjunto, suma_deseada)) {
        cout << "Sí, hay un subconjunto que suma " << suma_deseada << "." << endl;
    } else {
        cout << "No, no hay un subconjunto que suma " << suma_deseada << "." << endl;
    }

    return 0;
}
