#include <iostream>
#include <stdlib.h>

#define MENOS_INFINITO -9999999
#define TAMANO 25
using namespace std;


int nw; //NUMERO DE TRABAJADORES -----W
int nt; //NUMERO DE TRABAJOS ------------- T
int b[TAMANO][TAMANO]; //Array de beneficios de [trabajador], [trabajo]
int c[TAMANO]; //Array de capacidad máxima de trabajador

//Variables globales para el algoritmo
int bact;
int maxCol[TAMANO];//Array donde se almacenan el sumatorio de los máximos de las columnas de b[i][j]
int voa = MENOS_INFINITO; //voa = VALOR OPTIMO ACTUAL -- global;

void imprimeArray2d(){
	cout<<endl;
	for(int i=0; i<nw; i++){
		for(int j=0; j<nt; j++){
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void imprimeArray1d(int v[], int n){
	cout<<endl;
	for(int i=0; i<n; i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

void asignaValorArray(int a[], int b[], int n){
	for(int i=0; i<n; i++){
		b[i]=a[i];
	}
}

void Generar(int nivel, int s[]){
	s[nivel]++;
	if(s[nivel]==0){
		bact+=b[s[nivel]][nivel];
	}
	else{
		bact+=b[s[nivel]][nivel] - b[s[nivel]-1][nivel];
	}
	c[s[nivel]]--;
	c[s[nivel]-1]++;
}

bool Solucion(int nivel, int s[]){
	return nivel==nt-1 && c[s[nivel]]>=0;
}

bool Criterio(int nivel, int s[]){
	if(c[s[nivel]]<0 || b[s[nivel]][nivel]==0 ||  (bact + maxCol[nivel+1])<=voa  ){
		return false;
	}
	return true;
}	

bool MasHermanos(int nivel, int s[]){
	if(s[nivel]<nw-1){
		return true;	
	}
	return false;
}

void Retroceder(int &nivel, int s[]){
	bact -= b[s[nivel]][nivel];
	c[s[nivel]]++;
	s[nivel]=-1;
	nivel--;
}



void asignacionTrabajos(int s[]){//s es de tamaño nt	
	int nivel = 0;
	voa = MENOS_INFINITO; //voa = VALOR OPTIMO ACTUAL - global
	int *soa; //= SOLUCION OPTIMA ACTUAL
	soa=new int[nt];
	bact = 0; //bact = BENEFICIO ACTUAL
	
	//Inicializamos el array solución a -1, porque no representa ningún trabajador
	for(int i=0; i<nt; i++){
		s[i] = -1;
		soa[i]=-1;
	}
	//repetir
	while(nivel!=-1){//hasta nivel == 0
		Generar(nivel,s);
		if( Solucion(nivel,s) && bact > voa){
			voa=bact;
			asignaValorArray(s,soa,nt);//soa = s;
		}
		if(Criterio(nivel,s) && nivel!=nt-1){
			nivel++;
		}
		else{
			while(!MasHermanos(nivel,s) && nivel >= 0){
				Retroceder(nivel, s);
			}
		}
	}
	
	asignaValorArray(soa, s, nt);
}



int main(){
	int T; //Numero de casos de prueba
	cin >> T;
	//int nw; //NUMERO DE TRABAJADORES (global)--------------------------------------TRABAJADOR = W
	//int nt; //NUMERO DE TRABAJOS (global) ----------------------------------------------------TRABAJO = T
	for(int i=0; i<T; i++){
		cin >> nw >> nt;//Leemos filas, columnas
		
		//Vamos a crear un array  con el máx beneficio de cada columna para ver si nos interesa seguir 
		//el criterio
		//int maxCol[nt];//Aqui tenemos el array que almacena los máximos de cada trabajo -- global
		/*int maxCol[nt];
		b = new int *[nw];//Array de beneficios de [trabajador], [trabajo] -- global
		for(int j=0; j<nw; j++){
			b[j] = new int [nt];
		}
		int c[nw];//Array de capacidad máxima de trabajador -- global*/
			
		//Leemos el array de beneficios
		for(int j=0; j<nw; j++){
			for(int k=0; k<nt; k++){
				cin >> b[j][k];
				if(b[j][k]>maxCol[k]){
					maxCol[k] = b[j][k];
				}
			}
		}
		int sum=0;
		for(int j=nt-1; j>=0; j--){
			sum+=maxCol[j];
			maxCol[j]=sum;
		}
		
		//Leemos el array de capacidad
		for(int j=0; j<nw; j++){
			cin >> c[j];
		}	
		
		//Ya hemos leido los datos de entrada -> Aplicamos el algoritmo
		int sol[nt];
		asignacionTrabajos(sol);
		
		int res=0;
		for(int j=0; j<nt; j++){
			if(sol[j]!=-1){ //0 significa que no hay solución
				res += b[sol[j]][j];
			}
			else{
				res=0;
				break;
			}
		}		
		cout<<res<<endl;
		
		/*for(int j=0; j<nw; j++){ cerr << j << " "; cerr.flush();
			delete[] b[j];
		}
		cerr << endl << "b"; cerr.flush();
		delete[] b;		*/
		
	}
}
