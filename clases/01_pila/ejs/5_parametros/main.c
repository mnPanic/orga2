#include "stdio.h"

extern int suma_parametros(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
// a0-a1+a2-a3+a4-a5+a6-a7
int main() {

    // 5 - 7 + 5 - 1 + 5 - 3 + 9 - 0
    // 13
    int res = suma_parametros(5, 7, 5, 1, 5, 3, 9, 0);
    printf("got: %i", res);
}