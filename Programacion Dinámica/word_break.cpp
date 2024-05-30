#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

std::string dictionary[] = {"yo", "soy", "tu", "padre",
    "juntos", "dominaremos", "la", "galaxia",
    "junto", "dominar", "gala",
    "te", "quiero", "lo", "se", ",",
    "dejalo", "ganar", "no", "conviene", "soliviantar", "a", "un", "wookiee"};

int DIC_SIZE = sizeof(dictionary) / sizeof(dictionary[0]);

bool es_palabra(const std::string& s) {
    return std::find(std::begin(dictionary), std::end(dictionary), s) != std::end(dictionary);
}

void recuperar_resultado(const std::string& s, const bool tabla[]) {
    int N = s.size();
    int inicio = 0;
    for (int i = 1; i <= N; ++i) {
        if (tabla[i]) {
            std::cout << s.substr(inicio, i - inicio) << " ";
            inicio = i;
        }
    }
    std::cout << std::endl;
}

bool word_break(const std::string& s) {
    int N = s.size();
    bool tabla[N + 1];
    std::fill_n(tabla, N + 1, false);
    tabla[0] = true; // Caso base

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (tabla[j] && es_palabra(s.substr(j, i - j))) {
                tabla[i] = true;
                break;
            }
        }
    }
    if(tabla[N]){
        cout << "La cadena se puede dividir en palabras del diccionario" << endl;
        recuperar_resultado(s, tabla);
    }
    return tabla[N];
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "./work_break cadena" << std::endl;
        return 1;
    }

    std::string entrada = argv[1];

    bool r = word_break(entrada);

    std::cout << "Cadena: " << entrada << std::endl;
    std::cout << "Resultado: " << (r ? "SI" : "NO") << std::endl;
    
    return 0;
}
