#include <stdio.h>
#include <stdlib.h>
#define CANTIDAD_f2 5
#define CANTIDAD_f3 99
#define CANTIDAD_ARREGLO_PUNTEROS 8

void f1() {
	int *unPunteroAEntero = malloc(sizeof(int));
	*unPunteroAEntero = 5;
	printf("f1: El entero %d se encuentra en la posición de memoria %#x\n", *unPunteroAEntero, (long)unPunteroAEntero);
	printf("\n");
	free(unPunteroAEntero);
}

extern void f1_asm();

int f2_auxiliar = 2;

int* f2_aux(int numero) {
	int *resultado = malloc(sizeof(int));
	int *temp = &f2_auxiliar;
	*resultado = numero * *temp;
	return temp;
}


void f2() {
	int total = 0;
	for (int i = 0; i < CANTIDAD_f2; ++i) {
		int *temp = f2_aux(i + 1);
		total += *temp;
	}
	printf("f2: El total debería ser %d\n", (CANTIDAD_f2 * CANTIDAD_f2 + CANTIDAD_f2));
	printf("f2: El total es %d\n", total);
	printf("\n");
}

int f3_aux(int numero) {
	int *resultado_dinamica = malloc(sizeof(int));
	*resultado_dinamica = numero + (long)resultado_dinamica;
	free(resultado_dinamica);
	int resultado = *resultado_dinamica;
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
}

float *crear_float() {
	float *resultado = malloc(sizeof(float));
	*resultado = 3.1415;
	printf("float: Se creó el float %f en la dirección %#x\n", *resultado, (long) resultado);
	return resultado;
	free(resultado);
}

void imprimir_float(float **unFloat) {
	printf("float: El número de punto flotante %f está en la dirección %#x\n", *unFloat, (long) unFloat);
	printf("float: (el número y la dirección deberían ser iguales en ambas líneas)\n");
}

void liberar_float(float **unDoblePunteroAFloat) {
	//free(unDoblePunteroAFloat);
	printf("\n");
}

int** crear_arreglo_de_punteros() {
	int** resultado = malloc(sizeof(int*)*CANTIDAD_ARREGLO_PUNTEROS);
	long iterador = (long) resultado;
	iterador += sizeof(int*)*CANTIDAD_ARREGLO_PUNTEROS;
	for (int i = 0; i < CANTIDAD_ARREGLO_PUNTEROS; ++i) {
		iterador = iterador - sizeof(int);
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
	printf("arregloints: debería tener %d punteros distintos, cada uno apuntando a enteros del 17 al 10\n", CANTIDAD_ARREGLO_PUNTEROS);
}

void destruir_arreglo_de_punteros(int** unArregloDePunteros) {
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
