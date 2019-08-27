/* printf, scanf, NULL */
#include <stdio.h>
/* malloc, free, rand */
#include <stdlib.h>

struct nodo{
	int dato;
	struct nodo *prox;
};
struct lista{
	struct nodo *primero;
};

void borrar(struct nodo **unDoblePunteroANodo){
	struct nodo *nodoABorrar = *unDoblePunteroANodo;
	free(nodoABorrar);
	*unDoblePunteroANodo = NULL;
}

void borrarUltimo(struct lista *unaLista) {
	struct nodo** proxNodo = &(unaLista->primero);
	struct nodo** anterior = proxNodo;
	while (*proxNodo != NULL) {
		anterior = proxNodo;
		proxNodo = &((*proxNodo)->prox);
	}
	borrar(anterior);
}

void agregarPrimero(struct lista* unaLista, int unInt) {
	struct nodo* nuevoNodo = malloc(sizeof(struct nodo));
	nuevoNodo->dato = unInt;
	nuevoNodo->prox = unaLista->primero;
	unaLista->primero = nuevoNodo;
}