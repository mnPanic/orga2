// short suma(short* vector, short n);
// Dado un vector de n enteros de 16 bits, devolver la suma de los
// elementos.

short suma(short* vector, short n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += vector[i];
    }
    return sum;
}
