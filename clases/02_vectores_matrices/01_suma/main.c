#include "stdio.h"

extern short suma_asm(short* vector, short n);
int main() {
    short v[5] = {1, 2, 3, 4, 5};
    printf("Resultado: %i\n", suma(v, 5));
    printf("Resultado asm: %i\n", suma_asm(v, 5));
    return 0;
}
