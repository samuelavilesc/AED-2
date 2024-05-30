#include <iostream>
#include <vector>
int m=2;
int array[]={1, 2, 1, 2, 3, 4, 7, 8, 9, 10, 12, 6};
struct Solucion{
    int inicio; //`inicio` es el número de la primera posición
    int final; //`final` es el número de la ultima posición
    int longitud; //`longitud` es el calculo de C en el rango
};

bool pequeño(int p, int q){
    return q-p+1<=m;
}

Solucion SolucionDirecta(int p,int q){
    Solucion s;
    if(abs(array[q]-array[p])>1){
        s.inicio=0;
        s.final=0;
        s.longitud=0;
    }else{
        s.inicio=p;
        s.final=q;
        s.longitud=q-p+1;
    }
    return s;
}

int dividir(int p, int q){
    int r=(p+q)/2;
    return r;
}
Solucion solucionMayor(Solucion s1, Solucion s2){
    if(s1.longitud>s2.longitud){
        return s1;
    }else{
        return s2;
    }
}
Solucion extenderDerecha(Solucion s, int final){

    while(s.final<final && abs(array[s.final]-array[s.final+1])<=1){ //numero actual - numero anterior
       s.final++;
    }
    s.longitud=s.final-s.inicio+1;
    return s;
}
Solucion extenderIzq(Solucion s,int inicio){

    while(s.inicio>inicio && (array[s.inicio]-array[s.inicio-1])<=1){ //numero anterior - actual
        s.inicio--;
    }
    s.longitud=s.final-s.inicio+1;
    return s;

}

Solucion cadenaFrontera (int inicio, int mitad, int final){
    Solucion s;
    s=extenderIzq(s,inicio);
    s=extenderDerecha(s,final);
    return s;
}
Solucion combinar(Solucion s1, Solucion s2, int inicio, int final,int mitad){
   if(abs(array[mitad]-array[mitad+1])>1){
        return solucionMayor(s1,s2);
   }
   else if(s1.final==mitad){
        if(s2.inicio==mitad+1){
            Solucion s;
            s.inicio=s1.inicio;
            s.final=s2.final;
            s.longitud=s.final-s.inicio+1;
            return s;
        }else{
            s1=extenderDerecha(s1,final);
            return solucionMayor(s1,s2);
        }
   }else if(s2.inicio==mitad+1){
        s2=extenderIzq(s2,inicio);
        return solucionMayor(s1,s2);
    }else{
        Solucion s3 = {0,0,0};
        s3=cadenaFrontera(inicio,mitad,final);
        return solucionMayor(s1,solucionMayor(s2,s3));
    }
}
Solucion DyV(int p, int q){
    if(pequeño(p,q)){
        return SolucionDirecta(p,q);
    }else{
        int mitad=dividir(p,q);
        Solucion s1=DyV(p,mitad);
        Solucion s2=DyV(mitad+1,q);
        return combinar(s1,s2,p,q,mitad);
    }
}
int main(){
    Solucion s=DyV(0,12);
    std::cout<<"La longitud máxima es: "<<s.longitud<<std::endl;
    std::cout<<"La primera posición es: "<<s.inicio+1<<std::endl;
    std::cout<<"La última posición es: "<<s.final+1<<std::endl;
    //los +1 son por que la cadena de ejemplo va de 1 a n y no de 0 a n-1
    return 0;
}