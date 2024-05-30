#include <iostream>
#include <vector>
int m=2;
int array[]={1, 2, 3, 5, 4, 6, 5, 4, 3, 5, 7, 9, 9, 8, 10, 5, 3};
struct Solucion{
    int first; //`first` es el número de la primera posición
    int second; //`second` es el número de la ultima posición
    int third; //`third` es el calculo de C en el rango
};

bool pequeño(int p, int q){
    return q-p<=m;
}

Solucion SolucionDirecta(int p,int q){
    Solucion s;
    s.first=p;
    s.second=q;
    int C=array[q]-array[p];
    if(C<0){
        s.third=0;
    }else{
        s.third=C;
    }
    return s;
}

int dividir(int p, int q){
    int r=(p+q)/2;
    return r;
}
Solucion solucionMayor(Solucion s1, Solucion s2){
    if(s1.third>s2.third){
        return s1;
    }else{
        return s2;
    }
}
Solucion extenderDerecha(Solucion s, int final){
    int C=0;
    int i=s.second+1;
    while(array[i]<=array[final]){
        i++;
    }
    s.second=i;
    s.third=SolucionDirecta(s.first,s.second).third;
    return s;
}
Solucion extenderIzq(Solucion s,int inicio){
    int C=0;
    int i=s.first-1;
    while(array[i]>=array[inicio]){
        i--;
    }
    s.first=i;
    s.third=SolucionDirecta(s.first,s.second).third;
    return s;

}
Solucion cadenaFrontera (int inicio, int mitad, int final){
    Solucion s;
    s=extenderIzq(s,inicio);
    s=extenderDerecha(s,final);
    return s;
}
Solucion combinar(Solucion s1, Solucion s2, int inicio, int final,int mitad){
   if(array[mitad]>array[mitad+1]){
        return solucionMayor(s1,s2);
   }
   if(array[mitad-1]>array[mitad]){
        return solucionMayor(s1,s2);
   }
   else if(s1.first+s1.second==mitad){
        if(s2.first==mitad+1){
            Solucion s;
            s.first=s1.first;
            s.second=s2.second;
            s.third=SolucionDirecta(s1.first,s2.second).third;
            return s;
        }else{
            s1=extenderDerecha(s1,final);
        }
   }else if(s2.first==mitad+1){
        s2=extenderIzq(s2,inicio);
        return solucionMayor(s1,s2);
    }else{
        Solucion s3 = cadenaFrontera(inicio,mitad,final);
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
    Solucion s=DyV(0,17);
    std::cout<<"La suma máxima es: "<<s.third<<std::endl;
    std::cout<<"La primera posición es: "<<s.first<<std::endl;
    std::cout<<"La última posición es: "<<s.second<<std::endl;
    return 0;
}