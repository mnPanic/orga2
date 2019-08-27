#include <stdio.h>
#include <stdlib.h>
#define CANTIDAD_f2 64
#define CANTIDAD_f3 99
#define CANTIDAD_ARREGLO_PUNTEROS 8

void f1() {
	int *unPunteroAEntero = malloc(sizeof(int));
	*unPunteroAEntero = 5;
	printf("f1: El entero %d se encuentra en la posición de memoria %#x\n", *unPunteroAEntero, (long)unPunteroAEntero);
	printf("\n");

	// Falta hacer free al puntero unPunteroAEntero
	free(unPunteroAEntero);
}

extern void f1_asm();

int f2_auxiliar = 2;

int* f2_aux(int numero) {
	int *resultado = malloc(sizeof(int));
	int *temp = &f2_auxiliar;
	*resultado = numero * *temp;

	// Está mal el retorno, debería ser resultado
	return resultado;
}

void f2() {
	int total = 0;
	for (int i = 0; i < CANTIDAD_f2; ++i) {
		int *temp = f2_aux(i + 1);
		total += *temp;
		// Falta hacer free al resultado de f2_aux una vez que lo usamos, porque ya no lo necesitamos más
		// este se encuentra en la variable temp
		free(temp);
	}
	printf("f2: El total debería ser %d\n", (CANTIDAD_f2 * CANTIDAD_f2 + CANTIDAD_f2));
	printf("f2: El total es %d\n", total);
	printf("\n");
}

int f3_aux(int numero) {
	int *resultado_dinamica = malloc(sizeof(int));
	*resultado_dinamica = numero + (long)resultado_dinamica;
	// No se puede borrar resultado_dinamica y luego usarlo, eso está mal
	// Hay que usarlo primero, y luego borrar resultado_dinamica
	int resultado = *resultado_dinamica;
	free(resultado_dinamica);
	return resultado;
}

void f3() {
	int* unArreglitoDeEnteros = malloc(sizeof(int) * CANTIDAD_f3);
	for (int i = 0; i < CANTIDAD_f3; ++i) {
		unArreglitoDeEnteros[i] = f3_aux(i);
	}

	printf("f3: El primer número del arreglo es %d, el último es %d\n", *unArreglitoDeEnteros, unArreglitoDeEnteros[CANTIDAD_f3 - 1]);
	printf("f3: (estos números deberían ser distintos de cero)\n");
	printf("\n");

	// Falta hacer free de unArreglitoDeEnteros
	free(unArreglitoDeEnteros);
}

float *crear_float() {
	float *resultado = malloc(sizeof(float));
	*resultado = 3.1415;
	printf("float: Se creó el float %f en la dirección %#x\n", *resultado, (long) resultado);
	return resultado;
	free(resultado);
}

void imprimir_float(float **unFloat) {
	// Hay que desreferenciar el puntero recibido, o cambiar la aridad de la función
	printf("float: El número de punto flotante %f está en la dirección %#x\n", **unFloat, (long) *unFloat);
	printf("float: (el número y la dirección deberían ser iguales que la línea anterior)\n");
}

void liberar_float(float **unDoblePunteroAFloat) {
	// El free está bien, pero en este caso se debe desreferenciar el doble puntero antes de liberarlo
	// O en su defecto cambiar la aridad de la función para que reciba un puntero simple
	// (y cambiar también el llamado en main)
	free(*unDoblePunteroAFloat);
	printf("\n");
}

int** crear_arreglo_de_punteros() {
	int** resultado = malloc(sizeof(int*)*CANTIDAD_ARREGLO_PUNTEROS);
	long iterador = (long) resultado;
	iterador += sizeof(int*)*CANTIDAD_ARREGLO_PUNTEROS;
	// El iterador recorre desde el final de la lista, hacia atrás.
	for (int i = 0; i < CANTIDAD_ARREGLO_PUNTEROS; ++i) {
		// Debería restar de a 8 bytes, ya que eso ocupa un puntero
		// Es decir, sizeof(int*)
		iterador = iterador - sizeof(int*);
		*((int**)iterador) = malloc(sizeof(int));
		**((int**)iterador) = i + 10;
	}
	return resultado;
}

void imprimir_arreglo_de_punteros(int** doblePunteroAEntero) {
	printf("arregloints: El arreglo de punteros a entero tiene los elementos [");
	for (int i = 0; i < CANTIDAD_ARREGLO_PUNTEROS; ++i) {
		int* punteroAEntero = doblePunteroAEntero[i];
		printf("[%#x]", punteroAEntero);
		printf("->");
		printf("%d", (punteroAEntero!=NULL)?*punteroAEntero:0);
		
	}
	printf("]\n");
	printf("arregloints: debería tener %d punteros, cada uno apuntando a enteros del 17 al 10\n", CANTIDAD_ARREGLO_PUNTEROS);
}

void destruir_arreglo_de_punteros(int** unArregloDePunteros) {
	// Antes de liberar el arreglo de punteros, hay que liberar cada puntero que se encuentra adentro
	for (int i = 0; i < CANTIDAD_ARREGLO_PUNTEROS; ++i) {
		free(unArregloDePunteros[i]);
	}
	free(unArregloDePunteros);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	f1();

	f1_asm();

	f2();

	f3();

	float *unFloat = crear_float();
	imprimir_float(&unFloat);
	liberar_float(&unFloat);

	int **arregloDePunteros = crear_arreglo_de_punteros();
	imprimir_arreglo_de_punteros(arregloDePunteros);
	destruir_arreglo_de_punteros(arregloDePunteros);

	return 0;
}