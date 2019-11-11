#include <stdio.h>
#include <stdlib.h>
int main(int n, char** args){

    int a = atoi(args[1]);
    int b = 0;
    if (a > 5) {
        b = 4;
    } else {
        b = 6;
    }
    printf("%d", b);
}

