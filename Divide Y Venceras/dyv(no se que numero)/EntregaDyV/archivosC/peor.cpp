#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include <iostream>
using namespace std;
int main(int c, char** s){
    int n = 10000;
    char conj[] = "abcde";
    printf("%d\n",1);
    int i;
    srand(time(NULL));
    for(i = 0; i < n/4; i++){
        printf("%c", conj[1]);
        printf("%c", conj[2]);
        printf("%c", conj[3]);
        printf("%c", conj[4]);
    }
    printf("\n%d\n",n);
    printf("%s", conj);
    printf("\n");
}

