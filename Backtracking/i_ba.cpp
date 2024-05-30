#include <iostream>
#include <sstream>

using namespace std;

int A;
int M;		// A = AVERIA	M = MECANICO	
int avt = 0;					// avt averias actuales;
int nivel;
int voa;

void Generar(int &nivel , int s[],int c[][30]){
	s[nivel] = s[nivel]+1;	
	cout << "s = ( ";
	for (int i = 0 ; i < 3 ; i++){
		cout << s[i] << " ";  
	}
		cout << ")"<< endl;
	if (s[nivel] == 0){	// SI GENERAMOS UN HERMANO

		
		if ( c[nivel][s[nivel]] == 1 ){		// miramos si el mecanico es capaz
			avt = avt + s[nivel];		
			cout << "avt = " << avt << endl;
		}
		
		
	}

}

bool seRepite(int &nivel, int s[]){
	for (int i = 0; i <= nivel-1 ; i++){
		if ( s[nivel] == s[i])	{
			return true;
		}
	}

	return false;
}
bool Solucion(int &nivel, int s[],int c[][30]){
	if (nivel == M-1) {
		cout << "No se ha encontrado una solución"<<endl;
	}	


	return ((nivel == A) && (avt<=M-1)&& (c[nivel][s[nivel]] == 1));
}

bool Criterio(int &nivel, int s[],int c[][30]){

	
	return ((nivel < A-1) && (avt<=M-1)&&(c[nivel][s[nivel]] == 1)); 
}

bool MasHermanos(int &nivel, int s[]){
	return s[nivel] < M-1;
}

void Retroceder(int &nivel, int s[], int c[][30]){
	
	avt = avt -s[nivel] ;
	
	
	s[nivel]=-1;
	nivel = nivel-1;	



}
void Backtracking (int s[],int n, int c[][30]){
	nivel = 0;
	voa = -100000;				// Lleva la suma de averias final
	avt=0;
	int soa[n];
	// INICIALIZAMOS EL SOA
	for (int i = 0 ; i < n ; i++){
		soa[i] = -1;
	}
	for (int i = 0; i < n; i++){
		s[i] = -1;
	}
	 do{
		Generar(nivel,s,c);
		if ( Solucion(nivel,s,c) && ( avt > voa) ) {
			voa = avt;
			soa[nivel] = s[nivel];
			cout<< "sustituimos soa= s "<< endl;
			}
		
		 if ( Criterio(nivel,s,c)){
			nivel = nivel+1;
		}
		else {
			while (!MasHermanos(nivel,s) && (nivel > -1)){
				Retroceder(nivel,s,c);
			}
			
		}
	} while( !(nivel == -1));

	cout << "Las averias reparas son " << voa << endl;
	for (int i = 0 ; i< n ; i++ ){
		cout << soa[i] << " ";
	} 	

	cout << endl;
}




int main(){
	int numCasos;					
	cin >> numCasos;
	for (int k = 0 ; k < numCasos; k++){
		cin >> M >> A;
		int array[A];	// array de mecanicos
		int aux;
		int c[A][30];	// matriz de capacidad
		for ( int i = 0 ; i < A ; i++){
			for (int j = 0; j < M ; j++){
				cin >> aux;
				c[i][j] = aux;	
			}								
		}
		for (int i = 0 ; i < A ; i++ ){
			array[i] = -1;
		}
	
		cout << M << " "<< A <<endl;
		for ( int i = 0 ; i < M ; i++){
			for (int j = 0; j < A ; j++){
				cout << c[i][j] << " ";
			}				
			cout << endl;			
		}
		cout << endl << endl;
		Backtracking(array,A,c);


		
		

	}

}

