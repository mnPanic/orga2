#include "stdio.h"

extern void sumar(short* p, int len);
#define LEN 8
int main() {
    short ss[LEN] = {1, 2, 3, 4, -1, -2, 3, -8};
    sumar(ss, LEN);
    for (int i = 0; i < LEN; i++) {
        printf("ss[%i] = %d\n", i, ss[i]);
    }
    return 0;
}