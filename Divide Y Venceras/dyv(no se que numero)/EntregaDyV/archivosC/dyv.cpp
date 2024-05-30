#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
using namespace std;
#define PEQ 4

string conjunto;
string cadena;

list<int> resDirecta (int ini, int fin){
    list<int> posiciones;
    list<char> rep;
    int nLetra=0;
    int cont=0;
    for(int i =ini; i<=fin;i++){
        bool repetido = false;
        int j =0;
        bool igual = false;
        while(j<=(int)conjunto.length()-1 && !igual){
            if(cadena[i]==conjunto[j]) {
                if(rep.size()==3) rep.pop_front();
                if(find(rep.begin(), rep.end(), cadena[i]) != rep.end()) {
                        repetido = true;
                        if(nLetra>1 && rep.back() == cadena[i]) return posiciones;
                }
                igual = true;
                rep.push_back(cadena[i]);
                if(!repetido) cont++;
            }
            if(nLetra>0 && j==(int)conjunto.length()-1 && igual==false) return posiciones;
            //Si una letra diferente a la primera no pertenece al conjunto, ya no puede haber más cadenas que cumplan la condición
            j++;
        }
        if(igual==false) cont=0;
        if(cont==3){
            cont--;
            posiciones.push_back(i-1); //Añadimos 1 al inidice
        }
        nLetra++;
    }
    return posiciones;
}
list<int> combinar(list<int> res1, list<int> res2, int ini, int fin){
    int m = (fin+ini)/2;
    list<int> res3 = resDirecta(m-1,m+2);
    res1.merge(res3);
    res1.merge(res2);
    return res1;
}
list<int> buscaSubcadenas(int ini, int fin){
    if ((fin-ini+1) <=  PEQ) {return resDirecta(ini, fin);}
    else{
        list<int> res1 = buscaSubcadenas(ini,(ini+fin)/2);
        list<int> res2 = buscaSubcadenas((ini+fin)/2+1,fin);
        return combinar(res1, res2, ini, fin);
    }
}


int main (void) {
    int ncasos;
    string cad;
    string conj;
    int n;
    cin >> ncasos;
    for(int i=0; i<ncasos;i++){
        cin >> cad;
        cin >> n;
        cin >>conj;
        conjunto=conj;
        cadena = cad;
        list<int> solucion=buscaSubcadenas(0,n-1);
        cout << "La solucion es " << solucion.size()<< " "<<endl;
        cout << "En las posiciones: ";
        for (const auto& elemento : solucion) {
            cout << elemento << " ";
        }
    }
}
