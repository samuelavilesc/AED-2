#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;


void leerEntrada(int n, double v[][3], double p[]){
		
	int aux;

	for ( int j = 0 ; j < n ; j++){
		cin >> aux;
		v[j][0] = aux;						
	}
	
	for ( int j = 0 ; j < n ; j++){
		cin >> aux;
		p[j] = aux;						
	}
		
	

}


void calcularProporciones(int n, double v[][3], double p[], double ord[][2]){

	for (int i = 0; i < n ; i++){
		ord[i][0] = p[i] / v[i][0] ;		// calculo las proporciones
		ord[i][1] = i;			// almaceno la posicion de cada proporción.
		
	 }

}

int colocar(double ord[][2], int b, int t,double v[][3]){
	int i;
	double  valor_pivote;
	double temp;
	int auxpos;
	int pivote = b;
	valor_pivote = ord[pivote][0];
	for ( i = b+ 1; i <= t ; i++){
		if (ord[i][0] < valor_pivote){
			pivote++;
			temp = ord[i][0];
			auxpos = ord[i][1];
			ord[i][0] = ord[pivote][0];
			ord[i][1] = ord[pivote][1];
			ord[pivote][0] = temp;
			ord[pivote][1] = auxpos;
		} else if (ord[i][0] == valor_pivote) {
				int auxi = ord[i][1];
				int auxpivo = ord[pivote][1];
				if ( v[auxi][0]  < v[auxpivo][0] ){ //*
					pivote++;
					temp = ord[i][0];
					auxpos = ord[i][1];
					ord[i][0] = ord[pivote][0];
					ord[i][1] = ord[pivote][1];
					ord[pivote][0] = temp;
					ord[pivote][1] = auxpos;
				}
		}
	}
	temp = ord[b][0];
	auxpos = ord[b][1];
	ord[b][0] = ord[pivote][0];
	ord[b][1] = ord[pivote][1]; 
	ord[pivote][0] = temp;
	ord[pivote][1] = auxpos;
       return pivote;		
}

void Quicksort(double ord[][2], int b, int t, double v[][3]){
 	int pivote;
 	if(b < t){
 	pivote=colocar(ord, b, t,v);
 	Quicksort(ord, b, pivote-1,v);
 	Quicksort(ord, pivote+1, t,v);
 } 
}


double Moneda(double v[][3], double p[],double ord[][2],int V, int n){

	int sumaPeso = 0;			// campo peso
	int sumaValor = 0;			// campo valor
	int pesomax = 0;
	int k;
	int aux;

	for ( int i = 0 ; i < n ; i++) {
		v[i][1] = 0;
		v[i][2] = 0;
	}
	int j= n-1;
	while ( j >= 0 && sumaValor <= V ){
		k = ord[j][1]; 		// toma la mejor proporcion que hay candidatos
		int posicionValor = v[k][0];
		if ( v[k][0] <= V-sumaValor){		//miramos si la moneda cabe
			aux = (V-sumaValor)/posicionValor;
			v[k][1] = aux; // cuantas moendas caben
			sumaValor = sumaValor+v[k][1]*posicionValor;
			sumaPeso = sumaPeso + p[k]*v[k][1];
		}
	j--;

	}
	pesomax = sumaPeso;
	j = 0;
	sumaValor = 0;
	sumaPeso = 0;
	while ( j < n && sumaValor <= V ){
		k = ord[j][1]; 		// toma la mejor proporcion que hay candidatos
		int posicionValor = v[k][0]; 
		if ( v[k][0] <= V-sumaValor){		//miramos si la moneda cabe
			aux = (V-sumaValor)/posicionValor;
			v[k][2] = aux;
			sumaValor = sumaValor+v[k][2]*posicionValor;
			sumaPeso = sumaPeso + p[k]*v[k][2];
			
		}
	j++;
	}
	return pesomax-sumaPeso;
}


int main(){
	

	int V,n;			// n tipos de monedas  V , s		
	int numCasos;	
	double peso;	
	 struct timeval ti, tf;
    double tiempo,tiempo2, tiempo3;	
	cin >> numCasos;
	for (int i = 0 ; i < numCasos; i++){
		cin >> n >> V;
		double ord[n][2];		// ord ordenado por proporcion p/v 
		double v[n][3];
		double p[n];
		leerEntrada(n, v, p);	
		  gettimeofday(&ti, NULL );
		calcularProporciones(n, v, p, ord);
gettimeofday(&tf, NULL);
 tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
  cout << "Tiempo calcularProporciones = " << tiempo <<"ms"<< endl;
cout << endl;	
gettimeofday(&ti, NULL );
		Quicksort(ord,0,n-1,v);
gettimeofday(&tf, NULL);
 tiempo2 = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
cout << "Tiempo Quickshort = " << tiempo2 <<"ms"<< endl;
cout << endl;	
gettimeofday(&ti, NULL );
		peso = Moneda(v,p,ord,V,n);
gettimeofday(&ti, NULL );
tiempo3 = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
cout << "Tiempo Algoritmo Voraz = " << tiempo3 <<"ms"<< endl;
cout << endl;	
		cout << peso << endl;
		
		for( int i = 0 ; i < n; i++){
			cout << v[i][1] << " ";
		}
		cout << endl;
		for( int i = 0 ; i < n; i++){
			cout << v[i][2] << " ";
		}	
		cout << endl;		
	}

}
