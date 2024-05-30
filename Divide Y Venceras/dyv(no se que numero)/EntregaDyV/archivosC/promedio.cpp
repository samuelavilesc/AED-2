#include<stdlib.h>
#include<time.h>
#include<stdio.h>
int main(int c, char** s){
    int n = 10;
    printf("%d\n",1);
    int i;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        printf("%c", 'a' + rand() % (('z' - 'a') + 1));
    }
    printf("\n%d\n",n);
    for(i = 0; i < 5; i++){
        printf("%c", 'a' + rand() % (('z' - 'a') + 1));
    }
    printf("\n");
}


