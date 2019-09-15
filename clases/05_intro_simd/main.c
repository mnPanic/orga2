#include "stdio.h"

extern float productoInternoFloats(float* a, float* b, short n);

int main() {
    float fs_1[4] = {4.0, 3, 6, 10.0};
    float fs_2[4] = {2, 9, 10, 11};
    // 4 * 2 + 3 * 9 + 6* 10 + 10 * 11 = 205

    printf("resultado: %f", productoInternoFloats(fs_1, fs_2, 4));
}